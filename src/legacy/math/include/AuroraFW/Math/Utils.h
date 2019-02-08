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

#ifndef AURORAFW_MATH_UTILS_H
#define AURORAFW_MATH_UTILS_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#define AFW_PI 3.14159265358f

namespace AuroraFW {
	namespace Math {
		AFW_API inline float toRadians(const float& deg) { return (float)(deg * (AFW_PI / 180.0f)); }
		AFW_API inline float toDegrees(const float& rad) { return (float)(rad  * (180.0f / AFW_PI)); }

		AFW_API inline float sin(const float& a) { return ::sin(a); }
		AFW_API inline float cos(const float& a) { return ::cos(a); }
		AFW_API inline float tan(const float& a) { return ::tan(a); }
		AFW_API inline float asin(const float& v) { return ::asin(v); }
		AFW_API inline float acos(const float& v) { return ::acos(v); }
		AFW_API inline float atan(const float& v) {return ::atan(v); }
	}
}

#endif // AURORAFW_MATH_UTILS_H
