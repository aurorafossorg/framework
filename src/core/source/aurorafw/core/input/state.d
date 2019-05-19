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

module aurorafw.core.input.state;

///TODO: Need documentation

import aurorafw.core.input.keys;

struct KeyboardState {
	private bool[short] keys;

	bool isKeyPressed(Keycode key) const
	{
		if((key in keys) !is null)
			return keys[key];
		else
			return false;
	}

	void pressKey(Keycode key)
	{
		keys[key] = true;
	}

	void releaseKey(Keycode key)
	{
		keys[key] = false;
	}
}

struct MouseState {
	private bool[8] buttons;
	double x, y;

	bool isButtonPressed(InputButton button) const
	{
		return buttons[button];
	}

	void pressButton(InputButton button)
	{
		buttons[button] = true;
	}

	void releaseButton(InputButton button)
	{
		buttons[button] = false;
	}
}

struct TouchState {
	private bool[ubyte] fingers;

	bool isTouchPressed(ubyte id) const
	{
		return fingers[id];
	}

	void touchPress(ubyte id)
	{
		if(fingers[id] == false) fingers[id] = true;
	}

	void touchRelease(ubyte id)
	{
		fingers[id] = false;
	}
}
