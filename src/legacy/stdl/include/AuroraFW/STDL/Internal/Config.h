/*****************************************************************************
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