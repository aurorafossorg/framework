/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2019 Anton Fediushin
Copyright (C) 2019 Aurora Free Open Source Software.
Copyright (C) 2019 Luís Ferreira <luis@aurorafoss.org>

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
https://www.gnu.org/licenses/gpl-3.0.html.

NOTE: All products, services or anything associated to trademarks and
service marks used or referenced on this file are the property of their
respective companies/owners or its subsidiaries. Other names and brands
may be claimed as the property of others.

For more info about intellectual property visit: aurorafoss.org or
directly send an email to: contact (at) aurorafoss.org .

This file was based on silly runner.
More about silly: https://gitlab.com/AntonMeep/silly
*/

module aurorafw.unit.internal.test;

package(aurorafw.unit):
version(unittest):

import std.datetime : Duration;

struct Test {
	struct Unit {
		string fullName;
		string testName;

		void function() testFunc;
	}

	struct Thrown {
		string type;
		string msg;
		string file;

		size_t line;

		immutable(string)[] info;
	}

	Unit test;
	bool status;
	Duration duration;

	immutable(Thrown)[] thrown;
}

string getTestName(alias test)() {
	string name = __traits(identifier, test);

	foreach(attribute; __traits(getAttributes, test)) {
		static if(is(typeof(attribute) : string)) {
			name = attribute;
			break;
		}
	}

	return name;
}
