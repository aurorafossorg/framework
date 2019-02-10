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

module aurorafw.core.input.manager;

import aurorafw.core.input.state;
import aurorafw.core.input.rawlistener;
import aurorafw.core.input.events;

struct InputManager {
	void addRawListener(RawInputListener listener)
	{
		_rawlisteneres ~= listener;
	}

	void removeRawListener(int index)
	{
		import std.algorithm : remove;
		_rawlisteneres.remove(index);
	}

	void keyPressed(immutable KeyboardEvent e)
	{
		foreach(listener; _rawlisteneres)
			listener.keyPressed(e, _keyboardState.isKeyPressed(e.key));
		_keyboardState.pressKey(e.key);
	}

	void keyReleased(immutable KeyboardEvent e)
	{
		foreach(listener; _rawlisteneres)
			listener.keyReleased(e);
		_keyboardState.releaseKey(e.key);
	}
	void mousePressed(immutable MouseButtonEvent e)
	{
		foreach(listener; _rawlisteneres)
			listener.mousePressed(e, _mouseState.isButtonPressed(e.btn));
		_mouseState.pressButton(e.btn);
	}
	void mouseReleased(immutable MouseButtonEvent e)
	{
		foreach(listener; _rawlisteneres)
			listener.mouseReleased(e);
		_mouseState.releaseButton(e.btn);
	}
	void mouseMoved(immutable MouseMotionEvent e)
	{
		foreach(listener; _rawlisteneres)
			listener.mouseMoved(e);

		_mouseState.x = e.xpos;
		_mouseState.y = e.ypos;
	}
	void mouseScrolled(immutable MouseScrollEvent e)
	{
		foreach(listener; _rawlisteneres)
			listener.mouseScrolled(e);
	}
	void touchMoved(immutable TouchFingerEvent e)
	{
		foreach(listener; _rawlisteneres)
			listener.touchMoved(e);
	}
	void touchPressed(immutable TouchFingerEvent e)
	{
		foreach(listener; _rawlisteneres)
			listener.touchPressed(e, _touchState.isTouchPressed(e.fingerID));
		_touchState.touchPress(e.fingerID);
	}
	void touchReleased(immutable TouchFingerEvent e)
	{
		foreach(listener; _rawlisteneres)
			listener.touchReleased(e);
		_touchState.touchRelease(e.fingerID);
	}

	private RawInputListener[] _rawlisteneres;
	private MouseState _mouseState;
	private KeyboardState _keyboardState;
	private TouchState _touchState;
}