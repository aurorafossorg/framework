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

/**
 * @file AuroraFW/Audio/AudioBackend.h
 * AudioBackend header. This contains some
 * classes handled internally to process
 * audio data.
 */

#ifndef AURORAFW_AUDIO_AUDIOBACKEND_H
#define AURORAFW_AUDIO_AUDIOBACKEND_H

// AuroraFW
#include <AuroraFW/Global.h>
#include <AuroraFW/STDL/STL/IOStream.h>
#include <AuroraFW/Core/DebugManager.h>
#include <AuroraFW/CLI/Log.h>
#include <AuroraFW/Math/Vector3D.h>

// PortAudio
#include <portaudio.h>

// LibSNDFile
#include <sndfile.h>

// STD
#include <exception>

namespace AuroraFW {
	namespace AudioManager {

		/**
		 * An exception to tell the user that an internal <em>PortAudio</em> error ocurred.
		 * @since snapshot20180330
		 */
		class AFW_API PAErrorException : public std::exception
		{
		private:
			const std::string _paError;
		public:
			PAErrorException(const PaError& );
			virtual const char* what() const throw();
		};

		/**
		 * An exception to tell the user than an internal <em>libSNDFile</em> error ocurred.
		 * @since snapshot20180330
		 */
		class AFW_API SNDFILEErrorException : public std::exception
		{
		private:
			const std::string _sndFileError;
		public:
			SNDFILEErrorException(const int& );
			virtual const char* what() const throw();
		};

		/**
		 * An exception to tell the user that there was an attempt to process
		 * audio data without the backend having initialized yet.
		 * @since snapshot20180330
		 */
		class AFW_API AudioNotInitializedException : public std::exception
		{
		public:
			AudioNotInitializedException() {};
			virtual const char* what() const throw();
		};

		/**
		 * A struct representing an audio device. A struct that represents a
		 * pyhsical audio device and has some helper methods.
		 */
		struct AFW_API AudioDevice {
			/**
			 * Constructs an AudioDevice with the system's default audio device.
			 * @see AudioDevice(const PaDeviceInfo* )
			 * @since snapshot20180330
			 */
			AudioDevice();

			/**
			 * Constructs an AudioDevice with the desired audio device's info (from <em>PortAudio</em>).
			 * @param deviceInfo The <em>PortAudio</em>'s audio device info.
			 * @see AudioDevice()
			 * @since snapshot20180330
			 */
			AudioDevice(const PaDeviceInfo* );

			/**
			 * Destructs an AudioDevice.
			 * @since snapshot20180330
			 */
			~AudioDevice() {};

			/**
			 * Gets the name of the audio device.
			 * @return String containing the name of the device.
			 * @since snapshot20180330
			 */
			const char* getName() const;

			/**
			 * Gets the current host API for this audio device.
			 * @return An index of the host API (<em><a href="http://www.portaudio.com/docs/v19-doxydocs/api_overview.html">See PortAudio's docs</a></em>)
			 * @since snapshot20180330
			 */
			PaHostApiIndex getHostAPI() const;

			/**
			 * Gets the maximum number of input channels this audio device supports.
			 * @return The max number of input channels.
			 * @see getMaxOutputChannels()
			 * @since snapshot20180330
			 */
			int getMaxInputChannels() const;

			/**
			 * Gets the maximum number of output channels this audio device supports.
			 * @return The max number of output channels.
			 * @see getMaxInputChannels()
			 * @since snapshot20180330
			 */
			int getMaxOutputChannels() const;

			/**
			 * Gets the low-level input latency for this audio device.
			 * @return The low-level input latency.
			 * @see getDefaultHighInputLatency()
			 * @since snapshot20180330
			 */
			PaTime getDefaultLowInputLatency() const;

			/**
			 * Gets the low-level output latency for this audio device.
			 * @return The low-level output latency.
			 * @see getDefaultHighOutputLatency()
			 * @since snapshot20180330
			 */
			PaTime getDefaultLowOutputLatency() const;

			/**
			 * Gets the high-level input latency for this audio device.
			 * @return The high-level input latency.
			 * @see getDefaultLowInputLatency()
			 * @since snapshot20180330
			 */
			PaTime getDefaultHighInputLatency() const;

			/**
			 * Gets the high-level output latency for this audio device.
			 * @return The high-level output latency.
			 * @see getDefaultLowOutputLatency()
			 * @since snapshot20180330
			 */
			PaTime getDefaultHighOutputLatency() const;

			/**
			 * Gets the default sample rate for this audio device.
			 * @return The default sample rate of this device.
			 * @since snapshot20180330
			 */
			double getDefaultSampleRate() const;

			/**
			 * Checks if this audio device can record audio.
			 * @return <em>true</em> if this AudioDevice has any input channels. <em>false</em> otherwise.
			 * @see isOutputDevice()
			 * @since snapshot20180330
			 */
			bool isInputDevice() const;

			/**
			 * Checks if this audio device can play audio.
			 * @return <em>true</em> if this AudioDevice has any output channels. <em>false</em> otherwise.
			 * @see isInputDevice()
			 * @since snapshot20180330
			 */
			bool isOutputDevice() const;

			/**
			 * Checks if this AudioDevice is the system's default output audio device.
			 * @return <em>true</em> if this device is the system's default output device. <em>false</em> otherwise.
			 * @see isDefaultInputDevice()
			 * @since snapshot20180330
			 */
			bool isDefaultOutputDevice() const;

			/**
			 * Checks if this AudioDevice is the system's default input audio device.
			 * @return <em>true</em> if this device is the system's default input device. <em>false</em> otherwise.
			 * @see isDefaultOutputDevice()
			 * @since snapshot20180330
			 */
			bool isDefaultInputDevice() const;

		private:
			const PaDeviceInfo *_deviceInfo;
		};

		/**
		 * A singleton struct representing an audio listener.
		 * A singleton struct that represents an audio listener in 3D space, used for 3D effects.
		 * @since snapshot20180330
		 */
		class AFW_API AudioListener {
			private:
				static AudioListener *_instance;
				AudioListener() {};

				static void _start();
				static void _stop();
			public:
				friend struct AudioBackend;

				/**
				 * AudioListener destructor.
				 * Doesn't do anything, the AudioListener is handled by the AudioBackend, to prevent accidental deletions.
				 * @since snapshot20180330
				 */
				~AudioListener() {};

				/**
				 * The singleton's getIntance() method to get access to the AudioListener.
				 * @since snapshot20180330
				 */
				static AudioListener& getInstance();

				/**
				 * The listener's 3D position. Default is at the center. (0, 0, 0)
				 * @see direction
				 * @since snapshot20180330
				 */
				Math::Vector3D position;

				/**
				 * The listener's 3D direction. Default is looking at negative Z-axis. (0, 0, -1)
				 * @see position
				 * @since snapshot20180330
				 */
				Math::Vector3D direction = Math::Vector3D(0, 0, -1);
		};

		/**
		 * A singleton class representing the audio backend.
		 * A singleton class with the function of handling all the
		 * audio processing and settings.
		 * @since snapshot20180330
		 */
		class AFW_API AudioBackend {
		private:
			static AudioBackend *_instance;
			AudioBackend();

			const AudioDevice* _getDevices();

			int _calcNumOutputDevices();
			int _calcNumDevices();
			int _calcNumInputDevices();

			int _numDevices;
			int _numOutputDevices;
			int _numInputDevices;

		public:
			/**
			 * AudioBackend destructor.
			 * Doesn't do anything, to prevent accidental deletions. To terminate it, you must call terminate().
			 * @since snapshot20180330
			 */
			~AudioBackend() {};

			/**
			 * Starts the AudioBackend instance, making it ready to process audio.
			 * @throws PAErrorException In case there was a <em>PortAudio</em> error.
			 * @note Every call to start() should be followed by a terminate(), to ensure the backend is closed before the app leaves.
			 * @warning Do not call start() when it's started already. You can check if it's started already by calling getInstance(), which should return a non-null pointer.
			 * @see terminate()
			 * @since snapshot20180330
			 */
			static void start();

			/**
			 * The singleton's getIntance() method to get access to the AudioListener.
			 * @throws AudioNotInitializedException In case the AudioBackend wasn't initialized when this is called.
			 * @return A valid AudioListener instance, if is initialized.
			 * @since snapshot20180330
			 */
			static AudioBackend& getInstance();

			/**
			 * Terminates the AudioBackend instance, signaling no more audio is needed.
			 * @throws PAErrorException In case there was a <em>PortAudio</em> error.
			 * @note Every call to start() should be followed by a terminate(), to ensure the backend is closed before the app leaves.
			 * @warning Do not call terminate() when it's terminated already. You can check if it's started already by calling getInstance(), which should return a null pointer.
			 * @see start()
			 * @since snapshot20180330
			 */
			static void terminate();

			/**
			 * Gets an array containing all the audio devices.
			 * Use the getNumDevices() method to get the size of the array.
			 * @return A pointer containing all AudioDevices.
			 * @since snapshot20180330
			 */
			const AudioDevice* getAllDevices();

			/**
			 * Gets an array containing all the output audio devices.
			 * Use the getNumOutputDevices() method to get the size of the array.
			 * @return A pointer containing all output AudioDevices.
			 * @see getInputDevices()
			 * @since snapshot20180330
			 */
			const AudioDevice* getOutputDevices();

			/**
			 * Gets an array containing all the input audio devices.
			 * Use the getNumInputDevices() method to get the size of the array.
			 * @return A pointer containing all input AudioDevices.
			 * @see getOutputDevices()
			 * @since snapshot20180330
			 */
			const AudioDevice* getInputDevices();

			/**
			 * Sets the backend input device to the one given.
			 * @param device The desired AudioDevice
			 * @warning The given device must have input channels, or an error will occur.
			 * @see setOutputDevice(AudioDevice )
			 * @since snapshot20180330
			 */
			void setInputDevice(AudioDevice );

			/**
			 * Sets the backend output device to the one given.
			 * @param device The desired AudioDevice
			 * @warning The given device must have output channels, or an error will occur.
			 * @see setInputDevice(AudioDevice )
			 * @since snapshot20180330
			 */
			void setOutputDevice(AudioDevice );

			/**
			 * Gets the total number of audio devices available.
			 * @return The number of all audio devices available.
			 * @since snapshot20180330
			 */
			int getNumDevices();

			/**
			 * Gets the total number of output audio devices available.
			 * @return The number of output devices available.
			 * @see getNumInputDevices()
			 * @since snapshot20180330
			 */
			int getNumOutputDevices();

			/**
			 * Gets the total number of input audio devices available.
			 * @return The number of input devices available.
			 * @see getNumOutputDevices()
			 * @since snapshot20180330
			 */
			int getNumInputDevices();

			/**
			 * The global volume for all output audio.
			 * Ideally, it should only range from 0 to 1.
			 * @since snapshot20180330
			 */
			float globalVolume = 1;
		};

		// Inline definitions
		inline void catchPAProblem(const PaError& error)
		{
			if(error != paNoError)
				throw PAErrorException(error);
		}

		inline void catchSNDFILEProblem(const int& error)
		{
			if(error != SF_ERR_NO_ERROR)
				throw SNDFILEErrorException(error);
		}

		inline int AudioBackend::getNumDevices()
		{
			return _numDevices;
		}

		inline int AudioBackend::getNumOutputDevices()
		{
			return _numOutputDevices;
		}
		
		inline int AudioBackend::getNumInputDevices()
		{
			return _numInputDevices;
		}
	}
}

#endif // AURORAFW_AUDIO_AUDIOBACKEND_H