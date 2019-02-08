/*****************************************************************************
**                                     __
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

#ifndef AURORAFW_MATH_ALGORITHM_H
#define AURORAFW_MATH_ALGORITHM_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#ifdef AFW_TARGET_CXX
namespace AuroraFW {
	namespace Math {
		/**
		 *	Returns the smallest of the two given variables.
		 *	@return The smallest variable between a and b.
		 *	@see inline const T& max()
		 */
		template<class T>
		AFW_API inline const T& min(const T& a, const T& b)
		{
			return (b < a) ? b : a;
		}

		/**
		 *	Returns the biggest of the two given variables.
		 *	@return The biggest variable between a and b.
		 *	@see inline const T& min()
		 */
		template<class T>
		AFW_API inline const T& max(const T& a, const T& b)
		{
			return (a < b) ? b : a;
		}

		/**
		 * 	Clamps the first given variable to the values delimited by the two given variables.
		 *	@return The clamped variable.
		 */
		template<class T>
		AFW_API inline constexpr const T& clamp( const T& v, const T& lo, const T& hi )
		{
			return (v > lo) ? (v < hi) ? v : hi : lo;
		}

		/**
		 * Returns the absolute value of a variable.
		 * @return The absolute value.
		 */
		template<class T>
		AFW_API inline const T abs(const T& v)
		{
			return (v > 0) ? v : -v;
		}
	}
}
#else
inline const int& min(const int& a, const int& b)
{
	return (b < a) ? b : a;
}
inline const int32& min(const int32& a, const int32& b)
{
	return (b < a) ? b : a;
}
#endif

#endif // AURORAFW_MATH_ALGORITHM_H
