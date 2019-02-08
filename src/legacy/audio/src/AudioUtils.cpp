/*****************************************************************************
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

#include <AuroraFW/Audio/AudioUtils.h>
#include <AuroraFW/Audio/AudioBackend.h>

namespace AuroraFW {
	namespace AudioManager {
		// AudioInfo
		AudioInfo::AudioInfo(SF_INFO* sndInfo, SNDFILE* sndFile)
			: _sndInfo(sndInfo), _sndFile(sndFile)
		{}

		AudioInfo::~AudioInfo()
		{
			// NOTE: _sndInfo is deleted internally by libSNDFile
			if(_sndFile != AFW_NULLPTR)
				catchSNDFILEProblem(sf_close(_sndFile));

			delete _sndInfo;
		}

		int AudioInfo::getSampleRate() const
		{
			return _sndInfo->samplerate;
		}

		sf_count_t AudioInfo::getFrames() const
		{
			return _sndInfo->frames;
		}

		int AudioInfo::getChannels() const
		{
			return _sndInfo->channels;
		}

		int AudioInfo::getFormat() const
		{
			return _sndInfo->format;
		}

		void AudioInfo::setSampleRate(const int samplerate)
		{
			_sndInfo->samplerate = samplerate;
		}

		void AudioInfo::setFrames(const sf_count_t frames)
		{
			_sndInfo->frames = frames;
		}

		void AudioInfo::setChannels(const int channels)
		{
			_sndInfo->channels = channels;
		}

		void AudioInfo::setFormat(const int format)
		{
			_sndInfo->format = format;
		}

		const char* AudioInfo::getTitle() const
		{
			const char* string = sf_get_string(_sndFile, SF_STR_TITLE);
			return string ? string : "null";
		}

		const char* AudioInfo::getCopyright() const
		{
			const char* string = sf_get_string(_sndFile, SF_STR_COPYRIGHT);
			return string ? string : "null";
		}

		const char* AudioInfo::getSoftware() const
		{
			const char* string = sf_get_string(_sndFile, SF_STR_SOFTWARE);
			return string ? string : "null";
		}

		const char* AudioInfo::getArtist() const
		{
			const char* string = sf_get_string(_sndFile, SF_STR_ARTIST);
			return string ? string : "null";
		}

		const char* AudioInfo::getComment() const
		{
			const char* string = sf_get_string(_sndFile, SF_STR_COMMENT);
			return string ? string : "null";
		}

		const char* AudioInfo::getDate() const
		{
			const char* string = sf_get_string(_sndFile, SF_STR_DATE);
			return string ? string : "null";
		}

		const char* AudioInfo::getAlbum() const
		{
			const char* string = sf_get_string(_sndFile, SF_STR_ALBUM);
			return string ? string : "null";
		}

		const char* AudioInfo::getLicense() const
		{
			const char* string = sf_get_string(_sndFile, SF_STR_LICENSE);
			return string ? string : "null";
		}

		const char* AudioInfo::getTrackNumber() const
		{
			const char* string = sf_get_string(_sndFile, SF_STR_TRACKNUMBER);
			return string ? string : "null";
		}

		const char* AudioInfo::getGenre() const
		{
			const char* string = sf_get_string(_sndFile, SF_STR_GENRE);
			return string ? string : "null";
		}

		void AudioInfo::setTitle(const char* title)
		{
			sf_set_string(_sndFile, SF_STR_TITLE, title);
		}

		void AudioInfo::setCopyright(const char* copyright)
		{
			sf_set_string(_sndFile, SF_STR_COPYRIGHT, copyright);
		}

		void AudioInfo::setSoftware(const char* software)
		{
			sf_set_string(_sndFile, SF_STR_SOFTWARE, software);
		}

		void AudioInfo::setArtist(const char* artist)
		{
			sf_set_string(_sndFile, SF_STR_ARTIST, artist);
		}

		void AudioInfo::setComment(const char* comment)
		{
			sf_set_string(_sndFile, SF_STR_COMMENT, comment);
		}

		void AudioInfo::setDate(const char* date)
		{
			sf_set_string(_sndFile, SF_STR_DATE, date);
		}

		void AudioInfo::setAlbum(const char* album)
		{
			sf_set_string(_sndFile, SF_STR_ALBUM, album);
		}

		void AudioInfo::setLicense(const char* license)
		{
			sf_set_string(_sndFile, SF_STR_LICENSE, license);
		}

		void AudioInfo::setTrackNumber(const char* trackNumber)
		{
			sf_set_string(_sndFile, SF_STR_TRACKNUMBER, trackNumber);
		}

		void AudioInfo::setGenre(const char* genre)
		{
			sf_set_string(_sndFile, SF_STR_GENRE, genre);
		}
	}
}
