/*
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

module aurorafw.graphics.api.context;

import aurorafw.graphics.api.opengl.context : GLContext;
import aurorafw.graphics.api.vulkan.context : VKContext;
import aurorafw.gui.window;

abstract class Context {
	enum RenderAPI {
		OpenGL,
		Direct3D,
		Vulkan
	}

	enum RenderAPIVersion : uint {
		Unknown = 0,
		GL_2_0,
		GL_2_1,
		GL_3_0,
		GL_3_1,
		GL_3_2,
		GL_3_3,
		GL_3_3_CORE
	}

	static void create(WindowProperties wp, string name)
	{
		switch(getRenderAPI())
		{
			case RenderAPI.OpenGL: _instance = new GLContext(wp); break;
			case RenderAPI.Vulkan: _instance = new VKContext(name); break;
			default: assert(0);
		}
	}

	static void init(Window win)
	{
		_instance._init(win);
	}

	static void destroy()
	{
		_instance._destroy();
	}

	pragma(inline) static RenderAPI getRenderAPI()
	{
		return _rapi;
	}

	pragma(inline) static RenderAPIVersion getAPIVersion()
	{
		return _version;
	}

	pragma(inline) static void setRenderAPI(RenderAPI api)
	{
		_rapi = api;
	}

protected:
	void _init(Window );
	void _destroy();

	static Context _instance;
	static RenderAPI _rapi = RenderAPI.OpenGL;
	static RenderAPIVersion _version;
}