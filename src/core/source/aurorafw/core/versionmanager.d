/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2018-2019 Aurora Free Open Source Software.

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

module aurorafw.core.versionmanager;

//TODO: Documentation

@safe
struct Version {
	uint major;
	uint minor;
	uint rev;

	this(uint major, uint minor, uint rev = 1)
	{
		this.major = major;
		this.minor = minor;
		this.rev = rev;
	}

	this(string strVer)
	{
		import std.array : split, replace;
		import std.conv : to;

		auto sstrVer = strVer.split("-");
		assert(sstrVer.length > 0 && sstrVer.length <= 2);
		if(sstrVer.length == 2)
			this.rev = to!uint(sstrVer[1]);

		{
			auto mver = sstrVer[0].split(".");
			assert(mver.length == 2);

			this.major = to!uint(mver[0]);
			this.minor = to!uint(mver[1]);
		}
	}

	static auto fromString(string strVer)()
	{
		enum sret = Version(strVer);
		return sret;
	}
}

enum VersionFlag : byte {
	NONE = 0,
	REVIEW = 1,
	FORCE = 1 << 1
}

pragma(inline) @property @safe string toString(Version ver, byte flag = VersionFlag.REVIEW)
{
	import std.conv : to;
	string ret = to!string(ver.major) ~ "." ~ to!string(ver.minor);
	return ((ver.rev > 1 && ((flag & VersionFlag.REVIEW) != 0)) || ((flag & VersionFlag.FORCE) != 0)) ? ret ~ "-" ~ to!string(ver.rev) : ret;
}

@safe
@("Versioning: simple")
unittest {
	Version ver = Version(1, 0);
	assert(ver.major == 1);
	assert(ver.minor == 0);
	assert(ver.rev == 1); //default
}

@safe
@("Versioning: string")
unittest {
	assert(Version(1, 1, 2).toString == "1.1-2");
	assert(Version(1, 1, 2).toString(VersionFlag.NONE) == "1.1");
	assert(Version(1, 3).toString == "1.3");
	assert(Version(1, 3).toString(VersionFlag.FORCE) == "1.3-1");
}

@safe
@("Versioning: compile-time evaluation")
unittest {
	enum Version ver = Version("1.5-2");
	assert(ver.major == 1);
	assert(ver.minor == 5);
	assert(ver.rev == 2);

	assert(Version.fromString!("1.5-2") == ver);
}
