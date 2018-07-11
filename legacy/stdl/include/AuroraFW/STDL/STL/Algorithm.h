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

#ifndef AURORAFW_STDL_STL_ALGORITHM_H
#define AURORAFW_STDL_STL_ALGORITHM_H

#include <AuroraFW/CoreLib/Target/Compiler.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/STDL/Internal/Config.h>

//#undef AFW_STDLIB_CC
//#define AFW_STDLIB_CC 0
#include <AuroraFW/STDL/Internal/STL/Algorithm.h>

#if (AFW_STDLIB_CC == 0) || !defined(AURORAFW_STDL_STL__ALGORITHM_H)
#endif
namespace afwstd {
	/**
	 *	Returns the smallest of the two given variables.
	 *	@return The smallest variable between a and b.
	 *	@see inline const T& max()
	 */
	template<typename T>
	inline AFW_CONSTEXPR const T& min(const T& a, const T& b)
	{
		return (b < a) ? b : a;
	}

	/**
	 *	Returns the biggest of the two given variables.
	 *	@return The biggest variable between a and b.
	 *	@see inline const T& min()
	 */
	template<typename T>
	inline AFW_CONSTEXPR const T& max(const T& a, const T& b)
	{
		return (a < b) ? b : a;
	}
}

#endif // AURORAFW_STDL_STL_ALGORITHM_H