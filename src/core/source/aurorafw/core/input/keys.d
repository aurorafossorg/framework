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

module aurorafw.core.input.keys;

/// TODO: Need documentation

enum Keycode : short {
	Unknown = -1,
	Space = 32,
	Apostrophe = 39,
	Comma = 44,
	Minus,
	Period, /* . */
	Slash,
	Num0,
	Num1,
	Num2,
	Num3,
	Num4,
	Num5,
	Num6,
	Num7,
	Num8,
	Num9,
	Semicolon = 59,
	Equal = 61,
	A = 65,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	LeftBracket, /* [ */
	BackSlash, /* \ */
	RightBracket, /* ] */
	GraveAccent = 96, /* ` */
	World1 = 161, /* non-US #1 */
	World2 = 162, /* non-US #2 */
	Escape = 256,
	Enter,
	Tab,
	Backspace,
	Insert,
	Delete,
	Right,
	Left,
	Down,
	Up,
	PageUp,
	PageDown,
	Home,
	End,
	CapsLock = 280,
	ScrollLock,
	NumLock,
	PrintScreen,
	Pause,
	F1 = 290,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
	F13,
	F14,
	F15,
	F16,
	F17,
	F18,
	F19,
	F20,
	F21,
	F22,
	F23,
	F24,
	F25,
	NumPad0 = 320,
	NumPad1,
	NumPad2,
	NumPad3,
	NumPad4,
	NumPad5,
	NumPad6,
	NumPad7,
	NumPad8,
	NumPad9,
	NumPadDecimal,
	NumPadDivide,
	NumPadMultiply,
	NumPadSubtract,
	NumPadAdd,
	NumPadEnter,
	NumPadEqual,
	LeftShift = 340,
	LeftControl,
	LeftAlt,
	LeftSuper,
	RightShift,
	RightControl,
	RightAlt,
	RightSuper,
	Menu,
	Last = Menu
}

enum InputButton : ubyte {
	B1,
	B2,
	B3,
	B4,
	B5,
	B6,
	B7,
	B8,
	Last = B8,
	Left = B1,
	Right = B2,
	Middle = B3
}

enum InputModifier : ubyte {
	Shift = 1 << 0,
	Control = 1 << 1,
	Alt = 1 << 2,
	Super = 1 << 3,
	CapsLock = 1 << 4,
	NumLock = 1 << 5
}