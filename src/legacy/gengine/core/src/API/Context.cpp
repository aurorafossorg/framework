/*****************************************************************************
**                                    / _|
**   __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
**  / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
** | (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
**  \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/
**
** Copyright (C) 2018 Aurora Free Open Source Software.
**
** This file is part of the Aurora Free Open Source Software. This
** organization promote free and open source software that you can
** redistribute and/or modify under the terms of the GNU Lesser General
** Public License Version 3 as published by the Free Software Foundation or
** (at your option) any later version approved by the Aurora Free Open Source
** Software Organization. The license is available in the package root path
** as 'LICENSE' file. Please review the following information to ensure the
** GNU Lesser General Public License version 3 requirements will be met:
** https://www.gnu.org/licenses/lgpl.html .
**
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3 or later as published by the Free Software
** Foundation. Please review the following information to ensure the GNU
** General Public License requirements will be met:
** http://www.gnu.org/licenses/gpl-3.0.html.
**
** NOTE: All products, services or anything associated to trademarks and
** service marks used or referenced on this file are the property of their
** respective companies/owners or its subsidiaries. Other names and brands
** may be claimed as the property of others.
**
** For more info about intellectual property visit: aurorafoss.org or
** directly send an email to: contact (at) aurorafoss.org .
*****************************************************************************/

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
