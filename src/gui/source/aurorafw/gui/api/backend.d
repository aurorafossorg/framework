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

module aurorafw.gui.api.backend;

version(linux)
{
	import aurorafw.gui.api.wayland.backend;
	import aurorafw.gui.api.x11.backend;

	enum BackendType {
		X11,
		Wayland
	}
} else version(OSX)
{
	enum BackendType {
		X11,
		Quartz
	}
} else version(Windows)
{
	enum BackendType {
		DWM
	}
}

pure class Backend {
	public static Backend get()
	{
		if(!instance)
		{
			version(linux) {
				import std.process : environment;
				import aurorafw.gui.api.x11.backend : X11Backend;
				import aurorafw.gui.api.wayland.backend : WLBackend;
				immutable auto xdg_session_type = environment.get("XDG_SESSION_TYPE");
				if(xdg_session_type == "x11")
					instance = new X11Backend();
				else if(xdg_session_type == "wayland")
					instance = new WLBackend();
			} else {
				throw new NotImplementedException("Not yet implemented on this platform!");
			}
		}
		return instance;
	}

	public @property BackendType type()
	{
		return _type;
	}

	protected BackendType _type;

	private static Backend instance;
}
