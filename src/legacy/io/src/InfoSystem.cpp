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

#include <AuroraFW/IO/Info/System.h>

#include <AuroraFW/CoreLib/Target/System.h>
#include <AuroraFW/CoreLib/Target/Architecture.h>

#ifdef AFW_TARGET_PLATFORM_GNU_LINUX
#include <sys/utsname.h>
#elif defined(AFW_TARGET_KERNEL_NT)
#include <windows.h>
#endif

#ifdef AFW_TARGET_PLATFORM_ANDROID
	#include <android/api-level.h>
#endif

namespace AuroraFW {
	namespace IO {
		namespace Info {
			std::string getOSManufacturer()
			{
				#ifdef AFW_TARGET_PLATFORM_WINDOWS
					return "Microsoft Corporation";
				#elif defined(AFW_TARGET_PLATFORM_APPLE)
					return "Apple Inc.";
				#else
					return "Unknown Manufacturer";
				#endif
			}
			std::string getArchitecture()
			{
				#ifdef AFW_TARGET_PLATFORM_GNU_LINUX
					struct utsname linuxname_temp;
					uname(&linuxname_temp);
					return std::string(linuxname_temp.machine);
				#else
					#ifdef AFW_TARGET_CPUARCH_INTELX86
						return "x86 32-bit";
					#elif defined(AFW_TARGET_CPUARCH_AMD64)
						return "x86 64-bit";
					#elif defined(AFW_TARGET_CPUARCH_ARM)
						return "ARM";
					#else
						return "Unknown Architecture";
					#endif
				#endif
			}
			
			std::string getOSName()
			{
				#ifdef AFW_TARGET_PLATFORM_WINDOWS
					return "Microsoft Windows";
				#elif defined(AFW_TARGET_PLATFORM_GNU_LINUX)
					struct utsname linuxname_temp;
					uname(&linuxname_temp);
					return std::string(linuxname_temp.sysname);
				#elif defined(AFW_TARGET_PLATFORM_ANDROID)
					return "Android";
				#else
					return "Unknown Operation System";
				#endif
			}

			std::string getOSVersion()
			{
				// TODO: Get Version for Windows Platforms
				#ifdef AFW_TARGET_PLATFORM_GNU_LINUX
					struct utsname linuxname_temp;
					uname(&linuxname_temp);
					return std::string(linuxname_temp.release) + std::string(linuxname_temp.version);
				#else
					return "Unknown Version";
				#endif
			}

			std::string getUserComputerName()
			{
				// TODO: Get User computer name for others platforms
				#ifdef AFW_TARGET_PLATFORM_GNU_LINUX
					struct utsname linuxname_temp;
					uname(&linuxname_temp);
					return std::string(linuxname_temp.nodename);
				#elif defined(AFW_TARGET_PLATFORM_WINDOWS)
					return "Unknown"; // Temporary
				#else
					return "Unknown";
				#endif
			}
		}
	}
}
