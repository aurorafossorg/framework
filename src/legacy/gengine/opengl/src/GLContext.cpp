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
