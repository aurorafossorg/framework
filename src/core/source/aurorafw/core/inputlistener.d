module aurorafw.core.inputlistener;

/****************************************************************************
** ┌─┐┬ ┬┬─┐┌─┐┬─┐┌─┐  ┌─┐┬─┐┌─┐┌┬┐┌─┐┬ ┬┌─┐┬─┐┬┌─
** ├─┤│ │├┬┘│ │├┬┘├─┤  ├┤ ├┬┘├─┤│││├┤ ││││ │├┬┘├┴┐
** ┴ ┴└─┘┴└─└─┘┴└─┴ ┴  └  ┴└─┴ ┴┴ ┴└─┘└┴┘└─┘┴└─┴ ┴
** A Powerful General Purpose Framework
** More information in: https://aurora-fw.github.io/
**
** Copyright (C) 2018 Aurora Framework, All rights reserved.
**
** This file is part of the Aurora Framework. This framework is free
** software; you can redistribute it and/or modify it under the terms of
** the GNU Lesser General Public License version 3 as published by the
** Free Software Foundation and appearing in the file LICENSE included in
** the packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************/

pure @safe abstract class InputListener {
	struct KeyboardEvent {
		int key, scancode;
		ushort mods;
	}

	struct MouseButtonEvent {
		int btn;
		ushort mods;
	}

	struct MouseMotionEvent {
		double xpos, ypos;
	}

	struct MouseScrollEvent {
		double xoffset, yoffset;
	}

	~this() {}

	bool keyPressed(immutable ref KeyboardEvent )
	{ return true; }

	bool keyReleased(immutable ref KeyboardEvent )
	{ return true; }

	bool mousePressed(immutable ref MouseButtonEvent )
	{ return true; }

	bool mouseReleased(immutable ref MouseButtonEvent )
	{ return true; }

	bool mouseMoved(immutable ref MouseMotionEvent )
	{ return true; }

	bool mouseScrolled(immutable ref MouseScrollEvent )
	{ return true; }
}