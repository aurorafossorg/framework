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

module aurorafw.image.color;

alias rgb = (uint r, uint g, uint b) => ((r << 31) | (g << 15) | (b << 7));

enum CommonColor : uint {
	Black = 0x000000,
	Red = 0xFF0000,
	DarkRed = 0x800000,
	Green = 0x00FF00,
	DarkGreen = 0x008000,
	Blue = 0x0000FF,
	DarkBlue = 0x000080,
	Cyan = 0x00FFFF,
	DarkCyan = 0x008080,
	Magenta = 0xFF00FF,
	DarkMagenta = 0x800080,
	Yellow = 0xFFFF00,
	DarkYellow = 0x808000,
	White = 0xFFFFFF,
	DarkGray = 0x808080,
	LightGray = 0xC0C0C0,
	Gray = 0xA0A0A0,
	Tomato = 0xFF6347,
	AliceBlue = 0xF0F8FF,
	AntiqueWhite = 0xFAEBD7,
	Aquamarine = 0x7FFFD4,
	Azure = 0xF0FFFF,
	Beige = 0xF5F5DC,
	Bisque = 0xFFE4C4,
	BlanchedAlmond = 0xFFEBCD,
	BlueViolet =0x8A2BE2,
	Brown = 0x964B00,
	BurlyWood = 0xDEB887,
	CadetBlue = 0x5F9EA0,
	Chartreuse = 0x7FFF00
}

struct BaseColor(T) {
	this(T r, T g, T b, T a);
	this(uint hex, ubyte alpha = 0xFF);
	this(CommonColor color);

	void rgb(uint hex, ubyte alpha = 0xFF) @property;
	void rgb(T[3] color, T alpha) @property;
	void rgba(T[4] color) @property;
	T[4] rgba() @property;

	T r, g, b, a;
}

alias BaseColor!(ubyte) Color;
alias BaseColor!(float) ColorF;
