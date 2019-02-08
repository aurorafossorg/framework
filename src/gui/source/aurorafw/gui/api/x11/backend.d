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

import aurorafw.gui.api.backend;

pure class X11Backend : Backend {
	this()
	{
		super._type = BackendType.X11;

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

		// get system content scale
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

		//init x11 extensions
		// TODO

		X.XSetWindowAttributes wa;
		wa.event_mask = X.PropertyChangeMask;

		_helperWindowHandle = X.XCreateWindow(_display, _root,
			0, 0, 1, 1, 0, 0,
			X.InputOnly,
			X.XDefaultVisual(_display, _screen),
			X.CWEventMask, &wa);
		
		immutable byte[16 * 16 * 4] pixels;
		_hiddenCursorHandle = createXCursor(16, 16, pixels, 0, 0);

		if (X.XSupportsLocale())
		{
			X.XSetLocaleModifiers("");

			this._im = X.XOpenIM(_display, null, null, null);
			if (this._im)
			{
				bool found = false;
				X.XIMStyles* styles = null;

				if(X.XGetIMValues(_im, X.XNQueryInputStyle, &styles, null) == null)
				{
					for (uint i = 0; i < styles.count_styles; i++)
					{
						if (styles.supported_styles[i] == (X.XIMPreeditNothing | X.XIMStatusNothing))
						{
							found = true;
							break;
						}
					}

					X.XFree(styles);
				}

				if (!found)
				{
					X.XCloseIM(_im);
					this._im = null;
				}
			}
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

	X.Cursor createXCursor(immutable uint width, immutable uint height, immutable byte[] pixels, int xhot, int yhot)
	{
		X.Cursor cursor;

		if (!_xcursor_handle)
			return X.None;

		X.XcursorImage* native = X.XcursorImageCreate(width, height);
		if (native == null)
			return X.None;

		native.xhot = xhot;
		native.yhot = yhot;

		byte* source = cast(byte*) pixels;
		X.XcursorPixel* target = native.pixels;

		for (int i = 0; i < width * height; i++, target++, source += 4)
		{
			uint alpha = source[3];

			*target = (alpha << 24) |
					(cast(byte) ((source[0] * alpha) / 255) << 16) |
					(cast(byte) ((source[1] * alpha) / 255) <<  8) |
					(cast(byte) ((source[2] * alpha) / 255) <<  0);
		}

		cursor = X.XcursorImageLoadCursor(_display, native);
		X.XcursorImageDestroy(native);

		return cursor;
	}

	X.Display* display() @property { return _display; }
	int screen() @property { return _screen; }
	X.Window root() @property { return _root; }

private:
	X.Display* _display;
	X.Window _root;
	int _screen;
	Vector2f _contentScale;
	X.XContext _context;
	X.XIM _im;
	X.Window _helperWindowHandle;
	X.Cursor _hiddenCursorHandle;
	X.XCursorDylibLoader _xcursor_handle;
}