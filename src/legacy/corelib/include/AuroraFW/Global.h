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

#ifndef AURORAFW_GLOBAL_H
#define AURORAFW_GLOBAL_H

#include <AuroraFW/CoreLib/Target.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/CoreLib/Type.h>
#include <AuroraFW/CoreLib/Utils.h>
#include <AuroraFW/CoreLib/Allocator.h>

#ifndef AURORAFW_
#define AURORAFW_
#endif // AURORAFW_

//TODO: Build System!
#define AURORAFW_VERSION_MAJOR 0
#define AURORAFW_VERSION_MINOR 0
#define AURORAFW_VERSION_REVISION 0

#endif // AURORAFW_GLOBAL_H