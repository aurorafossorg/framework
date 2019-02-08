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

//TODO: Need to be documented

#ifndef AURORAFW_CORELIB_TARGET_SYSTEM_H
#define AURORAFW_CORELIB_TARGET_SYSTEM_H

#include <AuroraFW/CoreLib/Target/Compiler.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#if defined(__linux__) || defined(__linux) || defined(linux)
	#define AFW_TARGET_KERNEL_LINUX
#elif defined(AFW_TARGET_PLATFORM_WINDOWS)
	#define AFW_TARGET_KERNEL_NT
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
	#define AFW_TARGET_KERNEL_FREEBSD
#elif defined(__OpenBSD__)
	#define AFW_TARGET_KERNEL_OPENBSD
#elif defined(__NetBSD__)
	#define AFW_TARGET_KERNEL_NETBSD
#elif defined(__DragonFly__)
	#define AFW_TARGET_KERNEL_DRAGONFLY
#endif

#if defined(__unix__) || defined(__unix) || defined(unix)
	#define AFW_TARGET_ENVIRONMENT_UNIX
#elif defined(__CYGWIN__)
	#define AFW_TARGET_CYGWIN
#endif

#if defined(AFW_TARGET_ENVIRONMENT_UNIX) || defined(AFW_TARGET_PLATFORM_APPLE_MAC)
	#define AFW_TARGET_ENVIRONMENT_POSIX
#endif

#ifdef _WIN16
	#define AFW_TARGET_PLATFORM_WINDOWS
	#define AFW_TARGET_PLATFORM_WINDOWS_16
#elif defined(_WIN32)
	#define AFW_TARGET_PLATFORM_WINDOWS
	#define AFW_TARGET_PLATFORM_WINDOWS_32
	#ifdef _WIN64
		#define AFW_TARGET_PLATFORM_WINDOWS_86_64
	#endif
#elif __APPLE__
	#define AFW_TARGET_PLATFORM_APPLE
	#if defined(__APPLE_CPP__) || defined(__APPLE_CC__) || defined(__MACOS_CLASSIC__)
		#if (defined(__APPLE__) && defined(__MACH__)) || defined(macintosh) || defined(Macintosh)
			#define AFW_TARGET_PLATFORM_APPLE_MAC
		#endif
		#if defined(__GNUC__)
			#if 0
				#define INTERNAL_AFW_TARGET_PLATFORM_OS_EMBEDDED          @CONFIG_EMBEDDED@
				#define INTERNAL_AFW_TARGET_PLATFORM_OS_IPHONE            @CONFIG_IPHONE@
				#define INTERNAL_AFW_TARGET_PLATFORM_IPHONE_SIMULATOR     @CONFIG_IPHONE_SIMULATOR@
				#if INTERNAL_AFW_TARGET_PLATFORM_IPHONE_SIMULATOR
					#define AFW_TARGET_PLATFORM_APPLE_IPHONE_SIMULATOR
				#elif INTERNAL_AFW_TARGET_PLATFORM_OS_IPHONE
					#define AFW_TARGET_PLATFORM_APPLE_IPHONE
				#elif INTERNAL_AFW_TARGET_PLATFORM_OS_EMBEDDED
					#define AFW_TARGET_PLATFORM_APPLE_EMBEDDED
				#endif
				#undef INTERNAL_AFW_TARGET_PLATFORM_OS_EMBEDDED
				#undef INTERNAL_AFW_TARGET_PLATFORM_OS_IPHONE
				#undef INTERNAL_AFW_TARGET_PLATFORM_IPHONE_SIMULATOR
			#endif
		#endif
	#endif
#elif defined(AFW_TARGET_KERNEL_LINUX)
	#ifdef __gnu_linux__
		#define AFW_TARGET_PLATFORM_GNU_LINUX
	#endif
#elif defined(__ANDROID__)
	#define AFW_TARGET_PLATFORM_ANDROID
#endif

#endif // AURORAFW_CORELIB_TARGET_SYSTEM_H
