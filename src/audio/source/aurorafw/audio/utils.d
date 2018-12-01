/*
								   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2018 Aurora Free Open Source Software.

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

module aurorafw.audio.utils;

import std.string : toStringz;
import std.conv : to;

import aurorafw.core.debugmanager;
import aurorafw.audio.sndfile;
import aurorafw.audio.backend : catchSNDFILEProblem;

class AudioInfo {
	this(SF_INFO* sndInfo = new SF_INFO, SNDFILE* sndFile = null) {
		_sndInfo = sndInfo;
		_sndFile = sndFile;
	}

	~this() {
		if(_sndFile)
			catchSNDFILEProblem(sf_close(_sndFile));
	}

	@property int sampleRate() {
		return _sndInfo.samplerate;
	}

	@property int frames() {
		return cast(int)_sndInfo.frames;
	}

	@property int channels() {
		return _sndInfo.channels;
	}

	@property int format() {
		return _sndInfo.format;
	}

	@property void sampleRate(immutable int sampleRate) {
		_sndInfo.samplerate = sampleRate;
	}

	@property void frames(immutable int frames) {
		_sndInfo.frames = cast(sf_count_t)frames;
	}

	@property void channels(immutable int channels) {
		_sndInfo.channels = channels;
	}

	@property void format(immutable int format) {
		_sndInfo.format = format;
	}

	@property string title() {
		string str = to!string(sf_get_string(_sndFile, SF_STR_TITLE));
		return str ? str : "";
	}

	@property string copyright() {
		string str = to!string(sf_get_string(_sndFile, SF_STR_COPYRIGHT));
		return str ? str : "";
	}

	@property string software() {
		string str = to!string(sf_get_string(_sndFile, SF_STR_SOFTWARE));
		return str ? str : "";
	}

	@property string artist() {
		string str = to!string(sf_get_string(_sndFile, SF_STR_ARTIST));
		return str ? str : "";
	}

	@property string comment() {
		string str = to!string(sf_get_string(_sndFile, SF_STR_COMMENT));
		return str ? str : "";
	}

	@property string date() {
		string str = to!string(sf_get_string(_sndFile, SF_STR_DATE));
		return str ? str : "";
	}

	@property string album() {
		string str = to!string(sf_get_string(_sndFile, SF_STR_ALBUM));
		return str ? str : "";
	}

	@property string license() {
		string str = to!string(sf_get_string(_sndFile, SF_STR_LICENSE));
		return str ? str : "";
	}

	@property string trackNumber() {
		string str = to!string(sf_get_string(_sndFile, SF_STR_TRACKNUMBER));
		return str ? str : "";
	}

	@property string genre() {
		string str = to!string(sf_get_string(_sndFile, SF_STR_GENRE));
		return str ? str : "";
	}

	@property void title(string title) {
		sf_set_string(_sndFile, SF_STR_TITLE, title.toStringz);
	}

	@property void copyright(string copyright) {
		sf_set_string(_sndFile, SF_STR_COPYRIGHT, copyright.toStringz);
	}

	@property void software(string software) {
		sf_set_string(_sndFile, SF_STR_SOFTWARE, software.toStringz);
	}

	@property void artist(string artist) {
		sf_set_string(_sndFile, SF_STR_ARTIST, artist.toStringz);
	}

	@property void comment(string comment) {
		sf_set_string(_sndFile, SF_STR_COMMENT, comment.toStringz);
	}

	@property void date(string date) {
		sf_set_string(_sndFile, SF_STR_DATE, date.toStringz);
	}

	@property void album(string album) {
		sf_set_string(_sndFile, SF_STR_ALBUM, album.toStringz);
	}

	@property void license(string license) {
		sf_set_string(_sndFile, SF_STR_LICENSE, license.toStringz);
	}

	@property void tracknumber(string trackNumber) {
		sf_set_string(_sndFile, SF_STR_TRACKNUMBER, trackNumber.toStringz);
	}

	@property void genre(string genre) {
		sf_set_string(_sndFile, SF_STR_GENRE, genre.toStringz);
	}

	package SF_INFO* _sndInfo;
	package SNDFILE* _sndFile;
}