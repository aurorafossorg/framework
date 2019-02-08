/*****************************************************************************
**                                     __
**                                    / _|
**   __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
**  / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
** | (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
**  \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/
**
** Copyright (C) 2018-2019 Aurora Free Open Source Software.
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

#include <AuroraFW/GEngine/Window.h>
#include <AuroraFW/Core/DebugManager.h>
#include <AuroraFW/GEngine/API/Context.h>

#include <AuroraFW/GUI/Application.h>
#include <AuroraFW/GUI/Window.h>
#include <AuroraFW/GUI/Button.h>
#include <AuroraFW/GUI/Label.h>

#include <AuroraFW/CoreLib/Callback.h>

namespace AuroraFW {
	namespace GEngine {
		Window::Window(std::string name, const WindowProperties wp)
			: _monitor(glfwGetPrimaryMonitor()), _name(name), wp(wp)
		{
			if(wp.windowSettingsDialog)
				_openWindowSettingsDialog();

			if (!glfwInit())
				throw std::runtime_error("failed to initialize GLFW!");

			const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

			glfwDefaultWindowHints();

			glfwWindowHint(GLFW_SAMPLES, wp.samples);
			glfwWindowHint(GLFW_DOUBLEBUFFER, wp.doubleBuffer);
			glfwWindowHint(GLFW_SRGB_CAPABLE, wp.sRGB);
			glfwWindowHint(GLFW_STEREO, wp.stereo);
			glfwWindowHint(GLFW_RESIZABLE, wp.resizable);
			glfwWindowHint(GLFW_VISIBLE, wp.visible);
			glfwWindowHint(GLFW_DECORATED, wp.decorated);
			glfwWindowHint(GLFW_FOCUSED, wp.focused);
			glfwWindowHint(GLFW_AUTO_ICONIFY, wp.autoIconify);
			glfwWindowHint(GLFW_REFRESH_RATE, wp.refreshRate);
			glfwWindowHint(GLFW_AUX_BUFFERS, wp.auxBuffers);
			glfwWindowHint(GLFW_FLOATING, wp.floating);
			glfwWindowHint(GLFW_MAXIMIZED, wp.maximized);

			API::Context::create(wp, _name);

			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

			if(wp.width == 0 || wp.height == 0) {
				this->wp.width = mode->width;
				this->wp.height = mode->height;
			}

			if(wp.fullscreen) {
				if(wp.vsync) {
					window = glfwCreateWindow(wp.width, wp.height, _name.c_str(), glfwGetPrimaryMonitor(), NULL);
					glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, wp.width, wp.height, mode->refreshRate);
				}
				else {
					window = glfwCreateWindow(wp.width, wp.height, _name.c_str(), glfwGetPrimaryMonitor(), NULL);
				}
			} else {
				if(wp.vsync) {
					window = glfwCreateWindow(wp.width, wp.height, _name.c_str(), NULL, NULL);
					glfwSetWindowMonitor(window, NULL, 0, 0, wp.width, wp.height, mode->refreshRate);
				}
				else {
					window = glfwCreateWindow(wp.width, wp.height, _name.c_str(), NULL, NULL);
				}
			}

			if (!window) {
				glfwTerminate();
				throw std::runtime_error("failed to create window!");
			} else {
				_isCreated = true;
			}

			/* Make the window's context current */
			glfwMakeContextCurrent(window);

			API::Context::init(window);
		}

		Window::~Window()
		{
			API::Context::destroy();
			glfwDestroyWindow(window);
			glfwTerminate();
		}

		void Window::update()
		{
			if(!wp.vsync) glfwSwapInterval(0);
			// Swap front and back buffers
			if(wp.swapBuffers) glfwSwapBuffers(window);
		}

		void Window::present()
		{
			// Poll for and process events
			glfwPollEvents();
			glfwGetFramebufferSize(window, (int*)&wp.width, (int*)&wp.height);
		}

		bool Window::isClosed() const
		{
			return glfwWindowShouldClose(window) == 1;
		}

		void Window::_openWindowSettingsDialog()
		{
			
		}
	}
}
