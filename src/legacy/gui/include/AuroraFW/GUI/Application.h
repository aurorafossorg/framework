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

#ifndef AURORAFW_GUI_APPLICATION_H
#define AURORAFW_GUI_APPLICATION_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/Core/Application.h>

#include <functional>

typedef struct _GtkApplication GtkApplication;

namespace AuroraFW {
	namespace GUI {
		class AFW_API Application
		{
		public:
			enum ApplicationFlags
			{
				NoneFlag,
				ServiceFlag,
				LauncherFlag,
				HandlesOpenFlag,
				HandlesCommandLineFlag,
				SendEnvironmentFlag,
				NonUniqueFlag,
				OverrideAppIDFlag
			};

			template<typename R, typename... Args>
			Application(const std::string &pkgname = "org.aurora.example", const ApplicationFlags &flags = NoneFlag, R(*)(Args...) = []{}, int argc = 0, char **argv = NULL);
			~Application();

			Application(const Application &) = delete;
			Application &operator=(const Application &) = delete;
			inline int getStatus() const { return _appStatus; }
			GtkApplication* getNativeGtkApplication() const { return _app; }

			template<typename R, typename... Args>
			void connect(const std::string& , R(*)(Args...), void* = AFW_NULLPTR);

			template<typename R, typename... Args>
			inline void connect(const std::string& signal_, std::function<R(Args...)> callback, void* data = AFW_NULLPTR)
			{ connect(signal_, *getCallbackPtr(callback), data); }

		private:
			GtkApplication* _app;
			int _appStatus;
		};
	}
}

#include "Application_impl.h"

#endif // AURORAFW_GUI_APPLICATION
