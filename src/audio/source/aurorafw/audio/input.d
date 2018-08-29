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

module aurorafw.audio.input;

import aurorafw.audio.utils : AudioInfo;
import aurorafw.core.debugmanager;

protected int audioInputCallback() {
	pragma(msg, debugMsgPrefix, "TODO: Implement audioInputCallback()");
	return 0;
}

class AudioIStream {
	this(const string path, AudioInfo audioInfo, int bufferSize) {
		this.path = path;
		this.audioInfo = audioInfo;
		this.bufferSize = bufferSize;

		buffer = new float[bufferSize /** info.channels*/];

		//info._sndFile = sf_open(path, SFM_WRITE, info._sndInfo);

		// soundio_write_stream(...);
		pragma(msg, debugMsgPrefix, "TODO: Implement AudioIStream ctor()");
	}

	void record() {
		pragma(msg, debugMsgPrefix, "TODO: Implement record()");
		//soundio_start_stream(...);
	}

	void pause() {
		pragma(msg, debugMsgPrefix, "TODO: Implement pause()");
		//soundio_stop_stream(...);
	}

	void stop() {
		pragma(msg, debugMsgPrefix, "TODO: Implement stop()");
		_streamPosFrame = 0;

		//soundio_stop_stream(...);
	}

	bool isRecording() {
		pragma(msg, debugMsgPrefix, "TODO: Implement isRecording()");
		//return soundio_is_stream_active(...);
		return 0;
	}

	bool isPaused() {
		pragma(msg, debugMsgPrefix, "TODO: Implement isPaused()");
		//return !soundio_is_stream_active(...) && _streamPosFrame != 0;
		return 0;
	}

	bool isStopped() {
		pragma(msg, debugMsgPrefix, "TODO: Implement isStopped()");
		//return !soundio_is_stream_active(...)
		return 0;
	}

	bool isBufferFull() {
		pragma(msg, debugMsgPrefix, "TODO: Implement isBufferFull()");
		return 0;
	}
	void clearBuffer() {
		pragma(msg, debugMsgPrefix, "TODO: Implement clearBuffer()");
	}

	void clearBuffer(uint start, uint finish) {
		pragma(msg, debugMsgPrefix, "TODO: Implement clearBuffer(uint start, uint finish)");
	}

	bool save() {
		pragma(msg, debugMsgPrefix, "TODO: Implement save()");
		/*
		if(sf_write_float(info._sndFile, buffer, bufferSize) == -1)
			return false;
		return true;
		*/
		return 0;
	}


	immutable string path;
	AudioInfo audioInfo;
	pragma(msg, debugMsgPrefix, "TODO: Define wether the buffer should be public or private");
	float[] buffer;
	immutable uint bufferSize;

private:
	//soundioStream soundioStream;
	uint _streamPosFrame;
}