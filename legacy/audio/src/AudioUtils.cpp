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
