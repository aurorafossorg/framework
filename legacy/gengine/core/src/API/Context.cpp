/****************************************************************************
** ┌─┐┬ ┬┬─┐┌─┐┬─┐┌─┐  ┌─┐┬─┐┌─┐┌┬┐┌─┐┬ ┬┌─┐┬─┐┬┌─
** ├─┤│ │├┬┘│ │├┬┘├─┤  ├┤ ├┬┘├─┤│││├┤ ││││ │├┬┘├┴┐
** ┴ ┴└─┘┴└─└─┘┴└─┴ ┴  └  ┴└─┴ ┴┴ ┴└─┘└┴┘└─┘┴└─┴ ┴
** A Powerful General Purpose Framework
** More information in: https://aurora-fw.github.io/
**
** Copyright (C) 2017 Aurora Framework, All rights reserved.
**
** This file is part of the Aurora Framework. This framework is free
** software; you can redistribute it and/or modify it under the terms of
** the GNU Lesser General Public License version 3 as published by the
** Free Software Foundation and appearing in the file LICENSE included in
** the packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************/

#include <AuroraFW/GEngine/API/Context.h>

#include <AuroraFW/GEngine/GL/Context.h>
#include <AuroraFW/GEngine/Vulkan/Context.h>

namespace AuroraFW {
	namespace GEngine {
		namespace API {
			RenderAPI Context::_rapi = RenderAPI::OpenGL;
			Context *Context::_instance = AFW_NULLPTR;

			void Context::create(WindowProperties wp, std::string& name)
			{
				switch(getRenderAPI())
				{
					case RenderAPI::OpenGL: _instance = AFW_NEW GLContext(wp); break;
					case RenderAPI::Vulkan: _instance = AFW_NEW VKContext(name); break;
				}
			}

			void Context::init(GLFWwindow* window)
			{
				_instance->_init(window);
			}

			void Context::destroy()
			{
				_instance->_destroy();
			}
		}
	}
}
