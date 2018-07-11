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
