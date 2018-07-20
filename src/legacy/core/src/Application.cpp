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

#include <AuroraFW/Core/Application.h>
#include <AuroraFW/CLI/Log.h>
#include <AuroraFW/Core/DebugManager.h>

#include <AuroraFW/STDL/STL/IOStream.h>

namespace AuroraFW {
	Application::Application(int argc, char *argv[], void (*mainFunction)(Application*))
	{
		args = AFW_NEW std::vector<std::string>(argv + 1, argv + argc);
		for (std::vector<std::string>::iterator i = args->begin(); i != args->end(); ++i) {
			if(*i == "--afw-debug")
				DebugManager::enable();
		}
		DebugManager::Log("creating new application");
		DebugManager::Log("application is created.");
		(*mainFunction)(this);
	}
	Application::~Application()
	{
		delete args;
		DebugManager::Log("application is destroyed.");
	}
	void Application::ExitSuccess()
	{
		DebugManager::Log("application return success code: ", EXIT_SUCCESS);
		exit(EXIT_SUCCESS);
	}
	void Application::ExitFail()
	{
		DebugManager::Log("application return error code: ", EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
}
