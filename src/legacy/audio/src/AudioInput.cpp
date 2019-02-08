/*****************************************************************************
**                                     __
**                                    / _|
**   __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
**  / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
** | (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
**  \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/
**
** Copyright (C) 2018-2019 Aurora Free Open Source Software.
**
** This file is part of the Aurora Free Open Source Software. This
** organization promote free and open source software that you can
** redistribute and/or modify under the terms of the GNU Lesser General
** Public License Version 3 as published by the Free Software Foundation or
** (at your option) any later version approved by the Aurora Free Open Source
** Software Organization. The license is available in the package root path
** as 'LICENSE' file. Please review the following information to ensure the
** GNU Lesser General Public License version 3 requirements will be met:
** https://www.gnu.org/licenses/lgpl.html .
**
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3 or later as published by the Free Software
** Foundation. Please review the following information to ensure the GNU
** General Public License requirements will be met:
** http://www.gnu.org/licenses/gpl-3.0.html.
**
** NOTE: All products, services or anything associated to trademarks and
** service marks used or referenced on this file are the property of their
** respective companies/owners or its subsidiaries. Other names and brands
** may be claimed as the property of others.
**
** For more info about intellectual property visit: aurorafoss.org or
** directly send an email to: contact (at) aurorafoss.org .
*****************************************************************************/

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