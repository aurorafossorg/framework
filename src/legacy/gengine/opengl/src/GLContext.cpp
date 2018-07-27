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

#include <AuroraFW/GEngine/GL/Context.h>

 #include <stdexcept>

namespace AuroraFW {
	namespace GEngine {
		GLContext::GLContext(WindowProperties wp)
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
			#ifdef AFW__DEBUG
				glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
				glEnable(GL_DEBUG_OUTPUT);
				glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			#endif


			if(wp.samples > 1) {
				GLCall(glEnable(GL_MULTISAMPLE));
				GLCall(glEnable(GL_MULTISAMPLE_ARB));
			}

			//GLCall(glEnable(GL_CULL_FACE));
			//GLCall(glCullFace(GL_BACK));

			//GLCall(glEnable(GL_DEPTH_TEST));
			//GLCall(glEnable(GL_MULTISAMPLE));
			//GLCall(glEnable(GL_SAMPLE_SHADING));
		}

		void GLContext::_init(GLFWwindow* )
		{
			glewExperimental = GL_TRUE;

			if(glewInit() != GLEW_OK) {
				throw std::runtime_error("failed to initialize GLEW!");
			}
		}

		void GLContext::_destroy()
		{}
	}
}
