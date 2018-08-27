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

module aurorafw.audio.audiobackend;

class AudioDevice {
	this() {

	}

	/*this(const SoundioDevice device) {

	}*/

	immutable string getName() {
		pragma(msg, "TODO: Implement getName()");
		return null;
	}

	immutable int getMaxInputExceptions() {
		pragma(msg, "TODO: Implement getMaxInputExceptions()");
		return 0;
	}

	immutable int getMaxOutputExceptions() {
		pragma(msg, "TODO: Implement getMaxOutputExceptions()");
		return 0;
	}

	immutable int getOutputLowLatencyExceptions() {
		pragma(msg, "TODO: Implement getOutputLowLatencyExceptions()");
		return 0;
	}

	immutable int getOutputHighLatencyExceptions() {
		pragma(msg, "TODO: Implement getOutputHighLatencyExceptions()");
		return 0;
	}

	immutable int getInputLowLatencyExceptions() {
		pragma(msg, "TODO: Implement getInputLowLatencyExceptions()");
		return 0;
	}

	immutable int getInputHighLatencyExceptions() {
		pragma(msg, "TODO: Implement getInputHighLatencyExceptions()");
		return 0;
	}

	immutable bool isInputDevice() {
		pragma(msg, "TODO: Implement isInputDevice()");
		return 0;
	}

	immutable bool isOutputDevice() {
		pragma(msg, "TODO: Implement isOutputDevice()");
		return 0;
	}

	immutable bool isDefaultInputDevice() {
		pragma(msg, "TODO: Implement isDefaultInputDevice()");
		return 0;
	}

	immutable bool isDefaultOutputDevice() {
		pragma(msg, "TODO: Implement isDefaultOutputDevice()");
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

	immutable AudioDevice[] getDevices() {
		pragma(msg, "TODO: Implement getDevices()");
		return null;
	}

	immutable AudioDevice[] getOutputDevices() {
		pragma(msg, "TODO: Implement getOutputDevices()");
		return null;
	}

	immutable AudioDevice[] getInputDevices() {
		pragma(msg, "TODO: Implement getInputDevices()");
		return null;
	}

	void setInputDevice(AudioDevice inputDevice) {
		pragma(msg, "TODO: Implement setInputDevice()");
	}

	void setOutputDevice(AudioDevice outputDevice) {
		pragma(msg, "TODO: Implement setOutputDevice()");
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
		pragma(msg, "TODO: Implement AudioBackend ctor()");
	}
}