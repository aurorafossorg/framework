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

// TODO : Finish this implementation
/* TODO: Define this:
	int_fast8_t
	int_fast16_t
	int_fast32_t
	int_fast64_t

	int_least8_t
	int_least16_t
	int_least32_t
	int_least64_t

	intptr_t

	uint_fast8_t
	uint_fast16_t
	uint_fast32_t
	uint_fast64_t

	uint_least8_t
	uint_least16_t
	uint_least32_t
	uint_least64_t

	uintptr_t

	INT8_MIN
	INT16_MIN
	INT32_MIN
	INT64_MIN

	INT_FAST8_MIN
	INT_FAST16_MIN
	INT_FAST32_MIN
	INT_FAST64_MIN

	INT_LEAST8_MIN
	INT_LEAST16_MIN
	INT_LEAST32_MIN
	INT_LEAST64_MIN

	INTPTR_MIN
	INTMAX_MIN

	INT8_MAX
	INT16_MAX
	INT32_MAX
	INT64_MAX

	INT_FAST8_MAX
	INT_FAST16_MAX
	INT_FAST32_MAX
	INT_FAST64_MAX

	INT_LEAST8_MAX
	INT_LEAST16_MAX
	INT_LEAST32_MAX
	INT_LEAST64_MAX

	INTPTR_MAX

	INTMAX_MAX

	UINT8_MAX
	UINT16_MAX
	UINT32_MAX
	UINT64_MAX

	UINT_FAST8_MAX
	UINT_FAST16_MAX
	UINT_FAST32_MAX
	UINT_FAST64_MAX

	UINT_LEAST8_MAX
	UINT_LEAST16_MAX
	UINT_LEAST32_MAX
	UINT_LEAST64_MAX

	UINTPTR_MAX

	UINTMAX_MAX

	INT8_C
	INT16_C
	INT32_C
	INT64_C

	INTMAX_C

	UINT8_C
	UINT16_C
	UINT32_C
	UINT64_C

	UINTMAX_C
*/

#ifndef AURORAFW_STDL_LIBC_STDINT_H
#define AURORAFW_STDL_LIBC_STDINT_H

#include <AuroraFW/CoreLib/Target/Compiler.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/STDL/Internal/Config.h>

//#undef AFW_STDLIB_CC
//#define AFW_STDLIB_CC 0
#include <AuroraFW/STDL/Internal/LibC/STDInt.h>

#if (AFW_STDLIB_CC == 0) || !defined(AURORAFW_STDL_LIBC__STDINT_H) && \
	!(defined(_STDINT_H) || defined(__STDINT_H_) || defined(_GCC_WRAP_STDINT_H) || defined(_GLIBCXX_CSTDINT))

	#if !_GLIBCXX_HAVE_STDINT_H
		/* Largest integral types. */
		#if AFW_TARGET_WORDSIZE == 64
			typedef long int intmax_t;
			typedef unsigned long int uintmax_t;
		#else
			#ifdef AFW_TARGET_COMPILER_GNU
				__extension__ typedef long long int intmax_t;
				__extension__ typedef unsigned long long int uintmax_t;
			#else
				typedef long long int intmax_t;
				typedef unsigned long long int uintmax_t;
			#endif
		#endif
	#endif

	/* Fixed-size types, underlying types depend on word size and compiler. */
	#if !defined(_BITS_STDINT_INTN_H)
		#if !(defined(__int8_t_defined) || defined(INT8_MAX) || defined(__INT8_MAX__) \
			defined(INT8_MIN) || defined(__INT8_MIN__))
			#define __int8_t_defined
			typedef signed char int8_t;
		#else
			typedef __int8_t int8_t;
		#endif // __int8_t_defined

		#if !(defined(__int16_t_defined) || defined(INT16_MAX) || defined(__INT16_MAX__) \
			defined(INT16_MIN) || defined(__INT16_MIN__))
			#define __int16_t_defined
			typedef signed short int int16_t;
		#else
			typedef __int16_t int16_t;
		#endif // __int16_t_defined

		#if !(defined(__int32_t_defined) || defined(INT32_MAX) || defined(__INT32_MAX__) \
			defined(INT32_MIN) || defined(__INT32_MIN__))
			#define __int32_t_defined
			typedef signed int int32_t;
		#else
			typedef __int32_t int32_t;
		#endif // __int32_t_defined
		
		#if !(defined(__int64_t_defined) || defined(INT64_MAX) || defined(__INT64_MAX__) \
			defined(INT64_MIN) || defined(__INT64_MIN__))
			#define __int64_t_defined
			#if AFW_TARGET_WORDSIZE == 64
				typedef signed long int int64_t;
			#else
				#ifdef AFW_TARGET_COMPILER_GNU
					__extension__ typedef signed long long int int64_t;
				#else
					typedef signed long long int int64_t;
				#endif
			#endif // AFW_TARGET_WORDSIZE
		#else
			typedef __int64_t int64_t;
		#endif // __int64_t_defined
	#endif

	#if !defined(_BITS_STDINT_UINTN_H)
		#if !(defined(__uint8_t_defined) || defined(UINT8_MAX) || defined(__UINT8_MAX__))
			#define __uint8_t_defined
			typedef unsigned char uint8_t;
		#else
			typedef __uint8_t uint8_t;
		#endif // __uint8_t_defined

		#if !(defined(__uint16_t_defined) || defined(UINT16_MAX) || defined(__UINT16_MAX__))
			#define __uint16_t_defined
			typedef unsigned short int uint16_t;
		#else
			typedef __uint16_t uint16_t;
		#endif // __uint16_t_defined

		#if !(defined(__uint32_t_defined) || defined(UINT32_MAX) || defined(__UINT32_MAX__))
			#define __uint32_t_defined
			typedef unsigned int uint32_t;
		#else
			typedef __uint32_t uint32_t;
		#endif // __uint32_t_defined

		#if !(defined(__uint64_t_defined) || defined(UINT64_MAX) || defined(__UINT64_MAX__))
			#define __uint64_t_defined
			#if AFW_TARGET_WORDSIZE == 64
				typedef unsigned long int uint64_t;
			#else
				#ifdef AFW_TARGET_COMPILER_GNU
					__extension__ typedef unsigned long long int uint64_t;
				#else
					typedef unsigned long long int uint64_t;
				#endif
			#endif // AFW_TARGET_WORDSIZE
		#else
			typedef __uint64_t uint64_t;
		#endif // __uint64_t_defined
	#endif
#endif

#endif // AURORAFW_STDL_LIBC_STDINT_H