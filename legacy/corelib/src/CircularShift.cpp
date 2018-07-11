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

#include <AuroraFW/CoreLib/CircularShift.h>

#ifdef AFW_TARGET_CXX
	namespace AuroraFW
	{
#endif
	inline uint32_t rotl32 (const uint32_t& value, unsigned int count)
	{
		const unsigned int mask = (CHAR_BIT*sizeof(value)-1);
		count &= mask;
		return (value<<count) | (value>>( (-count) & mask ));
	}
	inline uint32_t rotr32 (const uint32_t& value, unsigned int count)
	{
		const unsigned int mask = (CHAR_BIT*sizeof(value)-1);
		count &= mask;
		return (value>>count) | (value<<( (-count) & mask ));
	}
	inline uint64_t rotl64 (const uint64_t& value, unsigned int count)
	{
		const unsigned int mask = (CHAR_BIT*sizeof(value)-1);
		count &= mask;
		return (value>>count) | (value<<( (-count) & mask ));
	}
	inline uint64_t rotr64 (const uint64_t& value, unsigned int count)
	{
		const unsigned int mask = (CHAR_BIT*sizeof(value)-1);
		count &= mask;
		return (value>>count) | (value<<( (-count) & mask ));
	}

#ifdef AFW_TARGET_CXX
	}
#endif
