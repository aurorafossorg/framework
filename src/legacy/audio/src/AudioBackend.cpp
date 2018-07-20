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

#include <AuroraFW/Audio/AudioBackend.h>

namespace AuroraFW {
	namespace AudioManager {
		// PAErrorException
		PAErrorException::PAErrorException(const PaError& paError)
			: _paError(std::string("PortAudio error: "
			+ std::string(Pa_GetErrorText(paError))))
		{}

		const char* PAErrorException::what() const throw()
		{
			return _paError.c_str();
		}

		// SNDFILEErrorException
		SNDFILEErrorException::SNDFILEErrorException(const int& error)
			: _sndFileError(std::string("SNDFILE error: "
			+ std::string(sf_error_number(error))))
		{}

		const char* SNDFILEErrorException::what() const throw()
		{
			return _sndFileError.c_str();
		}

		// AudioNotInitializedException
		const char* AudioNotInitializedException::what() const throw()
		{
			return "The AudioBackend was not initialized yet!";
		}

		// AudioListener
		AudioListener* AudioListener::_instance = nullptr;

		void AudioListener::_start()
		{
			_instance = new AudioListener();
		}

		void AudioListener::_stop()
		{
			delete _instance;
		}

		AudioListener& AudioListener::getInstance()
		{
			if(_instance == nullptr)
				throw AudioNotInitializedException();
			return *_instance;
		}

		// AudioDevice
		AudioDevice::AudioDevice()
			: _deviceInfo(Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice())) {}

		AudioDevice::AudioDevice(const PaDeviceInfo* deviceInfo)
			: _deviceInfo(deviceInfo) {}

		const char* AudioDevice::getName() const
		{
			return _deviceInfo->name;
		}

		PaHostApiIndex AudioDevice::getHostAPI() const
		{
			return _deviceInfo->hostApi;
		}

		int AudioDevice::getMaxInputChannels() const
		{
			return _deviceInfo->maxInputChannels;
		}

		int AudioDevice::getMaxOutputChannels() const
		{
			return _deviceInfo->maxOutputChannels;
		}

		PaTime AudioDevice::getDefaultLowInputLatency() const
		{
			return _deviceInfo->defaultLowInputLatency;
		}

		PaTime AudioDevice::getDefaultLowOutputLatency() const
		{
			return _deviceInfo->defaultLowOutputLatency;
		}

		PaTime AudioDevice::getDefaultHighInputLatency() const
		{
			return _deviceInfo->defaultHighInputLatency;
		}

		PaTime AudioDevice::getDefaultHighOutputLatency() const
		{
			return _deviceInfo->defaultHighOutputLatency;
		}

		double AudioDevice::getDefaultSampleRate() const
		{
			return _deviceInfo->defaultSampleRate;
		}

		bool AudioDevice::isInputDevice() const
		{
			return getMaxInputChannels() > 0;
		}

		bool AudioDevice::isOutputDevice() const
		{
			return getMaxOutputChannels() > 0;
		}

		bool AudioDevice::isDefaultOutputDevice() const
		{
			return Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice()) == _deviceInfo;
		}

		bool AudioDevice::isDefaultInputDevice() const
		{
			return Pa_GetDeviceInfo(Pa_GetDefaultInputDevice()) == _deviceInfo;
		}

		// AudioBackend
		AudioBackend::AudioBackend()
		{
			// Starts PortAudio
			catchPAProblem(Pa_Initialize());

			// Gets number of devices
			_numDevices = _calcNumDevices();
			_numOutputDevices = _calcNumOutputDevices();
			_numInputDevices = _calcNumInputDevices();

			// Prints verbose
			AuroraFW::DebugManager::Log("AudioBackend initialized. Num. of "
			"available audio devices: ", _numDevices, " (",
			_numOutputDevices, " output devices, ",
			_numInputDevices, " input devices.)");
		}

		const AudioDevice* AudioBackend::_getDevices()
		{
			int numDevices = getNumDevices();
			AudioDevice* audioDevices = new AudioDevice[numDevices];
			for(int i = 0; i < numDevices; i++) {
				audioDevices[i] = AudioDevice(Pa_GetDeviceInfo(i));
			}

			return const_cast<const AudioDevice*>(audioDevices);
		}

		int AudioBackend::_calcNumOutputDevices()
		{
			int numDevices = getNumDevices();
			const AudioDevice* audioDevices = _getDevices();
			for(int i = 0; i < getNumDevices(); i++) {
				if(!audioDevices[i].isOutputDevice())
					numDevices--;
			}

			delete[] audioDevices;

			return numDevices;
		}

		int AudioBackend::_calcNumInputDevices()
		{
			int numDevices = getNumDevices();
			const AudioDevice* audioDevices = _getDevices();
			for(int i = 0; i < getNumDevices(); i++) {
				if(!audioDevices[i].isInputDevice())
					numDevices--;
			}

			delete[] audioDevices;

			return numDevices;
		}

		#pragma message("TODO: Subject to change, plan changes well and revisit later")
		void AudioBackend::start()
		{
			// Starts the instance if it's not initialized yet
			if(_instance == nullptr) {
				_instance = new AudioBackend();

				// Calls AudioListener's private start method
				AudioListener::_start();
			} else {
				CLI::Log(CLI::Warning, "The AudioBackend was already initialized. "
				"This method shouldn't be called twice!");
			}
		}

		AudioBackend* AudioBackend::_instance = nullptr;

		AudioBackend& AudioBackend::getInstance()
		{
			if(_instance == nullptr)
				throw AudioNotInitializedException();
			return *_instance;
		}

		void AudioBackend::terminate()
		{
			// Safe guard in case someone terminates it when it's already deleted
			if(_instance != nullptr) {
				// Stops PortAudio
				catchPAProblem(Pa_Terminate());

				// Deletes the instance (in case it will be reused again)
				delete _instance;
				_instance = nullptr;

				// Terminates AudioListener
				AudioListener::_stop();

				// Prints verbose
				AuroraFW::DebugManager::Log("AudioBackend was terminated.");
			} else {
				CLI::Log(CLI::Warning, "The AudioBackend was already terminated. "
				"This method shouldn't be called twice!");
			}
		}

		const AudioDevice* AudioBackend::getAllDevices()
		{
			return _getDevices();
		}

		const AudioDevice* AudioBackend::getOutputDevices()
		{
			AudioDevice* audioDevices = new AudioDevice[_numOutputDevices];
			int trueIndex = 0;
			for(int i = 0; i < _numDevices; i++) {
				AudioDevice audioDevice(Pa_GetDeviceInfo(i));
				if(audioDevice.getMaxOutputChannels() > 0) {
					audioDevices[trueIndex] = audioDevice;
					trueIndex++;
				}
			}

			return audioDevices;
		}

		const AudioDevice* AudioBackend::getInputDevices()
		{
			AudioDevice* audioDevices = new AudioDevice[_numInputDevices];
			int trueIndex = 0;
			for(int i = 0; i < _numDevices; i++) {
				AudioDevice audioDevice(Pa_GetDeviceInfo(i));
				if(audioDevice.getMaxInputChannels() > 0) {
					audioDevices[trueIndex] = audioDevice;
					trueIndex++;
				}
			}

			return audioDevices;
		}

		int AudioBackend::_calcNumDevices()
		{
			return Pa_GetDeviceCount();
		}

		void AudioBackend::setInputDevice(const AudioDevice device)
		{
			#pragma message ("TODO: Need to be implemented")
		}

		void AudioBackend::setOutputDevice(const AudioDevice device)
		{
			#pragma message ("TODO: Need to be implemented")
		}
	}
}