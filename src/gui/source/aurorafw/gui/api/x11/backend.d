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

module aurorafw.gui.api.x11.backend;

import X = aurorafw.gui.platform.x11;
import std.conv : emplace;
import core.stdc.stdlib : malloc, free;
import aurorafw.math.vector : Vector2f;
import std.process : environment;
import aurorafw.core.logger : error;
import core.stdc.stdlib : exit;
import core.stdc.stdlib : atof;
import core.stdc.string : strcmp;

pure class X11Backend {
	private this()
	{
		X.XInitThreads();
		X.XrmInitialize();
		_display = X.XOpenDisplay(null);

		if(_display is null)
		{
			auto env_display = environment.get("DISPLAY");
			if(env_display)
				error("X11: Cannot open display ", env_display);
			else
				error("X11: DISPLAY variable is missing");

			exit(1); //TODO: add error to Error Database
		}

		_screen = X.XDefaultScreen(_display);
		_root = X.XRootWindow(_display, _screen);
		_context = X.XUniqueContext();

		{
			float xdpi = X.XDisplayWidth(_display, _screen) * 25.4f / X.XDisplayWidthMM(_display, _screen);
			float ydpi = X.XDisplayHeight(_display, _screen) * 25.4f / X.XDisplayHeightMM(_display, _screen);
			
			char* rms = X.XResourceManagerString(_display);
			if (rms)
			{
				X.XrmDatabase db = X.XrmGetStringDatabase(rms);
				if (db)
				{
					X.XrmValue value;
					char* type = null;

					if (X.XrmGetResource(db, "Xft.dpi", "Xft.Dpi", &type, &value))
					{
						if (type && strcmp(type, "String") == 0)
							xdpi = ydpi = atof(cast(char*)value.addr);
					}

					X.XrmDestroyDatabase(db);
				}
			}

			_contentScale.x = xdpi / 96.0f;
			_contentScale.y = ydpi / 96.0f;
		}
	}

	~this()
	{
		if(_display)
		{
			X.XCloseDisplay(_display);
			_display = null;
		}
	}

	static X11Backend get()
	{
		if(!_instance)
			_instance = new X11Backend();
		return _instance;
	}

	static X.Display* display() @property { return _instance._display; }
	static int screen() @property { return _instance._screen; }
	static X.Window root() @property { return _instance._root; }

private:
	private static X11Backend _instance;
	X.Display* _display;
	X.Window _root;
	int _screen;
	Vector2f _contentScale;
	X.XContext _context;
}