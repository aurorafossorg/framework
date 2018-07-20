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

#ifndef AURORAFW_CORELIB_TYPEINFO_H
#define AURORAFW_CORELIB_TYPEINFO_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/CoreLib/TypeTraits.h>

namespace AuroraFW {
	enum class TypeID : unsigned
	{
		Unsigned,
		UnsignedInt = Unsigned,
		UnsignedChar,
		Byte = UnsignedChar,
		UnsignedByte = Byte,
		Float,
		Double,
		Real,
		LongDouble = Real,
		Int,
		Int8,
		Int16,
		Int32 = Int,
		Char,
		Long,
		LongInt = Long,
		LongLong,
		LongLongInt = LongLong,
		Bool
	};

	class AFW_API TypeInfo {
		inline static constexpr size_t _sizeOf(TypeID type)
		{
			switch (type)
			{
				case TypeID::Float: return sizeof(float);
				case TypeID::UnsignedInt: return sizeof(unsigned int);
				case TypeID::UnsignedByte: return sizeof(byte_t);
				case TypeID::Bool: return sizeof(bool);
				default: return AFW_NULLVAL;
			}
		}

	public:
		AFW_FORCE_INLINE static constexpr size_t sizeOf(unsigned type)
		{
			return sizeOf(static_cast<TypeID>(type));
		}

		AFW_FORCE_INLINE static constexpr size_t sizeOf(TypeID type)
		{
			return ((AFW_IS_CONSTEXPR(type)) ? static_sizeOf(type) : _sizeOf(type));
		}

		AFW_FORCE_INLINE static constexpr size_t static_sizeOf(TypeID type)
		{
			static_assert(AFW_IS_CONSTEXPR(type));
			return _sizeOf(type);
		}
		AFW_FORCE_INLINE static constexpr size_t static_sizeOf(unsigned type) { return sizeOf(static_cast<TypeID>(type)); }
	};
}

#endif // AURORAFW_CORELIB_TYPEINFO_H