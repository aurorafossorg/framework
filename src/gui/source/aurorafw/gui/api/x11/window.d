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

module aurorafw.gui.api.x11.window;

import aurorafw.gui.window : Window;
import X = aurorafw.gui.platform.x11;

class X11Window : Window {
	struct VisualPreferences
	{
		X.Visual* visual = null;
		uint depth;
	}

	import aurorafw.gui.api.backend : Backend;
	import aurorafw.gui.api.x11.backend : X11Backend;
	this(VisualPreferences vpref = VisualPreferences())
	{
		_backend = cast(X11Backend)Backend.get();

		if(vpref.visual is null)
			vpref.visual = X.XDefaultVisual(_backend.display, _backend.screen);

		{
			X.XSetWindowAttributes _watt;
			_watt.border_pixel = 0;
			_watt.event_mask = X.StructureNotifyMask | X.KeyPressMask | X.KeyReleaseMask |
				X.PointerMotionMask | X.ButtonPressMask | X.ButtonReleaseMask |
				X.ExposureMask | X.FocusChangeMask | X.VisibilityChangeMask |
				X.EnterWindowMask | X.LeaveWindowMask | X.PropertyChangeMask;

			_handle = X.XCreateWindow(
					_backend.display,
					_backend.root,
					0,
					0,
					_wp.width,
					_wp.height,
					0,
					_wp.depth,
					X.InputOutput,
					vpref.visual,
					(X.CWBorderPixel | X.CWColormap | X.CWEventMask),
					&_watt);
		}
		X.XSelectInput(_backend.display, _handle, X.ExposureMask | X.KeyPressMask);
		X.XMapWindow(_backend.display, _handle);
		import std.string;
		X.XStoreName(_backend.display, _handle, _name.toStringz());
	}

	import aurorafw.core.input.manager;
	override void pollEvents(InputManager inmanager = InputManager())
	{
		X.XPending(_backend.display);
		while (X.XQLength(_backend.display))
		{
			X.XEvent e;
			X.XNextEvent(_backend.display, &e);

			import aurorafw.core.input.events;
			import aurorafw.gui.api.x11.input;
			switch(e.type)
			{
				case X.KeyPress:
					inmanager.keyPressed(KeyboardEvent(translateKeycodeX11(e.xkey.keycode), translateInputModifierX11(e.xkey.state)));
					break;

				case X.KeyRelease:
					inmanager.keyReleased(KeyboardEvent(translateKeycodeX11(e.xkey.keycode), translateInputModifierX11(e.xkey.state)));
					break;

				case X.ButtonPress:
					inmanager.mousePressed(MouseButtonEvent(translateInputButtonX11(e.xbutton.state), translateInputModifierX11(e.xbutton.state)));
					break;

				case X.ButtonRelease:
					inmanager.mouseReleased(MouseButtonEvent(translateInputButtonX11(e.xbutton.state), translateInputModifierX11(e.xbutton.state)));
					break;

				default: break;
			}
		}
	}

	~this()
	{

	}

private:
	X.Window _handle;
	X.Colormap _colormap;
	X11Backend _backend;
}