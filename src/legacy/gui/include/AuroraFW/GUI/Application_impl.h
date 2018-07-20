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

#ifndef AURORAFW_GUI_APPLICATION_IMPL_H
#define AURORAFW_GUI_APPLICATION_IMPL_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/GUI/_GTK.h>
#include <AuroraFW/Core/DebugManager.h>
#include <AuroraFW/CoreLib/Callback.h>
#include <functional>

namespace AuroraFW {
	namespace GUI {
		template<typename R, typename... Args>
		Application::Application(const std::string& pkgname, const ApplicationFlags& flags, R(*mainfunction)(Args...), int argc, char **argv)
			: _app(gtk_application_new (pkgname.c_str(), (GApplicationFlags)flags))
		{
			DebugManager::Log("creating a new application...");
			DebugManager::Log("application is created.");
			
			connect("activate", mainfunction);
			_appStatus = g_application_run(G_APPLICATION(_app), argc, argv);
		}

		template<typename R, typename... Args>
		void Application::connect(const std::string& signal_, R(*callback)(Args...), void* data)
		{
			DebugManager::Log("creating new signal on widget");
			g_signal_connect(_app, signal_.c_str(), G_CALLBACK(callback), data);
		}
	}
}

#endif // AURORAFW_GUI_APPLICATION_IMPL_H