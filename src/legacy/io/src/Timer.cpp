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

#include <AuroraFW/IO/Timer.h>
#include <AuroraFW/CoreLib/Type.h>

namespace AuroraFW {
	namespace IO {
		Timer::Timer()
		{
			#ifdef AFW_TARGET_PLATFORM_WINDOWS
			LARGE_INTEGER freq;
			QueryPerformanceFrequency(&freq);
			_frequency = 1.0 / freq.QuadPart;
			#endif

			reset();
		}

		void Timer::reset()
		{
			#ifdef AFW_TARGET_PLATFORM_WINDOWS
			QueryPerformanceCounter(&_start);
			#elif defined(AFW_TARGET_ENVIRONMENT_POSIX)
			_start = HighResolutionClock::now();
			#endif
		}

		float Timer::elapsed()
		{
			#ifdef AFW_TARGET_PLATFORM_WINDOWS
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			uint64_t cycles = current.QuadPart - _start.QuadPart;
			return (float)(cycles * _frequency);
			#elif defined(AFW_TARGET_ENVIRONMENT_POSIX)
			return elapsedMillis() / 1000.0f;
			#endif
		}

		float Timer::elapsedMillis()
		{
			#ifdef AFW_TARGET_PLATFORM_WINDOWS
			return elapsed() * 1000.0f;
			#elif defined(AFW_TARGET_ENVIRONMENT_POSIX)
			return std::chrono::duration_cast<milliseconds_type>(HighResolutionClock::now() - _start).count();
			#endif
		}
	}
}
