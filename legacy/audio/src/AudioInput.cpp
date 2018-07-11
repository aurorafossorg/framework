/****************************************************************************
** ┌─┐┬ ┬┬─┐┌─┐┬─┐┌─┐  ┌─┐┬─┐┌─┐┌┬┐┌─┐┬ ┬┌─┐┬─┐┬┌─
** ├─┤│ │├┬┘│ │├┬┘├─┤  ├┤ ├┬┘├─┤│││├┤ ││││ │├┬┘├┴┐
** ┴ ┴└─┘┴└─└─┘┴└─┴ ┴  └  ┴└─┴ ┴┴ ┴└─┘└┴┘└─┘┴└─┴ ┴
** A Powerful General Purpose Framework
** More information in: https://aurora-fw.github.io/
**
** Copyright (C) 2017 Aurora Framework, All rights reserved.
**
** This file is part of the Aurora Framework. This framework is free
** software; you can redistribute it and/or modify it under the terms of
** the GNU Lesser General Public License version 3 as published by the
** Free Software Foundation and appearing in the file LICENSE included in
** the packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************/

#include <AuroraFW/Audio/AudioInput.h>

namespace AuroraFW {
	namespace AudioManager {
		// audioInputCallback
		int audioInputCallback(const void* inputBuffer, void* outputBuffer,
				size_t framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags, void* userData)
		{
			float* input = (float*)inputBuffer;
			AudioIStream* stream = (AudioIStream*)userData;
			AudioInfo* info = stream->info;

			for(size_t f = 0; f < framesPerBuffer; f++) {
				for(uint8_t c = 0; c < info->getChannels(); c++) {
					stream->buffer[stream->_streamPosFrame * info->getChannels()
					+ (f * info->getChannels() + c)]
					= input[f * info->getChannels() + c];

					if(stream->_streamPosFrame + f == stream->bufferSize) {
						stream->_streamPosFrame = stream->bufferSize;
						return paComplete;
					}
				}
			}

			stream->_streamPosFrame += framesPerBuffer;

			return paContinue;
		}

		// AudioIStream
		AudioIStream::AudioIStream(const char* path, AudioInfo* info, int bufferSize)
			: path(path), info(info), bufferSize(bufferSize)
		{
			buffer = AFW_NEW float[bufferSize * info->getChannels()];

			info->_sndFile = sf_open(path, SFM_WRITE, info->_sndInfo);

			catchPAProblem(Pa_OpenDefaultStream(&_paStream, info->getChannels(), 0, paFloat32,
				info->getSampleRate(), paFramesPerBufferUnspecified,
				audioInputCallback, this));
		}

		AudioIStream::~AudioIStream()
		{
			if(buffer != AFW_NULLPTR)
				delete[] buffer;

			if(info != AFW_NULLPTR)
				delete info;
		}

		void AudioIStream::record()
		{
			catchPAProblem(Pa_StartStream(_paStream));
		}

		void AudioIStream::pause()
		{
			catchPAProblem(Pa_StopStream(_paStream));
		}

		void AudioIStream::stop()
		{
			_streamPosFrame = 0;

			catchPAProblem(Pa_StopStream(_paStream));
		}

		bool AudioIStream::isRecording()
		{
			return Pa_IsStreamActive(_paStream);
		}

		bool AudioIStream::isPaused()
		{
			return isStopped() && _streamPosFrame != 0;
		}

		bool AudioIStream::isStopped()
		{
			return Pa_IsStreamStopped(_paStream);
		}

		bool AudioIStream::isBufferFull()
		{
			#pragma message ("TODO: Need to be implemented")
		}

		void AudioIStream::clearBuffer()
		{
			#pragma message ("TODO: Need to be implemented")
		}

		void AudioIStream::clearBuffer(unsigned int start, unsigned int end)
		{
			#pragma message ("TODO: Need to be implemented")
		}

		bool AudioIStream::save()
		{
			if(sf_writef_float(info->_sndFile, buffer, bufferSize) == -1)
				return false;
			return true;
		}
	}
}