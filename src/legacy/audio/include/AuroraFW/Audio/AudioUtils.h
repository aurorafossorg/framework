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
 * @file AuroraFW/Audio/AudioUtils.h
 * AudioUtils header. This contains some
 * classes useful for the audio module.
 */

#ifndef AURORAFW_AUDIO_AUDIOUTILS_H
#define AURORAFW_AUDIO_AUDIOUTILS_H

// AuroraFW
#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

// LibSNDFile
#include <sndfile.h>

// PortAudio
#include <portaudio.h>

namespace AuroraFW {
	namespace AudioManager {
		/**
		 * A struct to hold audio info. A struct whose purpose is to store all the information
		 * about an audio stream/file, either technical (samplerate, channels, etc...) or
		 * additional. (title, artist, album, etc...)
		 * @since snapshot20180330
		 */
		struct AFW_API AudioInfo {
			friend struct AudioOStream;
			friend struct AudioIStream;
			friend int audioOutputCallback(const void* , void* , size_t ,
			const PaStreamCallbackTimeInfo* , PaStreamCallbackFlags , void* );

			/**
			 * Constructs an AudioInfo object, either with empty information or with already existing one.
			 * @param sndInfo The <em>libsndfile</em> info object, in case the user already has one (default = new empty object)
			 * @param sndFile The <em>libsndfile</em> file object, in case the user already has one (default = nullptr)
			 * @since snapshot20180330
			 */
			AudioInfo(SF_INFO* = new SF_INFO(), SNDFILE* = nullptr);

			/**
			 * Destructs an AudioInfo object.
			 * @since snapshot20180330
			 */
			~AudioInfo();

			/**
			 * Gets the sample rate of the audio file.
			 * @return The sample rate of the audio file.
			 * @see setSampleRate(const int )
			 * @since snapshot20180330
			 */
			int getSampleRate() const;

			/**
			 * Gets the number of frames of the audio file.
			 * @return The number of frames of the audio file, without counting in the number of channels.
			 * @see setFrames(const sf_count_t )
			 * @since snapshot20180330
			 */
			sf_count_t getFrames() const;

			/**
			 * Gets the number of channels of the audio file.
			 * @return The number of channels of the audio file.
			 * @see setChannels(const int )
			 * @since snapshot20180330
			 */
			int getChannels() const;

			/**
			 * Gets the format of the audio file.
			 * The format is the result of a bit-wise operation between a major and minor value
			 * from <em>libsndfile</em>. More info on this on the lib's
			 * <a href="http://www.mega-nerd.com/libsndfile/api.html#open">API page</a>.
			 * @return The format as an int resulting from bit-wise operations.
			 * @see setFormat(const int )
			 * @since snapshot20180330
			 */
			int getFormat() const;

			/**
			 * Sets the samplerate of the audio file.
			 * @param samplerate The desired samplerato.
			 * @see getSamplerate()
			 * @since snapshot20180330
			 */
			void setSampleRate(const int );

			/**
			 * Sets the number of frames of the audio file.
			 * @param frames The desired number of frames, without counting in the number of channels.
			 * @see getFrames()
			 * @since snapshot20180330
			 */
			void setFrames(const sf_count_t );

			/**
			 * Sets the number of channels of the audio file.
			 * @param channels The desired number of channels.
			 * @see getChannels()
			 * @since snapshot20180330
			 */
			void setChannels(const int );

			/**
			 * Sets the format of the audio file.
			 * The format must be the result of a bit-wise operation between a major and minor value
			 * from <em>libsndfile</em>. More info on this on the lib's
			 * <a href="http://www.mega-nerd.com/libsndfile/api.html#open">API page</a>.
			 * @param format The desired format
			 * @see getFormat()
			 * @since snapshot20180330
			 */
			void setFormat(const int );

			/**
			 * Gets the "Title" string of the audio file.
			 * @return A string containing the data, or <em>"null"</em> if there's no data.
			 * @see setTitle(const char* )
			 * @since snapshot20180330
			 */
			const char* getTitle() const;

			/**
			 * Gets the "Copyright" string of the audio file.
			 * @return A string containing the data, or <em>"null"</em> if there's no data.
			 * @see setCopyright(const char* )
			 * @since snapshot20180330
			 */
			const char* getCopyright() const;

			/**
			 * Gets the "Software" string of the audio file.
			 * @return A string containing the data, or <em>"null"</em> if there's no data.
			 * @see setSoftware(const char* )
			 * @since snapshot20180330
			 */
			const char* getSoftware() const;

			/**
			 * Gets the "Artist" string of the audio file.
			 * @return A string containing the data, or <em>"null"</em> if there's no data.
			 * @see setArtist(const char* )
			 * @since snapshot20180330
			 */
			const char* getArtist() const;

			/**
			 * Gets the "Comment" string of the audio file.
			 * @return A string containing the data, or <em>"null"</em> if there's no data.
			 * @see setComment(const char* )
			 * @since snapshot20180330
			 */
			const char* getComment() const;

			/**
			 * Gets the "Date" string of the audio file.
			 * @return A string containing the data, or <em>"null"</em> if there's no data.
			 * @see setDate(const char* )
			 * @since snapshot20180330
			 */
			const char* getDate() const;

			/**
			 * Gets the "Album" string of the audio file.
			 * @return A string containing the data, or <em>"null"</em> if there's no data.
			 * @see setAlbum(const char* )
			 * @since snapshot20180330
			 */
			const char* getAlbum() const;

			/**
			 * Gets the "License" string of the audio file.
			 * @return A string containing the data, or <em>"null"</em> if there's no data.
			 * @see setLicense(const char* )
			 * @since snapshot20180330
			 */
			const char* getLicense() const;

			/**
			 * Gets the "TrackNumber" string of the audio file.
			 * @return A string containing the data, or <em>"null"</em> if there's no data.
			 * @see setTrackNumber(const char* )
			 * @since snapshot20180330
			 */
			const char* getTrackNumber() const;

			/**
			 * Gets the "Genre" string of the audio file.
			 * @return A string containing the data, or <em>"null"</em> if there's no data.
			 * @see setGenre(const char* )
			 * @since snapshot20180330
			 */
			const char* getGenre() const;

			/**
			 * Sets the "Title" string of the audio file to the given string.
			 * @param title The desired string
			 * @see getTitle()
			 * @since snapshot20180330
			 */
			void setTitle(const char* title);

			/**
			 * Sets the "Copyright" string of the audio file to the given string.
			 * @param copyright The desired string
			 * @see getCopyright()
			 * @since snapshot20180330
			 */
			void setCopyright(const char* copyright);

			/**
			 * Sets the "Software" string of the audio file to the given string.
			 * @param software The desired string
			 * @see getSoftware()
			 * @since snapshot20180330
			 */
			void setSoftware(const char* software);

			/**
			 * Sets the "Artist" string of the audio file to the given string.
			 * @param artist The desired string
			 * @see getArtist()
			 * @since snapshot20180330
			 */
			void setArtist(const char* artist);

			/**
			 * Sets the "Comment" string of the audio file to the given string.
			 * @param comment The desired string
			 * @see getComment()
			 * @since snapshot20180330
			 */
			void setComment(const char* comment);

			/**
			 * Sets the "Date" string of the audio file to the given string.
			 * @param date The desired string
			 * @see getDate()
			 * @since snapshot20180330
			 */
			void setDate(const char* date);

			/**
			 * Sets the "Album" string of the audio file to the given string.
			 * @param album The desired string
			 * @see getAlbum()
			 * @since snapshot20180330
			 */
			void setAlbum(const char* album);

			/**
			 * Sets the "License" string of the audio file to the given string.
			 * @param license The desired string
			 * @see getLicense()
			 * @since snapshot20180330
			 */
			void setLicense(const char* license);

			/**
			 * Sets the "TrackNumber" string of the audio file to the given string.
			 * @param trackNumber The desired string
			 * @see getTrackNumber()
			 * @since snapshot20180330
			 */
			void setTrackNumber(const char* trackNumber);

			/**
			 * Sets the "Genre" string of the audio file to the given string.
			 * @param genre The desired string
			 * @see getGenre()
			 * @since snapshot20180330
			 */
			void setGenre(const char* genre);
		
		private:
			SF_INFO* _sndInfo;
			SNDFILE* _sndFile;
		};
	}
}

#endif // AURORAFW_AUDIO_AUDIO_UTILS_H