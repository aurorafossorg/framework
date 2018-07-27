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