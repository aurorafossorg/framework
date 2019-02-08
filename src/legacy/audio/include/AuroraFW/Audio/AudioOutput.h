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

/**
 * @file AuroraFW/Audio/AudioOutput.H
 * AudioOutput header. This contains an AudioOStream struct
 * used to handle audio output and some 3D effect classes.
 * @since snapshot20180330
 */

#ifndef AURORAFW_AUDIO_AUDIO_OUTPUT_H
#define AURORAFW_AUDIO_AUDIO_OUTPUT_H

// AuroraFW
#include <AuroraFW/Global.h>
#include <AuroraFW/Audio/AudioBackend.h>
#include <AuroraFW/Audio/AudioUtils.h>
#include <AuroraFW/Math/Algorithm.h>

namespace AuroraFW {
	namespace AudioManager {

		/**
		 * An enum to indicate the desired fallout type for 3D audio.
		 * @since snapshot20180330
		 */
		enum class AudioFallout {
			Linear,		/**< Linear function. */
			Exponential	/**< Exponential function. */
		};

		/**
		 * An enum to indicate the desired play mode for the audio stream.
		 * @since snapshot20180330
		 */
		enum class AudioPlayMode {
			Once,	/**< Play the audio stream once. */
			Loop,	/**< Loop the audio stream. */
		};

		/**
		 * An exception to tell the user the given audio file couldn't be found.
		 * @since snapshot20180330
		 */
		class AFW_API AudioFileNotFound : public std::exception
		{
		private:
			const std::string _errorMessage;
		public:
			AudioFileNotFound(const char* );
			virtual const char* what() const throw();
		};

		/**
		 * A struct representing an audio source. A class that represents an audio source
		 * in 3D space, used to calculate 3D effects.
		 * @since snapshot20180330
		 */
		struct AFW_API AudioSource {

			/**
			 * Constructs an AudioSource at (0, 0, 0) coordinates.
			 * @see AudioSource(const Math::Vector3D )
			 * @see AudioSource(const float , const float , const float )
			 * @since snapshot20180330
			 */
			AudioSource();

			/**
			 * Constructs an AudioSource at the coordinates of the given vector.
			 * @param vec The Vector3D indicating the coordinates.
			 * @see AudioSource()
			 * @see AudioSource(const float , const float , const float )
			 * @since snapshot20180330
			 */
			AudioSource(const Math::Vector3D);

			/**
			 * Constructs an AudioSource at the coordinates given by the three variables.
			 * @param xyz The 3D coordinates for, respectively, X, Y and Z axis.
			 * @see AudioSource()
			 * @see AudioSource(const Math::Vector3D )
			 * @since snapshot20180330
			 */
			AudioSource(const float , const float , const float );

			/**
			 * Copy constructor
			 * @since snapshot20180330
			 */
			AudioSource(const AudioSource& );

			/**
			 * The desired AudioFallout type
			 * @since snapshot20180330
			 */
			AudioFallout falloutType;

			/**
			 * Sets the position of the audio source.
			 * @param position The Vector3D indicating the new coordinates.
			 * @since snapshot20180330
			 */
			void setPosition(Math::Vector3D );

			/**
			 * Sets the medium distance, specified in WU: it defines at which distance the sound
			 * loses it's strength to 50%
			 * @param medDistance The medium distance from the source's center.
			 * @see setMaxDistance(float )
			 * @since snapshot20180330
			 */
			void setMedDistance(float );

			/**
			 * Sets the maximum distance, specified in WU: it defines the distance at which
			 * the sound will no longer be audible.
			 * @param maxDistance The maximum distance from the source's center.
			 * @see setMedDistance(float )
			 * @since snapshot20180330
			 */
			void setMaxDistance(float );

			/**
			 * Gets the calculated panning for the 3D effect.
			 * @return A value between -1 and 1: -1 means only audible on the left ear; 1 mean only audible on the right ear; 0 means an equilibrium between the two ears.
			 * @see getStrength()
			 * @since snapshot20180330
			 */
			float getPanning();

			/**
			 * Gets the calculated strength of the audio source.
			 * @return A value between 0 and 1: 1 means maximum strength; 0 means the audio is inaudible.
			 * @see getPanning()
			 * @since snapshot20180330
			 */
			float getStrength();

			/**
			 * Gets the audio source's position.
			 * @return The Vector3D representing the 3D coordinates.
			 * @since snapshot20180330
			 */
			Math::Vector3D getPosition();

			/**
			 * Gets the medium distance for the audio source.
			 * @return The medium distance from the source's center.
			 * @see getMaxDistance()
			 * @since snapshot20180330
			 */
			float getMedDistance();

			/**
			 * Gets the maximum distance for the audio source.
			 * @return The maximum distance from the source's center.
			 * @see getMedDistance()
			 * @since snapshot20180330
			 */
			float getMaxDistance();

			/**
			 * Notifies the system that the user changed some 3D values, and recalculates the 3D effect.
			 * @note You only need to call this method if you changed any 3D value using local methods; the values given in the constructor are calculated automatically.
			 * @since snapshot20180330
			 */
			void calculateValues();

		private:
			void _calculatePan();
			void _calculateStrength();

			Math::Vector3D _position;
			float _medDistance;
			float _maxDistance;

			float _strength = 1;
			float _pan = 0;
		};

		/**
		 * A struct representing an audio output stream. A struct that allows a user to
		 * open an audio file and play it.
		 * @since snapshot20180330
		 */
		struct AFW_API AudioOStream {
			friend struct AudioSource;
			friend int audioOutputCallback(const void* , void* , size_t ,
			const PaStreamCallbackTimeInfo* , PaStreamCallbackFlags , void* );

			/**
			 * Constructs a debug AudioOStream, which plays a "sawtooth" stereo wave.
			 * @see AudioOStream(const char* , AudioSource* , bool )
			 * @since snapshot20180330
			 */
			AudioOStream();

			/**
			 * Constructs an AudioOStream with the specified file.
			 * @param path The path of the file to be played. (including the file's extension)
			 * @param audioSource An AudioSource object to add a 3D effect to this audio stream. (default = none)
			 * @param buffered Specifies whether this audio stream should be pre-buffered on memory or streamed from disk. (default = false)
			 * @throws AudioFileNotFound In case it couldn't locate or read the audio file.
			 * @throws PAErrorException In case there was a PortAudio error.
			 * @see AudioOStream()
			 * @since snapshot20180330
			 */
			AudioOStream(const char* , AudioSource* = nullptr, bool = false);

			/**
			 * Destruct an AudioOStream object.
			 * @since snapshot20180330
			 */
			~AudioOStream();

			/**
			 * Starts playing this audio stream.
			 * @throws PAErrorException In case there was a PortAudio error.
			 * @see pause()
			 * @see stop()
			 * @since snapshot20180330
			 */
			void play();

			/**
			 * Pauses this audio stream.
			 * @throws PAErrorException In case there was a PortAudio error.
			 * @see play()
			 * @see stop()
			 * @since snapshot20180330
			 */
			void pause();

			/**
			 * Stops this audio stream, resetting it's read position to 0.
			 * @throws PAErrorException In case there was a PortAudio error.
			 * @see play()
			 * @see pause()
			 * @since snapshot20180330
			 */
			void stop();

			/**
			 * Returns whether the stream is currently being played.
			 * @return <em>true</em> if the stream is being currently played. <em>false</em> otherwise.
			 * @see isPaused()
			 * @see isStopped()
			 * @since snapshot20180330
			 */
			bool isPlaying();

			/**
			 * Returns whether the stream is currently paused.
			 * @return <em>true</em> if the stream is currently paused. <em>false</em> otherwise.
			 * @note If the stream is stopped, it doesn't count as being paused.
			 * @see isPlaying()
			 * @see isStopped()
			 * @since snapshot20180330
			 */
			bool isPaused();

			/**
			 * Returns whether the stream is currently stopped and not just paused.
			 * @return <em>true</em> if the stream is currently stopped <em>false</em> otherwise.
			 * @see isPlaying()
			 * @see isPaused()
			 * @since snapshot20180330
			 */
			bool isStopped();

			/**
			 * Sets the stream's read position to the given value in seconds.
			 * @param pos The position from the start in seconds.
			 * @see setStreamPosFrame(unsigned int )
			 * @since snapshot20180330
			 */
			void setStreamPos(unsigned int );

			/**
			 * Sets the stream's read position to the given frame, without counting in the number of channels.
			 * @param pos The position from the start in frames.
			 * @see setStreamPos(unsigned int )
			 * @since snapshot20180330
			 */
			void setStreamPosFrame(unsigned int );

			/**
			 * Returns a pointer for the AudioSource, it there's any.
			 * @return A pointer to this stream AudioSource. `nullptr` in case this effect wasn't added.
			 * @see setAudioSource(const AudioSource& )
			 * @since snapshot20180330
			 */
			AudioSource* getAudioSource();

			/**
			 * Sets the current AudioSource to the given one. If this stream had a source before, it's discarded.
			 * @param audioSource The AudioSource object desired.
			 * @see getAudioSource()
			 * @since snapshot20180330
			 */
			void setAudioSource(const AudioSource& );

			/**
			 * Gets the number of loops this stream did already.
			 * @return The number of completed loops. -1 if the AudioPlayMode is set to <em>Once</em>
			 * @since snapshot20180330
			 */
			float getNumLoops();

			/**
			 * Gets the current CPU load this stream is causing.
			 * @return A value ranging from 0 to 100 representing this stream's CPU load.
			 * @since snapshot20180330
			 */
			float getCpuLoad();

			/**
			 * The stream's AudioPlayMode.
			 * @since snapshot20180330
			 */
			AudioPlayMode audioPlayMode;

			/**
			 * The stream's AudioInfo.
			 * @since snapshot20180330
			 */
			AudioInfo audioInfo;

			/**
			 * The stream's volume. Can be set to any value, but ideally shoudl be set between 0 and 1.
			 * @since snapshot20180330
			 */
			float volume = 1;

			#pragma message("TODO: Need to implement pitch")
			/**
			 * The stream's pitch. To be implemented...
			 * @since snapshot20180330
			 */
			float pitch = 1;

		private:
			PaStream* _paStream;

			float* _buffer = nullptr;
			unsigned int _streamPosFrame = 0;
			uint8_t _loops = 0;
			
			AudioSource* _audioSource;
		};
		
		int debugCallback(const void* , void* , size_t ,
		const PaStreamCallbackTimeInfo* , PaStreamCallbackFlags , void* );

		// Inline definitions
		inline float AudioOStream::getNumLoops()
		{
			return audioPlayMode == AudioPlayMode::Loop ? _loops : -1;
		}
	}
}

#endif // AURORAFW_AUDIO_AUDIO_OUTPUT_H