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

#ifndef AURORAFW_GENGINE_API_RENDERAPI_H
#define AURORAFW_GENGINE_API_RENDERAPI_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#if defined(AFW_TARGET_PLATFORM_WINDOWS) || defined(AFW__RENDERAPI_DIRECT3D)
	#define AFW_RENDERAPI_DIRECT3D
#endif

namespace AuroraFW::GEngine::API {
	enum AFW_API RenderAPI
	{
		OpenGL,
#ifdef AFW_RENDERAPI_DIRECT3D
		Direct3D,
#endif
		Vulkan
	};

	enum AFW_API RenderAPIVersion : uint {
		Unknown = 0,
		GL_2_0,
		GL_2_1,
		GL_3_0,
		GL_3_1,
		GL_3_2,
		GL_3_3,
		GL_3_3_CORE
	};
}

#endif // AURORAFW_GENGINE_API_RENDERAPI_H