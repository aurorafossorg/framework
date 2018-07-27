/*****************************************************************************
**                                    / _|
**   __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
**  / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
** | (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
**  \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/
**
** Copyright (C) 2018 Aurora Free Open Source Software.
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

#include <AuroraFW/Audio/AudioOutput.h>

namespace AuroraFW {
	namespace AudioManager {
		// AudioFileNotFound
		AudioFileNotFound::AudioFileNotFound(const char* fileName)
			: _errorMessage(std::string("The specified audio file \""
			+ std::string(fileName)
			+ "\" couldn't be found/read!")) {}

		const char* AudioFileNotFound::what() const throw()
		{
			return _errorMessage.c_str();
		}

		// audioOutputCallback
		int audioOutputCallback(const void* inputBuffer, void* outputBuffer,
						size_t framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo,
						PaStreamCallbackFlags statusFlags, void* userData)
		{
			#pragma message("TODO: Cleanup this method as much as possible")
			// Gets the output buffer (it's of type paFloat32), and
			// the audioStream and audioInfo
			float* output = (float*)outputBuffer;
			AudioOStream* audioStream = (AudioOStream*)userData;
			AudioInfo* audioInfo = &(audioStream->audioInfo);

			// Reads the audio
			size_t readFrames = 0, offset = 0, framesToRead = framesPerBuffer;
			do {
				int readFramesNow;
				if(audioStream->_buffer != nullptr) {	// Buffered
					readFramesNow = (framesToRead + audioStream->_streamPosFrame)
					> audioInfo->getFrames()
					? audioInfo->getFrames() - audioStream->_streamPosFrame
					: framesToRead;

					for(size_t f = 0; f < readFramesNow; f++) {
						for(uint8_t c = 0; c < audioInfo->getChannels(); c++) {
							output[(offset * audioInfo->getChannels())
							+ f * audioInfo->getChannels() + c]
							= audioStream->_buffer[audioStream->_streamPosFrame
							* audioInfo->getChannels() + (f * audioInfo->getChannels()
							+ c)];
						}
					}
				} else {	// Streaming
					readFramesNow = sf_readf_float(audioInfo->_sndFile, output
					+ (offset * audioInfo->getChannels()), framesToRead);
				}

				audioStream->_streamPosFrame += readFramesNow;
				framesToRead -= readFramesNow;
				readFrames += readFramesNow;

				if(framesToRead > 0 && audioStream->audioPlayMode
					== AudioPlayMode::Loop) {
					audioStream->_streamPosFrame = 0;
					audioStream->_loops++;
					offset += readFramesNow;
					if(audioStream->_buffer == nullptr)	// Streaming
						sf_seek(audioInfo->_sndFile, 0, SF_SEEK_SET);
				}
			} while(framesToRead > 0 && audioStream->audioPlayMode
					!= AudioPlayMode::Once);
			// Adjusts the volume of each frame
			for(size_t i = 0; i < readFrames; i++) {
				// Applies the volume to all channels the sound might have
				for(uint8_t channels = 0; channels < audioInfo->getChannels();
					channels++) {
					float frame = *output;

					// In case there's 3D audio, calculates 3D audio
					if(audioStream->_audioSource != nullptr) {
						AudioSource* source = audioStream->_audioSource;
						const float panning = source->getPanning();
						if(channels == 0)
							frame *= (-0.5f * panning + 0.5f);
						else if(channels == 1)
							frame *= (0.5f * panning + 0.5f);
					}

					frame *= audioStream->volume
					* AudioBackend::getInstance().globalVolume;

					*output++ = frame;
				}
			}

			// If the read frames didn't fill the buffer to read, it reached EOF
			if(readFrames < framesPerBuffer && audioStream->audioPlayMode
				== AudioPlayMode::Once)
				return paComplete;

			return paContinue;
		}

		// debugCallBack
		int debugCallback(const void* inputBuffer, void* outputBuffer,
						size_t framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo,
						PaStreamCallbackFlags statusFlags, void* userData)
		{
			uint8_t left_ear = 0;
			uint8_t right_ear = 0;

			uint8_t* output = (uint8_t*)outputBuffer;

			for(unsigned int i = 0; i < framesPerBuffer; i++) {
				*output++ = left_ear;
				*output++ = right_ear;

				left_ear += 1;
				if(left_ear >= 255)
					left_ear -= -255;

				right_ear += 3;
				if(right_ear >= 255)
					right_ear -= -255;
			}

			return 0;
		}

		// AudioSource
		AudioSource::AudioSource()
			: _position(Math::Vector3D())
		{
			calculateValues();
		}

		AudioSource::AudioSource(const Math::Vector3D vec)
			: _position(vec)
		{
			calculateValues();
		}

		AudioSource::AudioSource(const float x, const float y, const float z)
			: _position(Math::Vector3D(x, y, z))
		{
			calculateValues();
		}

		AudioSource::AudioSource(const AudioSource& audioSource)
			: falloutType(audioSource.falloutType),
			_position(audioSource._position),
			_medDistance(audioSource._medDistance),
			_maxDistance(audioSource._maxDistance)
		{
			calculateValues();
		}

		void AudioSource::setPosition(Math::Vector3D position)
		{
			_position = position;
			_calculatePan();
		}

		void AudioSource::setMedDistance(float medDistance)
		{
			_medDistance = medDistance;
			_calculateStrength();
		}

		void AudioSource::setMaxDistance(float maxDistance)
		{
			_maxDistance = maxDistance;
			_calculateStrength();
		}

		float AudioSource::getPanning()
		{
			return _pan;
		}

		float AudioSource::getStrength()
		{
			return _strength;
		}

		Math::Vector3D AudioSource::getPosition()
		{
			return _position;
		}

		float AudioSource::getMedDistance()
		{
			return _medDistance;
		}

		float AudioSource::getMaxDistance()
		{
			return _maxDistance;
		}

		void AudioSource::calculateValues()
		{
			_calculatePan();
			_calculateStrength();
		}

		void AudioSource::_calculatePan()
		{
			Math::Vector3D listenerPos = AudioListener::getInstance().position;
			Math::Vector3D listenerDir = AudioListener::getInstance().direction;

			#pragma message("TODO: Values are hardcoded (see info on code)")
			// TODO: Right now it's hardcoded because the camera, under normal
			// circunstances, doesn't \"tilt\". Make less dirty later
			Math::Vector3D listenerUp = Math::Vector3D(0, 1, 0);

			#pragma message("FIXME: Not using matrixes (see info on code)")
			// FIXME: The method to obtain the perpendicular to both dir and
			// lookUp didn't use matrixes , because I am inexperienced on it.
			// This is where I got the formula:
			// https://math.stackexchange.com/questions/501949/determining-a-perpendicular-vector-to-two-given-vectors
			// however, this is dirty and should be cleaned up.)
			float x = listenerDir.y * listenerUp.z - listenerDir.z * listenerUp.y;
			float y = listenerDir.z * listenerUp.x - listenerDir.x * listenerUp.z;
			float z = listenerDir.x * listenerUp.y - listenerDir.y * listenerUp.x;

			Math::Vector3D cross = Math::Vector3D(x, y, z);
			cross.normalize();

			// Makes a copy of position, since it needs to be manipulated
			// to calculate the panning
			Math::Vector3D sourcePos = _position;
			sourcePos -= listenerPos;

			_pan = cross.dot(sourcePos.normalized());
		}

		void AudioSource::_calculateStrength()
		{
			#pragma message ("TODO: Need to be implemented")
			float distance = Math::abs(_position.distanceToPoint
			(AudioListener::getInstance().position));
		}

		// AudioOStream
		AudioOStream::AudioOStream()
			: _audioSource(nullptr)
		{
			AuroraFW::DebugManager::Log("Debug mode activated for AudioStream instance");

			AudioDevice device;

			catchPAProblem(Pa_OpenDefaultStream(&_paStream, 0, 2, paUInt8,
				device.getDefaultSampleRate(), 256, debugCallback, NULL));
		}

		AudioOStream::AudioOStream(const char* path, AudioSource* audioSource, bool buffered)
			: audioInfo(), _audioSource(audioSource)
		{
			audioInfo._sndFile = sf_open(path, SFM_READ, audioInfo._sndInfo);

			// If the audio should be buffered, do so
			if(buffered) {
				AuroraFW::DebugManager::Log("Buffering the audio..."
				"(Total frames: ", audioInfo.getFrames() * audioInfo.getChannels(), ")");
				_buffer = AFW_NEW float[audioInfo.getFrames() * audioInfo.getChannels()];
				sf_readf_float(audioInfo._sndFile, _buffer, audioInfo.getFrames());
				AuroraFW::DebugManager::Log("Buffering complete.");
			}

			// If the soundFile is null, it means there was no audio file
			if(audioInfo._sndFile == nullptr)
				throw AudioFileNotFound(path);

			AudioDevice device;

			// Opens the audio stream
			catchPAProblem(Pa_OpenDefaultStream(&_paStream, 0, audioInfo.getChannels(),
			paFloat32, device.getDefaultSampleRate(),
			paFramesPerBufferUnspecified, audioOutputCallback, this));
		}

		AudioOStream::~AudioOStream()
		{
			// Deletes the buffer
			if(_buffer != AFW_NULLPTR)
				delete[] _buffer;

			// Deletes audioSource
			if(_audioSource != AFW_NULLPTR)
				delete _audioSource;
		}

		void AudioOStream::play()
		{
			sf_seek(audioInfo._sndFile, _streamPosFrame, SF_SEEK_SET);
			catchPAProblem(Pa_StartStream(_paStream));
		}

		void AudioOStream::pause()
		{
			catchPAProblem(Pa_StopStream(_paStream));
		}

		void AudioOStream::stop()
		{
			_streamPosFrame = 0;
			
			catchPAProblem(Pa_StopStream(_paStream));
		}

		bool AudioOStream::isPlaying()
		{
			return Pa_IsStreamActive(_paStream);
		}

		bool AudioOStream::isPaused()
		{
			return isStopped() && _streamPosFrame != 0;
		}

		bool AudioOStream::isStopped()
		{
			return Pa_IsStreamStopped(_paStream);
		}

		void AudioOStream::setStreamPos(unsigned int pos)
		{
			#pragma message ("TODO: Need to be implemented")
		}

		void AudioOStream::setStreamPosFrame(unsigned int pos)
		{
			_streamPosFrame = pos;
		}

		AudioSource* AudioOStream::getAudioSource()
		{
			return _audioSource;
		}

		void AudioOStream::setAudioSource(const AudioSource& audioSource)
		{
			delete _audioSource;
			_audioSource = new AudioSource(audioSource);
		}

		float AudioOStream::getCpuLoad()
		{
			return Pa_GetStreamCpuLoad(_paStream);
		}
	}
}
