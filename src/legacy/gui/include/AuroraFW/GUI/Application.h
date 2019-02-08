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
