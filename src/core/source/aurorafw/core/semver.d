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

This file was based on DUB and Ruby Gems.
More about DUB: https://github.com/dlang/dub
More about Ruby Gems: https://github.com/rubygems/rubygems
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

import std.conv : to, ConvException;
import std.traits : isIntegral;
import std.ascii : isDigit;
import std.uni : isNumber;
import aurorafw.stdx.array : replaceFirst;
import std.string;
import std.range.primitives;
import std.format;
import std.algorithm;
import std.exception : enforce;
import core.exception;

version(unittest) import aurorafw.unit.assertion;
import aurorafw.stdx.string : indexOfAny;

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
	@safe pure @nogc
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
						verStrSplitted[1].all!(isNumber) &&
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
	int opCmp(ref const Version v) const // for l-values
	{
		return (this.major != v.major) ? this.major - v.major :
				(this.minor != v.minor) ? this.minor - v.minor :
				(this.patch != v.patch) ? this.patch - v.patch :
				0;
	}

	@safe pure
	int opCmp(const Version v) const // for r-values
	{
		return opCmp(v);
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

///
@safe pure
@("Versioning: boolean operations")
unittest {
	assertGreaterThan(Version(2), Version(1));
	assertGreaterThan(Version(2), Version(1, 2, 3));
	assertLessThan(Version(2), Version(3));

	assertFalse(Version(1) < Version(1) || Version(1) > Version(1));
	assertTrue(Version(1) >= Version(1) && Version(1) <= Version(1));

	assertEquals(Version(2), Version(2));
	assertGreaterThan(Version(1, 0, 1), Version(1, 0, 0));
	assertLessThan(Version(1, 0, 32), Version(1, 1, 0));
}


/**
 * Check if the given version is semver compatible
 */
@safe pure
bool isValidVersion(string str)
{
	try {
		Version(str);
		return true;
	} catch (FormatException )
	{
		return false;
	}
}

@("Versioning: check valid version")
@safe pure
unittest {
	enum testCTFE = isValidVersion("1.0.0");

	assertTrue(isValidVersion("1.0.0"));
	assertFalse(isValidVersion("1. -"));

	//aditional tests
	assertTrue(isValidVersion("01.9.0"));
	assertTrue(isValidVersion("1.09.0"));
	assertTrue(isValidVersion("1.9.00"));
	assertTrue(isValidVersion("1.0.0-alpha"));
	assertTrue(isValidVersion("1.0.0-alpha.1"));
	assertTrue(isValidVersion("1.0.0-0.3.7"));
	assertTrue(isValidVersion("1.0.0-x.7.z.92"));
	assertTrue(isValidVersion("1.0.0-x.7-z.92"));
	assertTrue(isValidVersion("1.0.0-00.3.7"));
	assertTrue(isValidVersion("1.0.0-0.03.7"));
	assertTrue(isValidVersion("1.0.0-alpha+001"));
	assertTrue(isValidVersion("1.0.0+20130313144700"));
	assertTrue(isValidVersion("1.0.0-beta+exp.sha.5114f85"));
	assertFalse(isValidVersion(" 1.0.0"));
	assertFalse(isValidVersion("1. 0.0"));
	assertFalse(isValidVersion("1.0 .0"));
	assertFalse(isValidVersion("1.0.0 "));
}

/**
 * Validates a version string according to the SemVer specification.
 */
@safe pure @nogc
bool isSemVer(string ver)
{
	// a
	auto sepi = ver.indexOf('.');
	if (sepi < 0) return false;
	if (!isSemVerNumber(ver[0 .. sepi])) return false;
	ver = ver[sepi+1 .. $];

	// c
	sepi = ver.indexOf('.');
	if (sepi < 0) return false;
	if (!isSemVerNumber(ver[0 .. sepi])) return false;
	ver = ver[sepi+1 .. $];

	// c
	sepi = ver.indexOfAny("-+");
	if (sepi < 0) sepi = ver.length;
	if (!isSemVerNumber(ver[0 .. sepi])) return false;
	ver = ver[sepi .. $];

	@safe pure @nogc
	bool isValidIdentifierChain(string str, bool allow_leading_zeros = false)
	{
		bool isValidIdentifier(string str, bool allow_leading_zeros = false)
		pure @nogc {
			if (str.length < 1) return false;

			bool numeric = true;
			foreach (ch; str) {
				switch (ch) {
					default: return false;
					case 'a': .. case 'z':
					case 'A': .. case 'Z':
					case '-':
						numeric = false;
						break;
					case '0': .. case '9':
						break;
				}
			}

			if (!allow_leading_zeros && numeric && str[0] == '0' && str.length > 1) return false;

			return true;
		}

		if (str.length == 0) return false;
		while (str.length) {
			auto end = str.indexOf('.');
			if (end < 0) end = str.length;
			if (!isValidIdentifier(str[0 .. end], allow_leading_zeros)) return false;
			if (end < str.length) str = str[end+1 .. $];
			else break;
		}
		return true;
	}

	// prerelease tail
	if (ver.length > 0 && ver[0] == '-') {
		ver = ver[1 .. $];
		sepi = ver.indexOf('+');
		if (sepi < 0) sepi = ver.length;
		if (!isValidIdentifierChain(ver[0 .. sepi])) return false;
		ver = ver[sepi .. $];
	}

	// build tail
	if (ver.length > 0 && ver[0] == '+') {
		ver = ver[1 .. $];
		if (!isValidIdentifierChain(ver, true)) return false;
		ver = null;
	}

	assert(ver.length == 0);
	return true;
}


///
@("Versioning: check valid semantic version")
@safe pure
unittest {
	enum testCTFE = isSemVer("1.0.0");

	assertTrue(isSemVer("1.9.0"));
	assertTrue(isSemVer("0.10.0"));
	assertFalse(isSemVer("01.9.0"));
	assertFalse(isSemVer("1.09.0"));
	assertFalse(isSemVer("1.9.00"));
	assertTrue(isSemVer("1.0.0-alpha"));
	assertTrue(isSemVer("1.0.0-alpha.1"));
	assertTrue(isSemVer("1.0.0-0.3.7"));
	assertTrue(isSemVer("1.0.0-x.7.z.92"));
	assertTrue(isSemVer("1.0.0-x.7-z.92"));
	assertFalse(isSemVer("1.0.0-00.3.7"));
	assertFalse(isSemVer("1.0.0-0.03.7"));
	assertTrue(isSemVer("1.0.0-alpha+001"));
	assertTrue(isSemVer("1.0.0+20130313144700"));
	assertTrue(isSemVer("1.0.0-beta+exp.sha.5114f85"));
	assertFalse(isSemVer(" 1.0.0"));
	assertFalse(isSemVer("1. 0.0"));
	assertFalse(isSemVer("1.0 .0"));
	assertFalse(isSemVer("1.0.0 "));
	assertFalse(isSemVer("1.0.0-a_b"));
	assertFalse(isSemVer("1.0.0+"));
	assertFalse(isSemVer("1.0.0-"));
	assertFalse(isSemVer("1.0.0-+a"));
	assertFalse(isSemVer("1.0.0-a+"));
	assertFalse(isSemVer("1.0"));
	assertFalse(isSemVer("1.0-1.0"));
}


/**
 * Takes a partial version and expands it to a valid SemVer version.
 *
 * This function corresponds to the semantivs of the "~>" comparison operator's
 * lower bound.
 *
 * See_Also: `bumpVersion`
 */
@safe pure
string expandVersion(string ver)
{
	auto mi = ver.indexOfAny("+-");
	auto sub = "";
	if (mi > 0) {
		sub = ver[mi..$];
		ver = ver[0..mi];
	}
	auto splitted = () @trusted { return split(ver, "."); } ();
	assert(splitted.length > 0 && splitted.length <= 3, "Version corrupt: " ~ ver);
	while (splitted.length < 3) splitted ~= "0";
	return splitted.join(".") ~ sub;
}


///
@("Versioning: expand version")
@safe pure
unittest {
	assertEquals("1.0.0", expandVersion("1"));
	assertEquals("1.0.0", expandVersion("1.0"));
	assertEquals("1.0.0", expandVersion("1.0.0"));
	// These are rather excotic variants...
	assertEquals("1.0.0-pre.release", expandVersion("1-pre.release"));
	assertEquals("1.0.0+meta", expandVersion("1+meta"));
	assertEquals("1.0.0-pre.release+meta", expandVersion("1-pre.release+meta"));
}


/**
 * Determines if a given valid SemVer version has a pre-release suffix.
 */
@safe pure
bool isPreReleaseVersion(string ver)
in { assert(isSemVer(ver)); }
body {
	foreach (i; 0 .. 2) {
		auto di = ver.indexOf('.');
		assert(di > 0);
		ver = ver[di+1 .. $];
	}
	auto di = ver.indexOf('-');
	if (di < 0) return false;
	return isSemVerNumber(ver[0 .. di]);
}

///
@("Versioning: check pre-release")
@safe pure
unittest {
	assertTrue(isPreReleaseVersion("1.0.0-alpha"));
	assertTrue(isPreReleaseVersion("1.0.0-alpha+b1"));
	assertTrue(isPreReleaseVersion("0.9.0-beta.1"));
	assertFalse(isPreReleaseVersion("0.9.0"));
	assertFalse(isPreReleaseVersion("0.9.0+b1"));
}



/**
 * Compares the precedence of two SemVer version strings.

 * The version strings must be validated using `isSemVer` before being
 * passed to this function. Note that the build meta data suffix (if any) is
 * being ignored when comparing version numbers.

 * Returns:
 *      Returns a negative number if `a` is a lower version than `b`, `0` if they are
 *      equal, and a positive number otherwise.
 */
@safe pure @nogc nothrow
int compareSemVer(string a, string b)
{
	@safe pure @nogc nothrow
	int compareIdentifier(ref string a, ref string b)
	{
		bool anumber = true;
		bool bnumber = true;
		bool aempty = true, bempty = true;
		int res = 0;
		while (true) {
			if (a[0] != b[0] && res == 0) res = a[0] - b[0];
			if (anumber && (a[0] < '0' || a[0] > '9')) anumber = false;
			if (bnumber && (b[0] < '0' || b[0] > '9')) bnumber = false;
			a = a[1 .. $]; b = b[1 .. $];
			aempty = !a.length || a[0] == '.' || a[0] == '+';
			bempty = !b.length || b[0] == '.' || b[0] == '+';
			if (aempty || bempty) break;
		}

		if (anumber && bnumber) {
			if (aempty != bempty) return bempty - aempty;
			return res;
		} else {
			if (anumber && aempty) return -1;
			if (bnumber && bempty) return 1;

			static assert('0' < 'a' && '0' < 'A');
			if (res != 0) return res;
			return bempty - aempty;
		}
	}

	@safe pure @nogc nothrow
	int compareNumber(ref string a, ref string b)
	{
		int res = 0;
		while (true) {
			if (a[0] != b[0] && res == 0) res = a[0] - b[0];
			a = a[1 .. $]; b = b[1 .. $];
			auto aempty = !a.length || (a[0] < '0' || a[0] > '9');
			auto bempty = !b.length || (b[0] < '0' || b[0] > '9');
			if (aempty != bempty) return bempty - aempty;
			if (aempty) return res;
		}
	}

	// compare a.b.c numerically
	if (auto ret = compareNumber(a, b)) return ret;
	assert(a[0] == '.' && b[0] == '.');
	a = a[1 .. $]; b = b[1 .. $];
	if (auto ret = compareNumber(a, b)) return ret;
	assert(a[0] == '.' && b[0] == '.');
	a = a[1 .. $]; b = b[1 .. $];
	if (auto ret = compareNumber(a, b)) return ret;

	// give precedence to non-prerelease versions
	bool apre = a.length > 0 && a[0] == '-';
	bool bpre = b.length > 0 && b[0] == '-';
	if (apre != bpre) return bpre - apre;
	if (!apre) return 0;

	// compare the prerelease tail lexicographically
	do {
		a = a[1 .. $]; b = b[1 .. $];
		if (auto ret = compareIdentifier(a, b)) return ret;
	} while (a.length > 0 && b.length > 0 && a[0] != '+' && b[0] != '+');

	// give longer prerelease tails precedence
	bool aempty = a.length == 0 || a[0] == '+';
	bool bempty = b.length == 0 || b[0] == '+';
	if (aempty == bempty) {
		assert(aempty);
		return 0;
	}
	return bempty - aempty;
}

///
@("Versioning: semver comparison")
@safe pure
unittest {
	assertEquals(0, compareSemVer("1.0.0", "1.0.0"));
	assertEquals(0, compareSemVer("1.0.0+b1", "1.0.0+b2"));
	assertLessThan(compareSemVer("1.0.0", "2.0.0"), 0);
	assertLessThan(compareSemVer("1.0.0-beta", "1.0.0"), 0);
	assertGreaterThan(compareSemVer("1.0.1", "1.0.0"), 0);

	void assertLess(string a, string b) {
		assertLessThan(compareSemVer(a, b), 0);
		assertGreaterThan(compareSemVer(b, a), 0);
		assertEquals(0, compareSemVer(a, a));
		assertEquals(0, compareSemVer(b, b));
	}
	assertLess("1.0.0", "2.0.0");
	assertLess("2.0.0", "2.1.0");
	assertLess("2.1.0", "2.1.1");
	assertLess("1.0.0-alpha", "1.0.0");
	assertLess("1.0.0-alpha", "1.0.0-alpha.1");
	assertLess("1.0.0-alpha.1", "1.0.0-alpha.beta");
	assertLess("1.0.0-alpha.beta", "1.0.0-beta");
	assertLess("1.0.0-beta", "1.0.0-beta.2");
	assertLess("1.0.0-beta.2", "1.0.0-beta.11");
	assertLess("1.0.0-beta.11", "1.0.0-rc.1");
	assertLess("1.0.0-rc.1", "1.0.0");
	assertEquals(0, compareSemVer("1.0.0", "1.0.0+1.2.3"));
	assertEquals(0, compareSemVer("1.0.0", "1.0.0+1.2.3-2"));
	assertEquals(0, compareSemVer("1.0.0+asdasd", "1.0.0+1.2.3"));
	assertLess("2.0.0", "10.0.0");
	assertLess("1.0.0-2", "1.0.0-10");
	assertLess("1.0.0-99", "1.0.0-1a");
	assertLess("1.0.0-99", "1.0.0-a");
	assertLess("1.0.0-alpha", "1.0.0-alphb");
	assertLess("1.0.0-alphz", "1.0.0-alphz0");
	assertLess("1.0.0-alphZ", "1.0.0-alpha");
}


/**
 * Increments a given (partial) version number to the next higher version.
 *
 * Prerelease and build metadata information is ignored. The given version
 * can skip the minor and patch digits. If no digits are skipped, the next
 * minor version will be selected. If the patch or minor versions are skipped,
 * the next major version will be selected.
 *
 * This function corresponds to the semantivs of the "~>" comparison operator's
 * upper bound.
 *
 * The semantics of this are the same as for the "approximate" version
 * specifier from rubygems.
 * (https://github.com/rubygems/rubygems/tree/81d806d818baeb5dcb6398ca631d772a003d078e/lib/rubygems/version.rb)
 *
 * See_Also: `expandVersion`
 */
@safe pure
string bumpVersion(string ver)
{
	// Cut off metadata and prerelease information.
	auto mi = ver.indexOfAny("+-");
	if (mi > 0) ver = ver[0..mi];
	// Increment next to last version from a[.b[.c]].
	auto splitted = () @trusted { return split(ver, "."); } (); // DMD 2.065.0
	assert(splitted.length > 0 && splitted.length <= 3, "Version corrupt: " ~ ver);
	auto to_inc = splitted.length == 3? 1 : 0;
	splitted = splitted[0 .. to_inc+1];
	splitted[to_inc] = to!string(to!int(splitted[to_inc]) + 1);
	// Fill up to three compontents to make valid SemVer version.
	while (splitted.length < 3) splitted ~= "0";
	return splitted.join(".");
}


///
@("Versioning: bump version")
@safe pure
unittest {
	assertEquals("1.0.0", bumpVersion("0"));
	assertEquals("1.0.0", bumpVersion("0.0"));
	assertEquals("0.1.0", bumpVersion("0.0.0"));
	assertEquals("1.3.0", bumpVersion("1.2.3"));
	assertEquals("1.3.0", bumpVersion("1.2.3+metadata"));
	assertEquals("1.3.0", bumpVersion("1.2.3-pre.release"));
	assertEquals("1.3.0", bumpVersion("1.2.3-pre.release+metadata"));
}


@safe pure @nogc nothrow
private bool isSemVerNumber(string str)
{
	if (str.length < 1) return false;
	foreach (ch; str)
		if (ch < '0' || ch > '9')
			return false;

	if (str[0] == '0' && str.length > 1) return false;

	return true;
}
