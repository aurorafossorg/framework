/*
								   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2018 Aurora Free Open Source Software.

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

import aurorafw.core.debugmanager;
import aurorafw.core.logger;
import aurorafw.audio.soundio : SoundIoError, SoundIoDevice, soundio_strerror;
import aurorafw.audio.sndfile : SF_ERR_NO_ERROR, sf_error_number;

import std.string;
import std.stdio;

import std.conv : to;

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

	}

	this(const SoundIoDevice device) {

	}

	@property const string name() {
		pragma(msg, debugMsgPrefix, "TODO: Implement name's getter");
		return null;
	}

	@property const int maxInputChannels() {
		pragma(msg, debugMsgPrefix, "TODO: Implement maxInputChannels's getter");
		return 0;
	}

	@property const int maxOutputChannels() {
		pragma(msg, debugMsgPrefix, "TODO: Implement maxOutputChannels's getter");
		return 0;
	}

	@property const int outputLowLatency() {
		pragma(msg, debugMsgPrefix, "TODO: Implement outputLowLatency's getter");
		return 0;
	}

	@property const int outputHighLatency() {
		pragma(msg, debugMsgPrefix, "TODO: Implement outputHighLatency's getter");
		return 0;
	}

	@property const int inputLowLatency() {
		pragma(msg, debugMsgPrefix, "TODO: Implement inputLowLatency's getter");
		return 0;
	}

	@property const int inputHighLatency() {
		pragma(msg, debugMsgPrefix, "TODO: Implement inputHighLatency's getter");
		return 0;
	}

	@property const int sampleRate() {
		pragma(msg, debugMsgPrefix, "TODO: Implement sampleRate's getter");
		return 0;
	}

	@property const bool isInputDevice() {
		pragma(msg, debugMsgPrefix, "TODO: Implement isInputDevice's getter");
		return 0;
	}

	@property const bool isOutputDevice() {
		pragma(msg, debugMsgPrefix, "TODO: Implement isOutputDevice's getter");
		return 0;
	}

	@property const bool isDefaultInputDevice() {
		pragma(msg, debugMsgPrefix, "TODO: Implement isDefaultInputDevice's getter");
		return 0;
	}

	@property const bool isDefaultOutputDevice() {
		pragma(msg, debugMsgPrefix, "TODO: Implement isDefaultOutputDevice's getter");
		return 0;
	}
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
	this() {};
}

class AudioBackend {
public:
	float globalVolume = 1f;

	static ref AudioBackend getInstance() {
		if(!_instance)
			_instance = new AudioBackend();
		
		return _instance;
	}

	immutable (AudioDevice)[] getDevices() {
		pragma(msg, debugMsgPrefix, "TODO: Implement getDevices()");
		return null;
	}

	immutable (AudioDevice)[] getOutputDevices() {
		pragma(msg, debugMsgPrefix, "TODO: Implement getOutputDevices()");
		return null;
	}

	immutable (AudioDevice)[] getInputDevices() {
		pragma(msg, debugMsgPrefix, "TODO: Implement getInputDevices()");
		return null;
	}

	void setInputDevice(AudioDevice inputDevice) {
		pragma(msg, debugMsgPrefix, "TODO: Implement setInputDevice()");
	}

	void setOutputDevice(AudioDevice outputDevice) {
		pragma(msg, debugMsgPrefix, "TODO: Implement setOutputDevice()");
	}
private:
	static AudioBackend _instance;
	this() {
		/**
			* Pseudocode:
			* 1º - Call soundio_create() and create a Soundio context
			* 2º - Get the number of devices available through soundio_input/output_device_count()
			* 3º - Log the connected backend and num of devices
			*/
		pragma(msg, debugMsgPrefix, "TODO: Implement AudioBackend ctor()");

		import aurorafw.audio.soundio : soundio_version_string;
		log("SoundIo version: ", soundio_version_string.fromStringz);
	}
}

void catchSOUNDIOProblem(const SoundIoError error) {
	if(error != SoundIoError.SoundIoErrorNone)
		throw new SoundioException(error);
}

void catchSNDFILEProblem(const int error) {
	if(error != SF_ERR_NO_ERROR)
		throw new SNDFileException(error);
}