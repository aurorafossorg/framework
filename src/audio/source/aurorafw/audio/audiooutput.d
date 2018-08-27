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

module aurorafw.audio.audiooutput;

import aurorafw.core.debugmanager;
import aurorafw.audio.audiobackend : AudioDevice;

enum AudioPlayMode : byte {
	Once,
	Loop
}

class AudioFileNotFoundExcpetion : Throwable {
	this(string file) {
		super("The specified audio file \"" ~ file ~ "\" couldn't be found/read!");
	}
}

int audioOutputCallback() {
	pragma(msg, "TODO: Implement audioOutputCallback()");
	return 0;
}

int debugCallback() {
	pragma(msg, "TODO: Implement debugCallback()");
	return 0;
}

class AudioOStream {
	this() {
		debug trace("Debug mode activated for AudioStream instance");

		/*
			AudioDevice device;
			soundio_create_stream(...);
		*/
	}

	this(immutable string path, immutable bool buffered) {
		//audioInfo = new AudioInfo();

		//audioInfo._sndFile = sf_open(path, SFM_READ, audioInfo._sndInfo);

		// If the audio should be buffered, do so
		if(buffered) {
			debug trace("Buffering the audio... (Total frames: )" /*audioInfo.frames * audioInfo.channels*/);
			//_buffer = new float[/*audioInfo.frames * audioInfo.channels*/];
			//sf_readf_float(audioInfo._sndFile, _buffer, audioInfo.frames);
			debug trace("Buffering complete.");
		}

		// If the soundFile is null, it means there was no audio file
		/*
		if(!audioInfo._sndFile)
			throw AudioFileNotFoundException(path);
		*/

		AudioDevice device;

		// soundio_create_stream(...);

		pragma(msg, "TODO: Implement AudioOStream ctor()");
	}

	void play() {
		pragma(msg, "TODO: Implement play()");
		// sf_seek(audioInfo._sndFile, _streamPosFrame, SF_SEEK_SET);
		// soundio_start_stream(...);
	}

	void pause() {
		pragma(msg, "TODO: Implement pause()");
		// soundio_stop_stream(...);
	}

	void stop() {
		pragma(msg, "TODO: Implement stop()");
		_streamPosFrame = 0;

		// soundio_stop_stream(...);
	}

	bool isPlaying() {
		pragma(msg, "TODO: Implement isPlaying()");
		// return soundio_is_stream_active(...);
		return 0;
	}

	bool isPaused() {
		pragma(msg, "TODO: Implement isPaused()");
		// return !soundio_is_stream_active(...) && _streamPosFrame != 0;
		return 0;
	}

	bool isStopped() {
		pragma(msg, "TODO: Implement isStopped()");
		// return !soundio_is_stream_active(...);
		return 0;
	}

	void setStreamPos(uint pos) {
		pragma(msg,"TODO: Implement setStreamPos(uint pos)");
	}

	void setStreamPosFrame(uint pos) {
		pragma(msg, "TODO: Implement setStreamPosFrame()");
		_streamPosFrame = pos;
	}

	float getNumLoops() {
		pragma(msg, "TODO: Implement getNumLoops()");
		return _loops;
	}

	float getCpuLoad() {
		pragma(msg, "TODO: Implement getCpuLoad()");
		// return soundio_get_cpu_load(...);
		return 0;
	}

	AudioPlayMode audioPlayMode;
	//AudioInfo audioInfo;
	float volume = 1;
	pragma(msg, "TODO: Implement pitch");
	float pitch = 1;

private:
	//SoundioStream soundioStream;
	float[] _buffer;
	uint _streamPosFrame = 0;
	ubyte _loops;
}