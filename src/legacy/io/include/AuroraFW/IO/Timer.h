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

#ifndef AURORAFW_IO_TIMER_H
#define AURORAFW_IO_TIMER_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/CoreLib/Target/System.h>

#ifdef AFW_TARGET_ENVIRONMENT_POSIX
#include <chrono>
#elif defined(AFW_TARGET_PLATFORM_WINDOWS)
#include <Windows.h>
#endif

namespace AuroraFW {
	namespace IO {
		#ifdef AFW_TARGET_ENVIRONMENT_POSIX
		typedef std::chrono::high_resolution_clock HighResolutionClock;
		typedef std::chrono::duration<float, std::milli> milliseconds_type;
		#endif

		class AFW_API Timer
		{
		private:
			#ifdef AFW_TARGET_ENVIRONMENT_POSIX
			std::chrono::time_point<HighResolutionClock> _start;
			#elif defined(AFW_TARGET_PLATFORM_WINDOWS)
			LARGE_INTEGER _start;
			double _frequency;
			#endif

		public:
			Timer();
			void reset();
			float elapsed();
			float elapsedMillis();
		};
	}
}

#endif // AURORAFW_IO_TIMER_H