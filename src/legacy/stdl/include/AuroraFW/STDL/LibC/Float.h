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

#ifndef AURORAFW_STDL_LIBC_FLOAT_H
#define AURORAFW_STDL_LIBC_FLOAT_H

#include <AuroraFW/CoreLib/Target/Compiler.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/STDL/Internal/Config.h>

//#undef AFW_STDLIB_CC
//#define AFW_STDLIB_CC 0
#include <AuroraFW/STDL/Internal/LibC/Float.h>

#if (AFW_STDLIB_CC == 0) || !defined(AURORAFW_STDL_LIBC__FLOAT_H)

/** @def FLT_RADIX
 * Radix of exponent representation, b.
 * @hideinitializer
 */
#undef FLT_RADIX
#define FLT_RADIX __FLT_RADIX__

/** @def FLT_MANT_DIG
 * Number of base-FLT_RADIX digits in the significand, p.
 * @hideinitializer
 */
#undef FLT_MANT_DIG
#define FLT_MANT_DIG __FLT_MANT_DIG__

/** @def DBL_MANT_DIG
 * @copydoc FLT_MANT_DIG
 * @hideinitializer
 */
#undef DBL_MANT_DIG
#define DBL_MANT_DIG __DBL_MANT_DIG__

/** @def LDBL_MANT_DIG
 * @copydoc FLT_MANT_DIG
 * @hideinitializer
 */
#undef LDBL_MANT_DIG
#define LDBL_MANT_DIG __LDBL_MANT_DIG__

#undef FLT_DIG
#define FLT_DIG __FLT_DIG__
#undef DBL_DIG
#define DBL_DIG __DBL_DIG__
#undef LDBL_DIG
#define LDBL_DIG __LDBL_DIG__

#undef FLT_MIN_EXP
#define FLT_MIN_EXP __FLT_MIN_EXP__
#undef DBL_MIN_EXP
#define DBL_MIN_EXP __DBL_MIN_EXP__
#undef LDBL_MIN_EXP
#define LDBL_MIN_EXP __LDBL_MIN_EXP__

#undef FLT_MIN_10_EXP
#define FLT_MIN_10_EXP __FLT_MIN_10_EXP__
#undef DBL_MIN_10_EXP
#define DBL_MIN_10_EXP __DBL_MIN_10_EXP__
#undef LDBL_MIN_10_EXP
#define LDBL_MIN_10_EXP __LDBL_MIN_10_EXP__

#undef FLT_MAX_EXP
#define FLT_MAX_EXP __FLT_MAX_EXP__
#undef DBL_MAX_EXP
#define DBL_MAX_EXP __DBL_MAX_EXP__
#undef LDBL_MAX_EXP
#define LDBL_MAX_EXP __LDBL_MAX_EXP__

#undef FLT_MAX_10_EXP
#define FLT_MAX_10_EXP __FLT_MAX_10_EXP__
#undef DBL_MAX_10_EXP
#define DBL_MAX_10_EXP __DBL_MAX_10_EXP__
#undef LDBL_MAX_10_EXP
#define LDBL_MAX_10_EXP __LDBL_MAX_10_EXP__

#undef FLT_MAX
#define FLT_MAX __FLT_MAX__
#undef DBL_MAX
#define DBL_MAX __DBL_MAX__
#undef LDBL_MAX
#define LDBL_MAX __LDBL_MAX__

#undef FLT_EPSILON
#define FLT_EPSILON __FLT_EPSILON__
#undef DBL_EPSILON
#define DBL_EPSILON __DBL_EPSILON__
#undef LDBL_EPSILON
#define LDBL_EPSILON __LDBL_EPSILON__

#undef FLT_MIN
#define FLT_MIN __FLT_MIN__
#undef DBL_MIN
#define DBL_MIN __DBL_MIN__
#undef LDBL_MIN
#define LDBL_MIN __LDBL_MIN__

#undef FLT_ROUNDS
#define FLT_ROUNDS 1

#endif

#endif // AURORAFW_STDL_LIBC_FLOAT_H