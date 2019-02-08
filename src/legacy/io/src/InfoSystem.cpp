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
