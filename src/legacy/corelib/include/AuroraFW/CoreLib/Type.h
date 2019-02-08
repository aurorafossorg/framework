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

//TODO: Need to be documented and structured

#ifndef AURORAFW_TLIB_TYPE_H
#define AURORAFW_TLIB_TYPE_H

#include <AuroraFW/CoreLib/Target/Compiler.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/STDL/LibC/Math.h>
#include <AuroraFW/STDL/LibC/STDDef.h>

#define AFW_DONTCARE -1

//Floating-point types
#include <AuroraFW/STDL/LibC/Float.h>

#define AFW_NAN NA

typedef long double real_t;
typedef unsigned char uchar_t;
typedef uchar_t byte_t;

//Boolean types
#include <AuroraFW/STDL/LibC/STDBool.h>

//Integer types
#include <AuroraFW/STDL/LibC/STDInt.h>

#define AFW_NULL NULL
#define AFW_NULLPTR nullptr
#define AFW_NULLVAL 0

typedef unsigned int uint_t;
typedef unsigned int uint;

typedef unsigned short int ushort;

#ifdef AFW_TARGET_PLATFORM_WINDOWS
typedef __int8 int8;
typedef __int16 int16;
typedef __int32 int32;
typedef __int64 int64;

typedef int8 int8_t;
typedef int16 int16_t;
typedef int32 int32_t;
typedef int64 int64_t;

typedef unsigned __int8 uint8;
typedef unsigned __int16 uint16;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;

typedef uint8 uint8_t;
typedef uint16 uint16_t;
typedef uint32 uint32_t;
typedef uint64 uint64_t;
#endif

#if AFW_DOUBLE_PRECISION == 2
	typedef real_t afw_real;
#elif AFW_DOUBLE_PRECISION == 1
	typedef double afw_real;
#else
	typedef float afw_real;
#endif

#ifdef AFW_TARGET_CXX
	namespace afw {
		typedef afw_real real;
	}
#endif

#endif // AURORAFW_TLIB_TYPE_H
