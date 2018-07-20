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

// TODO: Include all Compiler Targets ( https://sourceforge.net/p/predef/wiki/Compilers/ )

#ifndef AURORAFW_CORELIB_TARGET_COMPILER_H
#define AURORAFW_CORELIB_TARGET_COMPILER_H

#undef AFW_TARGET_CC
#undef AFW_TARGET_CXX

#ifdef __cplusplus
	#define AFW_TARGET_CXX __cplusplus
	#if AFW_TARGET_CXX >= 199711L
		#define AFW_TARGET_CXX_98
	#endif
	#if AFW_TARGET_CXX >= 201103L
		#define AFW_TARGET_CXX_11
	#endif
	#if AFW_TARGET_CXX >= 201402L
		#define AFW_TARGET_CXX_14
	#endif
	#if AFW_TARGET_CXX >= 201703L
		#define AFW_TARGET_CXX_17
	#endif
#else
	#define AFW_TARGET_CC
#endif

#if __USE_ISOC99
	#define AFW_TARGET_C99
#endif

#ifdef _MSC_VER
	#define AFW_TARGET_COMPILER_MSVC _MSC_VER
	//For clang version
	#ifdef __clang__
		#define AFW_TARGET_COMPILER_CLANG ((__clang_major__ * 100) + __clang_minor__)
		#define AFW_TARGET_PRAGMA_ONCE_SUPPORT 1
	#endif

	//Compiler specifications
	#define AFW_FUNC_INFO __FUNCSIG__
	#define AFW_DECL_DEPRECATED __declspec(deprecated)

	#define AFW_ALIGNED_ALLOC(s,a) _aligned_malloc(s,a)
	#define AFW_ALIGNED_FREE(x) _aligned_free(x)

	#ifdef AFW_TARGET_COMPILER_CLANG
		#define AFW_DECL_DEPRECATED_X(x) __declspec(deprecated(x))
	#endif
	#define AFW_DECL_EXPORT __declspec(dllexport)
	#define AFW_DECL_IMPORT __declspec(dllimport)
	#define AFW_DEBUGBREAK(x) __debugbreak();

	//Detect pragmaonce support
	#if _MSC_VER>=1020
		#define AFW_TARGET_PRAGMA_ONCE_SUPPORT 1
	#endif

	#ifdef __INTEL_COMPILER
		#define AFW_TARGET_COMPILER_INTEL __INTEL_COMPILER
	#endif

	#ifdef AFW_TARGET_CXX
		#define AFW_DECL_NOTHROW throw()
		#endif
#elif defined(__GNUG__) || defined(__GNUC__)
	#ifndef AFW_TARGET_COMPILER_GNU
		#define AFW_TARGET_COMPILER_GNU
	#endif
	#define AFW_TARGET_COMPILER_GNU_GCC
	#ifdef AFW_TARGET_CXX
		#define AFW_TARGET_COMPILER_GNU_CXX
	#else
		#define AFW_TARGET_COMPILER_GNU_CC
	#endif // AFW_TARGET_CXX

	#ifdef __GNUG__
		#define AFW_TARGET_COMPILER_GNU_GXX
	#endif

	#ifdef AFW__DEBUG
		#define AFW_FORCE_INLINE inline
	#else
		#define AFW_FORCE_INLINE __always_inline
	#endif // AFW__DEBUG
	
	#define AFW_ALIGNED_ALLOC(s,a) aligned_alloc(a,s)
	#define AFW_ALIGNED_FREE(x) ::free(x);
	#define AFW_DEBUGBREAK(x) __builtin_trap();
	#define AFW_DECL_UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
	#define AFW_DECL_UNUSED_FUNCTION(x) __attribute__((__unused__)) UNUSED_ ## x
#else
	#warning "Unknown compiler!"

	#define AFW_DECL_UNUSED(x) UNUSED_ ## x
	#define AFW_DECL_UNUSED_FUNCTION(x) UNUSED_ ## x

	#define AFW_FORCE_INLINE inline

	//#include <AuroraFW/STDL/LibC/Signal.h>
	#include<signal.h>
	#define AFW_DEBUGBREAK(x) raise(SIGTRAP);
#endif

#if defined(__BORLANDC__) || defined(__CODEGEARC__)
	#define AFW_TARGET_COMPILER_BORLAND
#elif defined(__COMO__)
	#define AFW_TARGET_COMPILER_COMEAU
#elif defined(__DECC)
	#define AFW_TARGET_COMPILER_COMPAQ_CC
#elif defined(__DECCXX)
	#define AFW_TARGET_COMPILER_COMPAQ_CXX
#elif defined(__convexc__)
	#define AFW_TARGET_COMPILER_CONVEXC
#elif defined(_MSC_VER)
	#define AFW_TARGET_COMPILER_MICROSOFT
#endif

#ifdef __CC_ARM
	#define AFW_TARGET_COMPILER_ARM
#endif

#ifdef __MINGW32__
	#define AFW_TARGET_COMPILER_MINGW

	#define AFW_DECL_EXPORT __declspec(dllexport)
	#define AFW_DECL_IMPORT __declspec(dllimport)
#endif

#ifdef __clang__
	#define AFW_TARGET_COMPILER_CLANG ((__clang_major__ * 100) + __clang_minor__)
#endif

#ifdef __ELF__
	#define AFW_TARGET_ELF 1
#endif

// Oracle Developer Studio C/C++ (12.5 or later)
#if (defined(__SUNPRO_C)&&(__SUNPRO_C>=0x5140))||(defined(__SUNPRO_CC)&&(__SUNPRO_CC>=0x5140))
	#define AFW_TARGET_PRAGMA_ONCE_SUPPORT 1
// MSVC
#elif defined(_MSC_VER)&&(_MSC_VER>=1020)
	#define AFW_TARGET_PRAGMA_ONCE_SUPPORT 1
// clang
#elif defined(__clang__)
	#define AFW_TARGET_PRAGMA_ONCE_SUPPORT 1
// comeau
#elif defined(__COMO__)
	#define AFW_TARGET_PRAGMA_ONCE_SUPPORT 1
// C++Builder (XE3 or greater)
#elif defined(__CODEGEARC__)&&(__CODEGEARC__ >=650)
	#define AFW_TARGET_PRAGMA_ONCE_SUPPORT 1
// Digital Mars
#elif defined(__DMC__)
	#define AFW_TARGET_PRAGMA_ONCE_SUPPORT 1
// GCC
#elif defined(__GNUC__)&&((__GNUC__ >3)||(defined(__GNUC_MINOR__)&&(__GNUC__ ==3)&&(__GNUC_MINOR__ >=4)))
	#define AFW_TARGET_PRAGMA_ONCE_SUPPORT 1
// HP aC++ (A.06.12)
#elif defined(__HP_aCC)&&(__HP_aCC >=61200)
	#define AFW_TARGET_PRAGMA_ONCE_SUPPORT 1
// IBM
#elif defined(__xlC__)&&((__xlC__ >1301)||((__xlC__ ==1301)&&(__xlC_ver__ >0100)))
	#define AFW_TARGET_PRAGMA_ONCE_SUPPORT 1
// Intel
#elif defined(__INTEL_COMPILER)||defined(__ICC)||defined(__ECC)||defined(__ICL)
	#define AFW_TARGET_PRAGMA_ONCE_SUPPORT 1
// Pelles C
#elif defined(__POCC__)
	#define AFW_TARGET_PRAGMA_ONCE_SUPPORT 1
// ARM compiler
#elif defined(__CC_ARM)
	#define AFW_TARGET_PRAGMA_ONCE_SUPPORT 1
// IAR C/C++
#elif defined(__IAR_SYSTEMS_ICC__)
	#define AFW_TARGET_PRAGMA_ONCE_SUPPORT 1
// Portland Group C/C++
#elif defined(__PGI)
	#define AFW_TARGET_PRAGMA_ONCE_SUPPORT 0
#endif

#ifdef __STRICT_ANSI__
	#if __STRICT_ANSI__ == 1
		#define AFW_TARGET_STRICT_ANSI
	#endif
#endif

//Temporary definitions
#define AFW_CONSTEXPR constexpr
#define AFW_NOEXCEPT noexcept

#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#endif // AURORAFW_CORELIB_TARGET_COMPILER_H
