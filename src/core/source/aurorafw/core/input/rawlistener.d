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

module aurorafw.core.input.rawlistener;

/// TODO: Need documentation

public import aurorafw.core.input.events;
public import aurorafw.core.input.keys;

pure @safe abstract class RawInputListener {
	~this() {}

	void keyPressed(immutable KeyboardEvent e, bool lastState) {}
	void keyReleased(immutable KeyboardEvent e) {}
	void mousePressed(immutable MouseButtonEvent e, bool lastState) {}
	void mouseReleased(immutable MouseButtonEvent e) {}
	void mouseMoved(immutable MouseMotionEvent e) {}
	void mouseScrolled(immutable MouseScrollEvent e) {}
	void touchMoved(immutable TouchFingerEvent e) {}
	void touchPressed(immutable TouchFingerEvent e, bool lastState) {}
	void touchReleased(immutable TouchFingerEvent e) {}
}


@safe pure
@("Input: raw listener")
unittest {
	class MyInputListener : RawInputListener {

		override void keyPressed(immutable KeyboardEvent e, bool lastState)
		{
			assert(e.key == Keycode.Enter);
			assert(e.mods == InputModifier.Control);

			assert(!lastState);
		}


		override void keyReleased(immutable KeyboardEvent e)
		{
			assert(e.key == Keycode.Enter);
			assert(e.mods == InputModifier.None);
		}


		override void mousePressed(immutable MouseButtonEvent e, bool lastState)
		{
			assert(e.btn == InputButton.Left);
			assert(e.mods == InputModifier.NumLock);

			assert(lastState);
		}


		override void mouseReleased(immutable MouseButtonEvent e)
		{
			assert(e.btn == InputButton.Right);
			assert(e.mods == InputModifier.None);
		}


		override void mouseMoved(immutable MouseMotionEvent e)
		{
			assert(e.xpos == 1.04);
			assert(e.ypos == -0.23);
		}


		override void mouseScrolled(immutable MouseScrollEvent e)
		{
			assert(e.xoffset == 1.0);
			assert(e.yoffset == -1.0);
		}


		override void touchMoved(immutable TouchFingerEvent e)
		{
			assert(e.dx == 1.32f);
			assert(e.dy == 0.23f);

			assert(e.x == 2.54f);
			assert(e.y == -5.27f);

			assert(e.fingerID == 3);
		}


		override void touchPressed(immutable TouchFingerEvent e, bool lastState)
		{
			assert(e.dx == 1.32f);
			assert(e.dy == 0.23f);

			assert(e.x == 2.54f);
			assert(e.y == -5.27f);

			assert(e.fingerID == 3);

			assert(lastState);
		}


		override void touchReleased(immutable TouchFingerEvent e)
		{
			assert(e.dx == 1.32f);
			assert(e.dy == 0.23f);

			assert(e.x == 2.54f);
			assert(e.y == -5.27f);

			assert(e.fingerID == 3);
		}
	}

	MyInputListener listener = new MyInputListener();

	listener.keyPressed(KeyboardEvent(Keycode.Enter, InputModifier.Control), false);
	listener.keyReleased(KeyboardEvent(Keycode.Enter));
	listener.mousePressed(MouseButtonEvent(InputButton.Left, InputModifier.NumLock), true);
	listener.mouseReleased(MouseButtonEvent(InputButton.Right));
	listener.mouseMoved(MouseMotionEvent(1.04, -0.23));
	listener.mouseScrolled(MouseScrollEvent(1.0, -1.0));
	listener.touchMoved(TouchFingerEvent(1.32f, 0.23f, 2.54f, -5.27f, 3));
	listener.touchPressed(TouchFingerEvent(1.32f, 0.23f, 2.54f, -5.27f, 3), true);
	listener.touchReleased(TouchFingerEvent(1.32f, 0.23f, 2.54f, -5.27f, 3));
}
