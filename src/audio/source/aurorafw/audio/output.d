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

module aurorafw.audio.output;

import std.conv : text, to;
import std.string : toStringz;
import std.math : round, rint;
import std.algorithm : max;
import core.thread : Thread;
import core.time: Duration, dur;

import aurorafw.core.debugmanager;
import aurorafw.core.logger;
import aurorafw.audio.backend : AudioDevice, catchSOUNDIOProblem, catchSNDFILEProblem, AudioBackend;
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
	pragma(msg, "TODO: Cleanup this method as much as possible");
	// Gets the output buffer (it's of type float32NE), and
	// the audioStream and audioInfo
	// DEBUG

	AudioOStream audioStream = cast(AudioOStream)(stream.userdata);
	AudioInfo audioInfo = audioStream.audioInfo;

	int framesLeft = maxFrames;

	// If the stream is stopped, exit the callback
	if(audioStream.isStopped()) {
		trace("Callback stopped at beginning...");
		return;
	}

	// Fills the buffer to it's fullest
	while(framesLeft > 0) {
		// Gets the number of frames it needs to read
		//int framesToRead = framesLeft;
		int framesToRead = 256;
		SoundIoChannelArea* area;
		catchSOUNDIOProblem(cast(SoundIoError)soundio_outstream_begin_write(stream, &area, &framesToRead));

		// Reads the frames
		int framesRead;
		do {
			// Fill the data using either buffer or stream
			if(audioStream._buffer.length > 0) {	// Buffered
				framesRead = (framesToRead + audioStream._streamPosFrame) > audioInfo.frames
					? audioInfo.frames - audioStream._streamPosFrame
					: framesToRead;

				for(int f = 0; f < framesRead; f++) {
					for(ubyte c = 0; c < audioInfo.channels; c++) {
						float* output = cast(float*)(area[c].ptr + area[c].step * f);
						*output = audioStream._buffer[audioStream._streamPosFrame
						* audioInfo.channels + (f * audioInfo.channels
						+ c)];
					}
				}
			} else {	// Streaming
				float* output = cast(float*)(area.ptr);
				framesRead = cast(int)sf_readf_float(audioInfo._sndFile, output, framesToRead);
			}

			// Updates the value of frames read
			framesToRead -= framesRead;
			framesLeft -= framesRead;
			audioStream._streamPosFrame += framesRead;

			// If it reached EOF and is in looping mode, restart accordingly
			if(framesToRead > 0 && audioStream.audioPlayMode == AudioPlayMode.Loop) {
				audioStream._streamPosFrame = 0;
				audioStream._loops++;
				// If streaming reset the seek pointer to start of file
				if(audioStream._buffer.length == 0)
					sf_seek(audioInfo._sndFile, 0, SF_SEEK_SET);
			}
		} while(framesToRead > 0 && audioStream.audioPlayMode == AudioPlayMode.Loop);

		debug trace("Frames to read: ", framesToRead, "\tFrames read: ", framesRead, "\tFrames left: ", framesLeft);

		// If the read frames didn't fill the buffer to read, it reached EOF
		if(framesToRead > 0 && audioStream.audioPlayMode
			== AudioPlayMode.Once) {
			debug trace("No more frames to read, filling the rest with zero...");
			for(int f = 0; f < framesLeft; f++) {
					for(ubyte c = 0; c < audioInfo.channels; c++) {
						float* output = cast(float*)(area[c].ptr + area[c].step * (f + framesRead));
						*output = 0;
					}
				}
			//audioStream.stop();
			framesLeft = 0;
			break;
		}

		catchSOUNDIOProblem(cast(SoundIoError)soundio_outstream_end_write(stream));
	}
	trace("Exited while loop!");
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
		_stream = soundio_outstream_create(device.device);

		_stream.write_callback = &debugCallback;
		_stream.sample_rate = device.sampleRate;
		if(soundio_device_supports_format(device.device, SoundIoFormat.SoundIoFormatU8))
			_stream.format = SoundIoFormat.SoundIoFormatU8;
		_stream.name = "AuroraFW Application".toStringz;

		catchSOUNDIOProblem(cast(SoundIoError)soundio_outstream_open(_stream));
	}

	this(immutable string path, immutable bool buffered) {
		audioInfo = new AudioInfo();

		audioInfo._sndFile = sf_open(path.toStringz, SFM_READ, audioInfo._sndInfo);

		// If the soundFile is null, it means there was no audio file
		if(!audioInfo._sndFile)
			throw new AudioFileNotFoundException(path);

		// If the audio should be buffered, do so
		if(buffered) {
			trace("Buffering the audio... (Total frames: " ~ text(audioInfo.frames * audioInfo.channels) ~ ")");
			_buffer = new float[audioInfo.frames * audioInfo.channels];
			sf_readf_float(audioInfo._sndFile, _buffer.ptr, audioInfo.frames);
			trace("Buffering complete.");
		}

		AudioDevice device = new AudioDevice();
		_stream = soundio_outstream_create(device.device);

		_stream.write_callback = &audioOutputCallback;
		_stream.sample_rate = device.sampleRate;
		_stream.name = "AuroraFW Application".toStringz;
		if(soundio_device_supports_format(device.device, SoundIoFormat.SoundIoFormatU32LE))
			_stream.format = SoundIoFormat.SoundIoFormatU32LE;
		_stream.userdata = cast(void*)this;

		catchSOUNDIOProblem(cast(SoundIoError)soundio_outstream_open(_stream));
	}

	~this() {
		soundio_outstream_destroy(_stream);
	}

	void play() {
		playing = true;
		//sf_seek(audioInfo._sndFile, _streamPosFrame, SF_SEEK_SET);
		catchSOUNDIOProblem(cast(SoundIoError)soundio_outstream_start(_stream));
	}

	void pause() {
		playing = false;
		catchSOUNDIOProblem(cast(SoundIoError)soundio_outstream_pause(_stream, true));
	}

	void stop() {
		_streamPosFrame = 0;

		playing = false;
		catchSOUNDIOProblem(cast(SoundIoError)soundio_outstream_pause(_stream, true));
		//Thread.sleep(dur!("msecs")(cast(long)rint(_stream.software_latency * 1000)));
	}

	void callbackStop() {
		trace("Being called!");
		callbackStopped = true;
	}

	bool isPlaying() {
		return playing;
	}

	bool isPaused() {
		return !playing && _streamPosFrame != 0;
	}

	bool isStopped() {
		debug trace("!playing: ", text(!playing), "\t_streamPosFrame: ", _streamPosFrame);
		return !playing && _streamPosFrame == 0;
	}

	bool isCallbackStopped() {
		trace(text(callbackStopped));
		return callbackStopped;
	}

	void setStreamPos(double pos) {
		setStreamPosFrame(to!uint(round(pos * audioInfo.sampleRate) * audioInfo.channels));
	}

	void setStreamPosFrame(uint pos) {
		_streamPosFrame = pos;
	}

	float getNumLoops() {
		return _loops;
	}

	float getCpuLoad() {
		pragma(msg, debugMsgPrefix, "TODO: Implement getCpuLoad()");
		// return soundio_get_cpu_load(...);
		return 0;
	}

	AudioPlayMode audioPlayMode;
	AudioInfo audioInfo;

	float volume = 1;
	pragma(msg, debugMsgPrefix, "TODO: Implement pitch");
	float pitch = 1;

private:
	SoundIoOutStream* _stream;
	float[] _buffer;
	int _streamPosFrame = 0;
	ubyte _loops;
	bool playing, callbackStopped = false;
}
