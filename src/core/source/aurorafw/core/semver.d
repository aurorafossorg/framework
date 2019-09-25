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

/++
Semantic Versioning
This file defines semantic versioning validators and structs for versioning
Authors: Luís Ferreira <luis@aurorafoss.org>
Copyright: All rights reserved, Aurora Free Open Source Software
License: GNU Lesser General Public License (Version 3, 29 June 2007)
Date: 2018-2019
+/
module aurorafw.core.semver;

import aurorafw.unit.assertion;
import std.conv : to, ConvException;
import std.traits : isIntegral;
import std.ascii : isDigit;
import std.string : split;
import aurorafw.stdx.array : replaceFirst;
import std.range.primitives;
import std.format;
import std.algorithm;
import std.exception : enforce;
import core.exception;

/** Version struct
 *
 * Data struct to store version with MAJOR.MINOR.PATCH format.
 *
 * Examples:
 * --------------------
 * Version foo = Version(3, 1);
 * assert(foo.to!string == "3.1.0");
 * --------------------
 */
@safe pure
struct Version {
	/// Major version
	public uint major;
	/// Minor version
	public uint minor;
	/// Patch version
	public uint patch;


	/// Default constructor
	@safe pure
	public this(M = uint, N = uint, P = uint)(M major = uint.init, N minor = uint.init, P patch = uint.init)
	if(isIntegral!M && isIntegral!N && isIntegral!P)
	{
		this.major = major;
		this.minor = minor;
		this.patch = patch;
	}


	/** Construct from string
	 * Use common version strings and convert to
	 * MAJOR.MINOR.PATCH version scheme if its possible
	 *
	 * Throws: FormatException if format is invalid
	 */
	@safe pure
	public this(string str)
	{
		if(str.empty)
			return;

		if(str.length > 0 && str[0] == 'v')
			str = str[1 .. $];

		auto strSplitted = str.split('.');

		try {
			foreach(i, verStr; strSplitted)
			{
				if((i + 1 == strSplitted.length && i <= 2) || i == 2)
				{
					auto verStrReplaced = verStr.replaceFirst('+', '-');
					auto verStrSplitted = verStrReplaced.split('-');
					this[i] = verStrSplitted.front.to!uint;
					if(verStrSplitted.length > 1 &&
						verStrReplaced == verStr &&
						verStrSplitted[1].all!(isDigit) &&
						i != 2)
					{
						this[2] = verStrSplitted[1].to!uint;
					}
				} else if(i >= 3)
				{
					return;
				}
				else {
					this[i] = verStr.to!uint;
				}
			}
		}
		catch(Exception e)
		{
			throw new FormatException("Invalid version format", e.file, e.line);
		}

	}


	@safe pure
	uint[] opIndex()
	{
		return [major, minor, patch];
	}


	@safe pure
	uint opIndex(size_t idx)
	{
		enforce(idx < 3, "Invalid index");

		return opIndex[idx];
	}


	@safe pure
	uint opIndexAssign(uint val, size_t idx)
	{
		enforce(idx < 3, "Invalid index");

		final switch(idx)
		{
			case 0: return this.major = val;
			case 1: return this.minor = val;
			case 2: return this.patch = val;
		}
	}

	@safe pure
	public string toString()
	{
		return major.to!string ~ "." ~ minor.to!string ~ "." ~ patch.to!string;
	}
}


///
@safe pure
@("Versioning: Check for .init in ctor")
unittest
{
	Version ver = Version();
	assertEquals(0, ver.major);
	assertEquals(0, ver.minor);
	assertEquals(0, ver.patch);

	ver = Version(1);
	assertEquals(1, ver.major);
	assertEquals(0, ver.minor);
	assertEquals(0, ver.patch);

	ver = Version(2, 1);
	assertEquals(2, ver.major);
	assertEquals(1, ver.minor);
	assertEquals(0, ver.patch);

	ver = Version(1, 2, 4);
	assertEquals(1, ver.major);
	assertEquals(2, ver.minor);
	assertEquals(4, ver.patch);
}


///
@safe pure
@("Versioning: index operator")
unittest
{
	Version ver = Version(1, 4, 5);
	assertEquals(1, ver[0]);
	assertEquals(4, ver[1]);
	assertEquals(5, ver[2]);

	ver[2] = 2;
	assertEquals(Version(1, 4, 2), ver);

	expectThrows(ver[3] = 0);
	expectThrows(ver[3]);
}


///
@safe pure
@("Versioning: ctor from string")
unittest
{
	Version ver = Version("");
	assertEquals(Version(), ver);

	// supress minor and patch
	ver = Version("1");
	assertEquals(Version(1), ver);

	// supress patch
	ver = Version("2.1");
	assertEquals(Version(2, 1, 0), ver);

	ver = Version("1.2.4");
	assertEquals(Version(1, 2, 4), ver);

	ver = Version("v1.2.4");
	assertEquals(Version(1, 2, 4), ver);

	ver = Version("1.2.4-alpha.1");
	assertEquals(Version(1, 2, 4), ver);

	ver = Version("1.2-1");
	assertEquals(Version(1, 2, 1), ver);

	ver = Version("1.2.4-1");
	assertEquals(Version(1, 2, 4), ver);

	ver = Version("2-1");
	assertEquals(Version(2, 0, 1), ver);

	ver = Version("1.2+543");
	assertEquals(Version(1, 2), ver);

	ver = Version("1.2.1+543");
	assertEquals(Version(1, 2, 1), ver);

	expectThrows(Version("-alpha.1"));
	expectThrows(Version(".-rc.1"));
	expectThrows(Version("1.."));
	expectThrows(Version("vv1.1"));
	expectThrows(Version("1.1-"));
	expectThrows(Version("-1"));
	expectThrows(Version("-"));
	expectThrows(Version("alpha"));
	expectThrows(Version("."));
}


///
@safe pure
@("Versioning: string conversion")
unittest {
	Version ver = Version(1, 3, 4);
	assertEquals("1.3.4", ver.to!string);

	ver = Version(1, 3);
	assertEquals("1.3.0", ver.to!string);
}
