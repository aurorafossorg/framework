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

module aurorafw.audio.output;

import std.conv : text;
import std.string : toStringz;

import aurorafw.core.debugmanager;
import aurorafw.core.logger;
import aurorafw.audio.backend : AudioDevice, catchSOUNDIOProblem, catchSNDFILEProblem;
import aurorafw.audio.utils : AudioInfo;
import aurorafw.audio.sndfile;
import aurorafw.audio.soundio;

enum AudioPlayMode : byte {
	Once,
	Loop
}

class AudioFileNotFoundException : Throwable {
	this(string file) {
		super("The specified audio file \"" ~ file ~ "\" couldn't be found/read!");
	}
}

extern(C) void audioOutputCallback(SoundIoOutStream* stream, int minFrames, int maxFrames) {
	pragma(msg, debugMsgPrefix, "TODO: Implement audioOutputCallback()");
}

extern(C) void debugCallback(SoundIoOutStream* stream, int minFrames, int maxFrames) {
	ubyte left_ear = 0;
	ubyte right_ear = 0;

	SoundIoChannelArea* area;

	int desiredFrames = maxFrames;

	while(desiredFrames > 0) {
		int frames = 256;
		catchSOUNDIOProblem(cast(SoundIoError)soundio_outstream_begin_write(stream, &area, &frames));

		for(int i = 0; i < frames; i++) {
			*(area[0].ptr) = left_ear;
			area[0].ptr += area[0].step;
			*(area[1].ptr) = right_ear;
			area[1].ptr += area[1].step;

			left_ear += 1;
			if(left_ear >= 255)
				left_ear -= 255;

			right_ear += 3;
			if(right_ear >= 255)
				right_ear -= 255;
		}

		catchSOUNDIOProblem(cast(SoundIoError)soundio_outstream_end_write(stream));

		desiredFrames -= frames;
	}
}

extern(C) void underFlowCallback(SoundIoOutStream* stream) {
	trace("Underflow ocurred!");
}

class AudioOStream {
	this() {
		audioInfo = new AudioInfo();
		trace("Debug mode activated for AudioStream instance");

		AudioDevice device = new AudioDevice();
		stream = soundio_outstream_create(device.device);
		trace("Output stream created.");

		stream.write_callback = &debugCallback;
		stream.underflow_callback = &underFlowCallback;
		stream.sample_rate = device.sampleRate;
		if(soundio_device_supports_format(device.device, SoundIoFormat.SoundIoFormatU8))
			stream.format = SoundIoFormat.SoundIoFormatU8;
		stream.name = "AuroraFW Application".toStringz;
		trace("Output stream configurated.");

		catchSOUNDIOProblem(cast(SoundIoError)soundio_outstream_open(stream));
		trace("Output stream started.");
	}

	this(immutable string path, immutable bool buffered) {
		audioInfo = new AudioInfo();

		audioInfo._sndFile = sf_open(path.toStringz, SFM_READ, audioInfo._sndInfo);

		// If the audio should be buffered, do so
		if(buffered) {
			debug trace("Buffering the audio... (Total frames: " ~ text(audioInfo.frames * audioInfo.channels) ~ ")");
			_buffer = new float[audioInfo.frames * audioInfo.channels];
			sf_readf_float(audioInfo._sndFile, _buffer.ptr, audioInfo.frames);
			debug trace("Buffering complete.");
		}

		// If the soundFile is null, it means there was no audio file
		if(!audioInfo._sndFile)
			throw new AudioFileNotFoundException(path);

		AudioDevice device;

		// soundio_create_stream(...);

		pragma(msg, debugMsgPrefix, "TODO: Implement AudioOStream ctor()");
	}

	void play() {
		sf_seek(audioInfo._sndFile, _streamPosFrame, SF_SEEK_SET);
		catchSOUNDIOProblem(cast(SoundIoError)soundio_outstream_start(stream));
	}

	void pause() {
		pragma(msg, debugMsgPrefix, "TODO: Implement pause()");
		// soundio_stop_stream(...);
	}

	void stop() {
		pragma(msg, debugMsgPrefix, "TODO: Implement stop()");
		_streamPosFrame = 0;

		// soundio_stop_stream(...);
	}

	bool isPlaying() {
		pragma(msg, debugMsgPrefix, "TODO: Implement isPlaying()");
		// return soundio_is_stream_active(...);
		return 0;
	}

	bool isPaused() {
		pragma(msg, debugMsgPrefix, "TODO: Implement isPaused()");
		// return !soundio_is_stream_active(...) && _streamPosFrame != 0;
		return 0;
	}

	bool isStopped() {
		pragma(msg, debugMsgPrefix, "TODO: Implement isStopped()");
		// return !soundio_is_stream_active(...);
		return 0;
	}

	void setStreamPos(uint pos) {
		pragma(msg, debugMsgPrefix,"TODO: Implement setStreamPos(uint pos)");
	}

	void setStreamPosFrame(uint pos) {
		pragma(msg, debugMsgPrefix, "TODO: Implement setStreamPosFrame()");
		_streamPosFrame = pos;
	}

	float getNumLoops() {
		pragma(msg, debugMsgPrefix, "TODO: Implement getNumLoops()");
		return _loops;
	}

	float getCpuLoad() {
		pragma(msg, debugMsgPrefix, "TODO: Implement getCpuLoad()");
		// return soundio_get_cpu_load(...);
		return 0;
	}

	AudioPlayMode audioPlayMode;
	AudioInfo audioInfo;
	SoundIoOutStream* stream;

	float volume = 1;
	pragma(msg, debugMsgPrefix, "TODO: Implement pitch");
	float pitch = 1;

private:
	//SoundioStream soundioStream;
	float[] _buffer;
	uint _streamPosFrame = 0;
	ubyte _loops;
}