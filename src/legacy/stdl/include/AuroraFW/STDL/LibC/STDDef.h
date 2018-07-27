/*****************************************************************************
**                                    / _|
**   __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
**  / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
** | (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
**  \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/
**
** Copyright (C) 2018 Aurora Free Open Source Software.
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