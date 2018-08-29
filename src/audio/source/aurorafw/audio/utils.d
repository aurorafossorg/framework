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

import aurorafw.core.debugmanager;

class AudioInfo {
	this(/*SF_INFO* sndInfo = new SF_INFO, SNDFILE* sndFile = null*/) {
		/*
		_sndInfo = sndinfo;
		_sndFile = sndFile;
		*/
	}

	~this() {
		/*
		if(_sndFile)
			catchSNDFILEProblem(sf_close(_sndFile));
		*/
	}

	@property int sampleRate() {
		pragma(msg, debugMsgPrefix, "TODO: Implement sampleRate getter");
		// return _sndInfo.samplerate;
		return 0;
	}

	@property /*sf_count_t*/int frames() {
		pragma(msg, debugMsgPrefix, "TODO: Implement frames getter");
		// return _sndInfo.frames;
		return 0;
	}

	@property int channels() {
		pragma(msg, debugMsgPrefix, "TODO: Implement channels getter");
		// return _sndInfo.channels;
		return 0;
	}

	@property int format() {
		pragma(msg, debugMsgPrefix, "TODO: Implement format getter");
		// return _sndInfo.format;
		return 0;
	}

	@property void sampleRate(immutable int sampleRate) {
		// _sndInfo.samplerate = sampleRate;
		pragma(msg, debugMsgPrefix, "TODO: Implement sampleRate setter");
	}

	@property void frames(immutable /*sf_count_t*/ int frames) {
		// _sndInfo.frames = frames;
		pragma(msg, debugMsgPrefix, "TODO: Implement frames setter");
	}

	@property void channels(immutable int channels) {
		// _sndInfo.channels = channels;
		pragma(msg, debugMsgPrefix, "TODO: Implement channels setter");
	}

	@property void format(immutable int format) {
		// _sndInfo.format = format;
		pragma(msg, debugMsgPrefix, "TODO: Implement format setter");
	}

	@property string title() {
		/*
		string str = sf_get_string(_sndFile, SF_STR_TITLE);
		return str ? str : "";
		*/
		return "null";
		pragma(msg, debugMsgPrefix, "TODO: Implement title getter");
	}

	@property string copyright() {
		/*
		string str = sf_get_string(_sndFile, SF_STR_COPYRIGHT);
		return str ? str : "";
		*/
		return "null";
		pragma(msg, debugMsgPrefix, "TODO: Implement copyright getter");
	}

	@property string software() {
		/*
		string str = sf_get_string(_sndFile, SF_STR_SOFTWARE);
		return str ? str : "";
		*/
		return "null";
		pragma(msg, debugMsgPrefix, "TODO: Implement software getter");
	}

	@property string artist() {
		/*
		string str = sf_get_string(_sndFile, SF_STR_ARTIST);
		return str ? str : "";
		*/
		return "null";
		pragma(msg, debugMsgPrefix, "TODO: Implement artist getter");
	}

	@property string comment() {
		/*
		string str = sf_get_string(_sndFile, SF_STR_COMMENT);
		return str ? str : "";
		*/
		return "null";
		pragma(msg, debugMsgPrefix, "TODO: Implement comment getter");
	}

	@property string date() {
		/*
		string str = sf_get_string(_sndFile, SF_STR_DATE);
		return str ? str : "";
		*/
		return "null";
		pragma(msg, debugMsgPrefix, "TODO: Implement date getter");
	}

	@property string album() {
		/*
		string str = sf_get_string(_sndFile, SF_STR_ALBUM);
		return str ? str : "";
		*/
		return "null";
		pragma(msg, debugMsgPrefix, "TODO: Implement album getter");
	}

	@property string license() {
		/*
		string str = sf_get_string(_sndFile, SF_STR_LICENSE);
		return str ? str : "";
		*/
		return "null";
		pragma(msg, debugMsgPrefix, "TODO: Implement license getter");
	}

	@property string trackNumber() {
		/*
		string str = sf_get_string(_sndFile, SF_STR_TRACKNUMBER);
		return str ? str : "";
		*/
		return "null";
		pragma(msg, debugMsgPrefix, "TODO: Implement trackNumber getter");
	}

	@property string genre() {
		/*
		string str = sf_get_string(_sndFile, SF_STR_GENRE);
		return str ? str : "";
		*/
		return "null";
		pragma(msg, debugMsgPrefix, "TODO: Implement genre getter");
	}

	@property void title(string title) {
		// sf_set_string(_sndFile, SF_STR_TITLE, title);
		pragma(msg, debugMsgPrefix, "TODO: Implement title setter");
	}

	@property void copyright(string copyright) {
		// sf_set_string(_sndFile, SF_STR_COPYRIGHT, copyright);
		pragma(msg, debugMsgPrefix, "TODO: Implement copyright setter");
	}

	@property void software(string software) {
		// sf_set_string(_sndFile, SF_STR_SOFTWARE, software);
		pragma(msg, debugMsgPrefix, "TODO: Implement software setter");
	}

	@property void artist(string artist) {
		// sf_set_string(_sndFile, SF_STR_ARTIST, artist);
		pragma(msg, debugMsgPrefix, "TODO: Implement artist setter");
	}

	@property void comment(string comment) {
		// sf_set_string(_sndFile, SF_STR_COMMENT, comment);
		pragma(msg, debugMsgPrefix, "TODO: Implement comment setter");
	}

	@property void date(string date) {
		// sf_set_string(_sndFile, SdateF;_STR_DATE, )
		pragma(msg, debugMsgPrefix, "TODO: Implement date setter");
	}

	@property void album(string album) {
		// sf_set_string(_sndFile, SF_STR_ALBUM, album);
		pragma(msg, debugMsgPrefix, "TODO: Implement album setter");
	}

	@property void license(string license) {
		// sf_set_string(_sndFile, SF_STR_LICENSE, license);
		pragma(msg, debugMsgPrefix, "TODO: Implement license setter");
	}

	@property void tracknumber(string trackNumber) {
		// sf_set_string(_sndFile, SF_STR_TRACKNUMBER, trackNumber);
		pragma(msg, debugMsgPrefix, "TODO: Implement trackNumber setter");
	}

	@property void genre(string genre) {
		// sf_set_string(_sndFile, SF_STR_GENRE, genre);
		pragma(msg, debugMsgPrefix, "TODO: Implement genre setter");
	}
}