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

#ifndef AURORAFW_STDL_LIBC_STRING_H
#define AURORAFW_STDL_LIBC_STRING_H

#include <AuroraFW/CoreLib/Target/Compiler.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/STDL/Internal/Config.h>
#include <AuroraFW/STDL/Internal/LibC/String.h>

#if (AFW_STDLIB_CC == 0) || !defined(AURORAFW_STDL_LIBC__STRING_H) || defined(AFW_TARGET_CXX)
	#include <AuroraFW/STDL/LibC/STDDef.h>
	
	#ifdef AFW_TARGET_CXX
		extern "C" {
	#endif
		void *memcpy(void *dst, const void *src, size_t n);
		void *memmove(void *dst, const void *src, size_t n);
		int memcmp(const void *cs, const void *ct, size_t n);
		void *memset(void *s, const int c, size_t n);
	#ifdef AFW_TARGET_CXX
		}
		namespace afwstd {
			using ::memcpy;
			using ::memmove;
			using ::memcmp;
			using ::memset;
		}
	#endif
#endif

#endif // AURORAFW_STDL_LIBC_STRING_H