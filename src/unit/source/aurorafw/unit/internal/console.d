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

module aurorafw.unit.internal.console;

__gshared bool noColours;

enum Colour {
	none,
	ok = 32,
	achtung = 31,
}

static struct Console {
	import std.conv : text;

	static void init() {
		if(noColours) {
			return;
		} else {
			version(Posix) {
				import core.sys.posix.unistd;
				noColours = isatty(STDOUT_FILENO) == 0;
			} else version(Windows) {
				import core.sys.windows.winbase : GetStdHandle, STD_OUTPUT_HANDLE, INVALID_HANDLE_VALUE;
				import core.sys.windows.wincon : SetConsoleOutputCP, GetConsoleMode, SetConsoleMode;
				import core.sys.windows.windef : DWORD;
				import core.sys.windows.winnls : CP_UTF8;

				SetConsoleOutputCP(CP_UTF8);

				auto hOut = GetStdHandle(STD_OUTPUT_HANDLE);
				DWORD originalMode;

				noColours = hOut == INVALID_HANDLE_VALUE ||
					!GetConsoleMode(hOut, &originalMode) ||
					!SetConsoleMode(hOut, originalMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
			}
		}
	}

	static string colour(T)(T t, Colour c = Colour.none) {
		return noColours
			? text(t)
			: text("\033[", cast(int) c, "m", t, "\033[m");
	}

	static string emphasis(T)(T t)
	{
		return noColours
			? text(t)
			: text("\033[1m", t, "\033[m");
	}

	static string truncateName(string s, bool verbose = false)
	{
		import std.algorithm : max;
		import std.string : indexOf;
		return s.length > 30 && !verbose
			? s[max(s.indexOf('.', s.length - 30), s.length - 30) .. $]
			: s;
	}
}
