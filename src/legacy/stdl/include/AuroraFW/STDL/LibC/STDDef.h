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

#ifndef AURORAFW_STDL_LIBC_STDDEF_H
#define AURORAFW_STDL_LIBC_STDDEF_H

#include <AuroraFW/CoreLib/Target/Compiler.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/STDL/Internal/Config.h>

//#undef AFW_STDLIB_CC
//#define AFW_STDLIB_CC 0
#include <AuroraFW/STDL/Internal/LibC/STDDef.h>

#if (AFW_STDLIB_CC == 0) || !defined(AURORAFW_STDL_LIBC__STDDEF_H)

#include <AuroraFW/CoreLib/Target/Compiler.h>
#include <AuroraFW/CoreLib/Target/Language.h>
#include <AuroraFW/CoreLib/Target/DataModel.h>

#undef NULL
#if defined(AFW_TARGET_COMPILER_GNU_GXX) || (!defined(AFW_TARGET_COMPILER_MINGW) && !defined(AFW_TARGET_COMPILER_MICROSOFT))
	#define NULL __null
#else
	#ifdef AFW_TARGET_CXX
		#ifdef AFW_TARGET_CXX_11
			#define NULL nullptr
		#else
			#define NULL 0
		#endif
	#else
		#define NULL ((void *)0)
	#endif
#endif

#ifdef AFW_TARGET_DATAMODEL_LP64
	typedef unsigned long long int size_t;
#else
	typedef unsigned long int size_t;
#endif

#endif

#ifdef AFW_TARGET_CXX
	namespace afwstd {	
		enum class byte : unsigned char {};
	#ifdef AFW_TARGET_CXX_11
		typedef decltype(nullptr) nullptr_t;
	#endif
	}
#endif

#endif // AURORAFW_STDL_LIBC_STDDEF_H