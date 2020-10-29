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

module aurorafw.core.input.events;

import aurorafw.core.input.keys;

/**
 * Keyboard Event
 *
 * This represents a keyboard event with keycode
 * and input modifiers
 *
 * Examples:
 * --------------------
 * auto ke = KeyboardEvent(Keycode.A, InputModifier.Control | InputModifier.Alt);
 * --------------------
 */
struct KeyboardEvent
{
	Keycode key;
	InputModifier mods;
}

/**
 * Mouse Button Event
 *
 * This represents a mouse button event with
 * button id and input modifiers
 *
 * Examples:
 * --------------------
 * auto mbe = MouseButtonEvent(InputButton.B1, InputModifier.None);
 * --------------------
 */
struct MouseButtonEvent
{
	InputButton btn;
	InputModifier mods;
}

/**
 * Mouse Motion Event
 *
 * This represents a mouse motion event with
 * x and y position.
 *
 * Examples:
 * --------------------
 * auto mme = MouseMotionEvent(0.5, -0.4);
 * --------------------
 */
struct MouseMotionEvent
{
	double xpos, ypos;
}

/**
 * Mouse Scroll Event
 *
 * This represents a mouse scroll event with
 * x and y position offset.
 *
 * Examples:
 * --------------------
 * auto mse = MouseScrollEvent(-1.0, 0);
 * --------------------
 */
struct MouseScrollEvent
{
	double xoffset, yoffset;
}

/**
 * Touch Finger Event
 *
 * This represents a touch finger event with,
 * deslocated x and y, x and y position and
 * finger ID
 *
 * Examples:
 * --------------------
 * auto tfe = TouchFingerEvent(1.0f, 1.0f, 0.5f, 0.4f, 1);
 * --------------------
 */
struct TouchFingerEvent
{
	float dx, dy;
	float x, y;
	ubyte fingerID;
}
