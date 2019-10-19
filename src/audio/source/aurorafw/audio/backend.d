/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2018-2019 Aurora Free Open Source Software.

This file is part of the Aurora Free Open Source Software. This
organization promote free and open source software that you can
redistribute and/or modify under the terms of the GNU Lesser General
Public License Version 3 as published by the Free Software Foundation or
(at your option) any later version approved by the Aurora Free Open Source
Software Organization. The license is available in the package root path
as 'LICENSE' file. Please review the following information to ensure the
GNU Lesser General Public License version 3 requirements will be met:
https://www.gnu.org/licenses/lgpl.html .

Alternatively, this file may be used under the terms of the GNU General
Public License version 3 or later as published by the Free Software
Foundation. Please review the following information to ensure the GNU
General Public License requirements will be met:
http://www.gnu.org/licenses/gpl-3.0.html.

NOTE: All products, services or anything associated to trademarks and
service marks used or referenced on this file are the property of their
respective companies/owners or its subsidiaries. Other names and brands
may be claimed as the property of others.

For more info about intellectual property visit: aurorafoss.org or
directly send an email to: contact (at) aurorafoss.org .
*/

module aurorafw.audio.backend;

import riverd.sndfile;
import riverd.soundio;
import aurorafw.core.logger;
import aurorafw.stdx.exception;

import std.conv : text, to;

import std.stdio;
import std.string;

class SoundioException : Throwable {
	this(SoundIoError error) {
		super("SoundIo error: " ~ to!string(soundio_strerror(error)));
	}
}

class SNDFileException : Throwable {
	this(int error) {
		super("SNDFile error: " ~ to!string(sf_error_number(error)));
	}
}

class AudioDevice {
	this() {
		SoundIo* soundio = AudioBackend.getInstance().soundio;
		this(soundio_get_output_device(soundio, soundio_default_output_device_index(soundio)));
	}

	this(SoundIoDevice* device) {
		catchSOUNDIOProblem(cast(SoundIoError)device.probe_error);

		this.device = device;
	}

	~this() {
		soundio_device_unref(device);
	}

	@property const string name() {
		return to!string(device.name.fromStringz);
	}

	@property const int maxInputChannels() {
		return isInputDevice() ? device.current_layout.channel_count : 0;
	}

	@property const int maxOutputChannels() {
		return isOutputDevice() ? device.current_layout.channel_count : 0;
	}

	@property const double currentLatency() {
		return device.software_latency_current;
	}

	@property const double minLatency() {
		return device.software_latency_min;
	}

	@property const double maxLatency() {
		return device.software_latency_max;
	}

	@property const int sampleRate() {
		return device.sample_rate_current;
	}

	@property const bool isInputDevice() {
		return device.aim == SoundIoDeviceAim.SoundIoDeviceAimInput;
	}

	@property const bool isOutputDevice() {
		return device.aim == SoundIoDeviceAim.SoundIoDeviceAimOutput;
	}

	@property const bool isDefaultInputDevice() {
		SoundIo* soundio = cast(SoundIo*)device.soundio;
		SoundIoDevice* defaultDevice = soundio_get_input_device(soundio, soundio_default_input_device_index(soundio));
		char* id = defaultDevice.id;
		soundio_device_unref(defaultDevice);

		return id == device.id && isInputDevice();
	}

	@property const bool isDefaultOutputDevice() {
		SoundIo* soundio = cast(SoundIo*)device.soundio;
		SoundIoDevice* defaultDevice = soundio_get_output_device(soundio, soundio_default_output_device_index(soundio));
		char* id = defaultDevice.id;
		soundio_device_unref(defaultDevice);

		return id == device.id && isOutputDevice();
	}

	package SoundIoDevice* device;
}

class AudioListener {
public:
	static ref AudioListener getInstance() {
		if(!_instance)
			_instance = new AudioListener;

		return _instance;
	}

	//import aurorafw.math.vector : Vector3d;
	//Vector3d position = new Vector3d, direction = new Vector3d(0, 0, -1);
private:
	__gshared AudioListener _instance;
	this() {}
}

class AudioBackend {
public:
	float globalVolume = 1f;

	static ref AudioBackend getInstance() {
		if(!_instance)
			_instance = new AudioBackend();

		return _instance;
	}

	immutable (AudioDevice[]) getDevices() {
		immutable (AudioDevice[]) devices = getOutputDevices ~ getInputDevices;
		return devices;
	}

	immutable (AudioDevice[]) getOutputDevices() {
		immutable int count = soundio_output_device_count(soundio);
		AudioDevice[] devices;

		for(int i = 0; i < count; i++) {
			devices ~= new AudioDevice(soundio_get_output_device(soundio, i));
		}

		return cast(immutable)devices;
	}

	immutable (AudioDevice[]) getInputDevices() {
		immutable int count = soundio_input_device_count(soundio);
		AudioDevice[] devices;

		for(int i = 0; i < count; i++) {
			devices ~= new AudioDevice(soundio_get_input_device(soundio, i));
		}

		return cast(immutable)devices;
	}

	void setInputDevice(AudioDevice inputDevice) {
		//TODO: Need implementation
		throw new NotImplementedException("Not yet implemented!");
	}

	void setOutputDevice(AudioDevice outputDevice) {
		//TODO: Need implementation
		throw new NotImplementedException("Not yet implemented!");
	}

	void flushEvents() {
		soundio_flush_events(soundio);
	}
private:
	this() {
		log("Initializing AudioBackend...");

		// Get versions from SoundIo and SNDFile
		log("SoundIo version: ", soundio_version_string.fromStringz);

		char[128] sndfileVersion;
		sf_command(null, SFC_GET_LIB_VERSION, sndfileVersion.ptr, sndfileVersion.sizeof);
		log("SNDFile version: ", sndfileVersion.ptr.fromStringz);

		// Initializes SoundIo
		soundio = soundio_create();
		if(!soundio)
			throw new SNDFileException(SoundIoError.SoundIoErrorNoMem);

		// Connects to a backend
		catchSOUNDIOProblem(cast(SoundIoError)soundio_connect(soundio));

		log("Connection to backend successfull. Current backend: ", soundio_backend_name(soundio.current_backend).fromStringz);

		// Gets the number of available devices
		flushEvents();
		immutable int outputNum = soundio_output_device_count(soundio), inputNum = soundio_input_device_count(soundio);
		log("AudioBackend initialized. Num. of ",
			"available audio devices: ", text(outputNum + inputNum), " (",
			outputNum, " output devices, ",
			inputNum, " input devices.)");
	}

	~this() {
		// Terminates SoundIo
		soundio_destroy(soundio);
	}

	static AudioBackend _instance;
	package SoundIo* soundio;
}

void catchSOUNDIOProblem(const SoundIoError error) {
	if(error != SoundIoError.SoundIoErrorNone)
		throw new SoundioException(error);
}

void catchSNDFILEProblem(const int error) {
	if(error != SF_ERR_NO_ERROR)
		throw new SNDFileException(error);
}
