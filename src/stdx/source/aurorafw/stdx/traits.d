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

/++
Extras to std.traits

This file defines extra functions to std.traits.

Authors: Luís Ferreira <luis@aurorafoss.org>
Copyright: All rights reserved, Aurora Free Open Source Software
License: GNU Lesser General Public License (Version 3, 29 June 2007)
Date: 2018-2019
+/
module aurorafw.stdx.traits;

import std.format;

version(unittest) import aurorafw.unit.assertion;


/**
 * Detect version identifiers
 *
 * This is a template to check if a version
 * identifier is available.
 *
 * Examples:
 * --------------------
 * static if(isVersion!"unittest")
 * {
*      // code with version unittest ...
 * }
 * --------------------
 */
@nogc @safe pure nothrow
template isVersion(string ver) {
	mixin(format(q{
		version(%s) {
			enum isVersion = true;
		}
		else {
			enum isVersion = false;
		}
	}, ver));
}


///
@safe pure
@("Traits: isVersion")
unittest
{
	assertTrue(isVersion!"unittest");
	assertFalse(isVersion!"this_shouldnt_be_a_version_identifier");
}
