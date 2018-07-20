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

#ifndef AURORAFW_STDL_CIRCULARSHIFT_H
#define AURORAFW_STDL_CIRCULARSHIFT_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/STDL/LibC/STDDef.h>
#include <AuroraFW/STDL/LibC/STDInt.h>
#include <AuroraFW/CoreLib/Target/Compiler.h>
#include <AuroraFW/CoreLib/Target/Architecture.h>
#include <AuroraFW/STDL/LibC/Limits.h>

#ifdef AFW_TARGET_CXX
	namespace afw {
		template <typename intT>
		#ifdef AFW_TARGET_CXX_11
			constexpr
		#endif
		intT rotl(const intT& val, const size_t& len)
		{
			#if defined(AFW_TARGET_CXX_11) && _wp_force_unsigned_rotate
				static_assert(std::is_unsigned<intT>::value, "Rotate Left only makes sense for unsigned types");
			#endif
			return (val << len) | ((unsigned) val >> (-len & (sizeof(intT) * CHAR_BIT - 1)));
		}
		template <typename intT>
		#ifdef AFW_TARGET_CXX_11
			constexpr
		#endif
		intT rotr(const intT& val, const size_t& len)
		{
			#if defined(AFW_TARGET_CXX_11) && _wp_force_unsigned_rotate
				static_assert(std::is_unsigned<intT>::value, "Rotate Right only makes sense for unsigned types");
			#endif
			return (val >> len) | ((unsigned) val << (-len & (sizeof(intT) * CHAR_BIT - 1)));
		}
#endif
extern inline uint32_t rotl32 (const uint32_t& value, unsigned int count);
extern inline uint32_t rotr32 (const uint32_t& value, unsigned int count);
#if AFW_TARGET_WORDSIZE == 64
	extern inline uint64_t rotl64 (const uint64_t& value, unsigned int count);
	extern inline uint64_t rotr64 (const uint64_t& value, unsigned int count);
#endif
#ifdef AFW_TARGET_CXX
	}
#endif

#endif // AURORAFW_STDL_CIRCULARSHIFT_H
