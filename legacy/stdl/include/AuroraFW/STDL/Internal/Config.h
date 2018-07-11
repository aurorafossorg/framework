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

#ifndef AURORAFW_STDL_CONFIG_H
#define AURORAFW_STDL_CONFIG_H

#ifndef AFW_MODULE_STDL
	#define AFW_MODULE_STDL
#endif

/** @def AFW_STDLIB_CC
 * Define if aurora will use Standard C Library
 */
#define AFW_STDLIB_CC 1

/** @def AFW_STDLIB_CXX
 * Define if aurora will use C++ Standard Template Library
 */
#define AFW_STDLIB_CXX 1

#ifdef AFW__FORCE_STDLIB
	#undef AFW_STDLIB_CC
	#define AFW_STDLIB_CC 1

	#undef AFW_STDLIB_CXX
	#define AFW_STDLIB_CXX 1
#endif // AFW__FORCE_STDLIB

#ifdef AFW__FORCE_NO_STDLIB
	#ifdef AFW__FORCE_STDLIB
		#error "AFW__FORCE_STDLIB and AFW__FORCE_NO_STDLIB both defined!"
	#endif
	#undef AFW_STDLIB_CC
	#define AFW_STDLIB_CC 0
	
	#undef AFW_STDLIB_CXX
	#define AFW_STDLIB_CXX 0
#endif // AFW__FORCE_NO_STDLIB

#ifdef AFW__FORCE_STDLIB_CC
	#undef AFW_STDLIB_CC
	#define AFW_STDLIB_CC 1
#endif // AFW__FORCE_STDLIB_CC

#ifdef AFW__FORCE_NO_STDLIB_CC
	#ifdef AFW__FORCE_STDLIB_CC
	#error "AFW__FORCE_STDLIB_CC and AFW__FORCE_NO_STDLIB_CC both defined!"
	#endif
	#undef AFW_STDLIB_CC
	#define AFW_STDLIB_CC 0
#endif // AFW__FORCE_NO_STDLIB_CC

#ifdef AFW__FORCE_STDLIB_CXX
#undef AFW_STDLIB_CXX
#define AFW_STDLIB_CXX 1
#endif // AFW__FORCE_STDLIB_CXX

#ifdef AFW__FORCE_NO_STDLIB_CXX
	#ifdef AFW__FORCE_STDLIB_CXX
		#error "AFW__FORCE_STDLIB_CXX and AFW__FORCE_NO_STDLIB_CXX both defined!"
	#endif
	#undef AFW_STDLIB_CXX
	#define AFW_STDLIB_CXX 0
#endif // AFW__FORCE_NO_STDLIB_CXX

#if AFW_STDLIB_CXX == 0
	#ifdef AFW_TARGET_CXX
		namespace std = ::afwstd;
	#endif
#endif

#endif // AURORAFW_STDL_CONFIG_H