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

#ifndef AURORAFW_STDL_LIBC_MATH_H
#define AURORAFW_STDL_LIBC_MATH_H

#include <AuroraFW/CoreLib/Target/Compiler.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/STDL/Internal/Config.h>

//#undef AFW_STDLIB_CC
//#define AFW_STDLIB_CC 0
#include <AuroraFW/STDL/Internal/LibC/Math.h>

#if (AFW_STDLIB_CC == 0) || !defined(AURORAFW_STDL_LIBC__MATH_H)

#include <AuroraFW/CoreLib/Target/Compiler.h>
#include <AuroraFW/CoreLib/Target/Language.h>

/** @def NAN
 * Represents a NaN. Define a non-a-number macro for NULL floating-point number.
 * @hideinitializer
 * @since snapshot20171005
*/
#ifndef NAN
	#ifdef AFW_TARGET_COMPILER_GNU
		#define NAN __builtin_nan("")
	#else
		#define NAN (0.0F/0.0F)
	#endif
#endif // NAN

/** @def __AFW_FLT_EVAL_METHOD
 * Define the float_t and double_t.
 * This floating-point types is used to evaluate floating-point expressions
 * and is at least as wide as your floating-point types.
 * @exception null unknown floating-point evaluation method
 * @hideinitializer
 * @since snapshot20171005
 */
#ifdef __FLT_EVAL_METHOD__
	#if __FLT_EVAL_METHOD__ == -1
		#define __AFW_FLT_EVAL_METHOD 2
	#else
		#define __AFW_FLT_EVAL_METHOD __FLT_EVAL_METHOD__
	#endif
#elif defined AFW_TARGET_ARCH_X86_64
	#define __AFW_FLT_EVAL_METHOD 0
#else
	#define __AFW_FLT_EVAL_METHOD 2
#endif

/** @var float_t
* Define an efficient floating-point type to evaluate floating-point expressions.
*/
/** @var double_t
* Define a efficient floating-point type to evaluate floating-point expressions.
*/
#ifdef AFW_TARGET_C99
	#if __AFW_FLT_EVAL_METHOD == 0 || __AFW_FLT_EVAL_METHOD == 16
		typedef float float_t;
		typedef double double_t;
	#elif __AFW_FLT_EVAL_METHOD == 1
		typedef double float_t;
		typedef double double_t;
	#elif __AFW_FLT_EVAL_METHOD == 2
		typedef long double float_t;
		typedef long double double_t;
	#elif __AFW_FLT_EVAL_METHOD == 32
		typedef _Float32 float_t;
		typedef double double_t;
	#elif __AFW_FLT_EVAL_METHOD == 33
		typedef _Float32x float_t;
		typedef _Float32x double_t;
	#elif __AFW_FLT_EVAL_METHOD == 64
		typedef _Float64 float_t;
		typedef _Float64 double_t;
	#elif __AFW_FLT_EVAL_METHOD == 65
		typedef _Float64x float_t;
		typedef _Float64x double_t;
	#elif __AFW_FLT_EVAL_METHOD == 128
		typedef _Float128 float_t;
		typedef _Float128 double_t;
	#elif __AFW_FLT_EVAL_METHOD == 129
		typedef _Float128x float_t;
		typedef _Float128x double_t;
	#else
		#error "Unknown floating-point evaluation method"
	#endif
#endif

#endif

#endif // AURORAFW_STDL_LIBC_MATH_H