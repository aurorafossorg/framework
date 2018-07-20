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

#ifndef AURORAFW_CORE_DEBUG_H
#define AURORAFW_CORE_DEBUG_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/STDL/STL/IOStream.h>

namespace AuroraFW {
	class AFW_API DebugManager {
		private:
			static bool _status;

			template <typename T>
			static void _Log(const T& t)
			{
				std::cout << t;
			}

			template <typename T, typename... R>
			static void _Log(const T& t, const R&... args)
			{
				std::cout << t;
				_Log(args...);
			}

		public:
			static void enable(const bool& silent = false);
			static void disable(const bool& silent = false);
			inline static bool getStatus() { return _status; }

			template <typename... T>
			static void Log(const T&... args)
			{
				// TODO: Windows ANSI integration
				//       Needs to be tested on Windows and Apple platforms
				if(_status)
				{
					//Temporary code
					#ifdef AFW_TARGET_ENVIRONMENT_UNIX
						std::cout << "\033[0m\033[1m[\033[1;36mDEBUG\033[0;1m] \033[0m";
					#else
						std::cout << "[DEBUG] ";
					#endif
					_Log(args...);
					std::cout << std::endl;
					return;
				}
			}
	};
}

#endif // AURORAFW_CORE_DEBUG_H
