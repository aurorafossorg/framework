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

#ifndef AURORAFW_GENGINE_GL_SPECIFICATION_HPP
#define AURORAFW_GENGINE_GL_SPECIFICATION_HPP

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/GEngine/GL/Global.h>

namespace AuroraFW {
	namespace GEngine {
		namespace GL {
			enum class BufferType : GLenum
			{
				Array = GL_ARRAY_BUFFER,
				VertexBuffer = GL_ARRAY_BUFFER,
				ElementArray = GL_ELEMENT_ARRAY_BUFFER,
				IndexBuffer = GL_ELEMENT_ARRAY_BUFFER,
				PixelPack = GL_PIXEL_PACK_BUFFER,
				PixelUnpack = GL_PIXEL_UNPACK_BUFFER
			};

			enum class BufferUsage : GLenum
			{
				StreamDraw = GL_STREAM_DRAW,
				StreamRead = GL_STREAM_READ,
				StreamCopy = GL_STREAM_COPY,
				StaticDraw = GL_STATIC_DRAW,
				StaticRead = GL_STATIC_READ,
				StaticCopy = GL_STATIC_COPY,
				DynamicDraw = GL_DYNAMIC_DRAW,
				DynamicRead = GL_DYNAMIC_READ,
				DynamicCopy = GL_DYNAMIC_COPY
			};
		}
	}
}

#endif // AURORAFW_GENGINE_GL_SPECIFICATION_HPP