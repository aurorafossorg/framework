/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2018-2019 Aurora Free Open Source Software.
Copyright (C) 2018-2019 Luís Ferreira <luis@aurorafoss.org>

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

module aurorafw.stdx.string;

public import std.string;

import aurorafw.unit.assertion;


@nogc @safe pure nothrow
string substr(string s, ptrdiff_t offset, ptrdiff_t length = -1)
{
	size_t end = void;
	import std.stdio;

	if (offset > 0 && offset > s.length)
		return "";
	if (offset < 0)
		offset = 0;
	if (length < 0)
		end = s.length;
	else
		end = offset + length;
	if(end > s.length)
		end = s.length;

	return s[offset .. end];
}


@nogc @safe pure nothrow
bool isAlpha(string str)
{
	import std.algorithm : all;
	import std.uni : isAlpha;

	foreach(c; str)
		if (!isAlpha(c))
			return false;

	return true;
}


///
@safe pure
@("String: substr")
unittest
{
	string s = "Aurora Framework";
	assertEquals("urora", s.substr(1,5));
	assertEquals("urora Framework", s.substr(1));
	assertEquals(s, s.substr(-1, -1));
	assertEquals(s, s.substr(-1));
	assertEquals(s, s.substr(0, ptrdiff_t.max));
	assertEquals("", s.substr(ptrdiff_t.max));
}


///
@safe pure
@("String: isAlpha")
unittest
{
	assertTrue(isAlpha("tunaisgood"));
	assertFalse(isAlpha("tun41s900d"));
}
