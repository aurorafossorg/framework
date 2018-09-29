/*
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2018 Aurora Free Open Source Software.

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

	import aurorafw.gui.api.x11.backend : X11Backend;
	this(VisualPreferences vpref = VisualPreferences())
	{
		X11Backend.get();

		if(vpref.visual is null)
			vpref.visual = X.XDefaultVisual(X11Backend.display, X11Backend.screen);

		{
			X.XSetWindowAttributes _watt;
			_watt.border_pixel = 0;
			_watt.event_mask = X.StructureNotifyMask | X.KeyPressMask | X.KeyReleaseMask |
				X.PointerMotionMask | X.ButtonPressMask | X.ButtonReleaseMask |
				X.ExposureMask | X.FocusChangeMask | X.VisibilityChangeMask |
				X.EnterWindowMask | X.LeaveWindowMask | X.PropertyChangeMask;

			_handle = X.XCreateWindow(
					X11Backend.display,
					X11Backend.root,
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
		X.XSelectInput(X11Backend.display, _handle, X.ExposureMask | X.KeyPressMask);
		X.XMapWindow(X11Backend.display, _handle);
		X.XEvent _event;
	}

	~this()
	{

	}

private:
	X.Window _handle;
	X.Colormap _colormap;
}