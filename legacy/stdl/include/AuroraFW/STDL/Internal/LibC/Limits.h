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

#ifndef AURORAFW_STDL_LIBC__LIMITS_H
#define AURORAFW_STDL_LIBC__LIMITS_H

#include <AuroraFW/CoreLib/Target/Compiler.h>

#if !defined(AURORAFW_STDL_LIBC_LIMITS_H) && !defined(AFW__PHC)
	#error "Don't include this header directly, include AuroraFW/STDL/LibC/Limits.h instead"
#endif

#if AFW_STDLIB_CC == 1
	#ifdef AFW_TARGET_CC
		#include <limits.h>
	#elif defined(AFW_TARGET_CXX)
		#include <climits>
	#endif
#endif // AFW_STDLIB_CC

#endif // AURORAFW_STDL_LIBC__LIMITS_H