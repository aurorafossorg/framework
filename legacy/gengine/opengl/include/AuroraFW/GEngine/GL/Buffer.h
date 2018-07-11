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

#ifndef AURORAFW_GENGINE_GL_BUFFER_H
#define AURORAFW_GENGINE_GL_BUFFER_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/GEngine/GL/Global.h>

#include <AuroraFW/GEngine/API/Buffer.h>

namespace AuroraFW {
	namespace GEngine {
		namespace API {
			class AFW_API GLBuffer : public Buffer {
			//friend GLVertexArray;
			public:
				GLBuffer(Buffer::Type );
				GLBuffer(Buffer::Type , const void* , size_t , Buffer::Usage );
				~GLBuffer();

				void allocate(const void* , size_t , Buffer::Usage = Buffer::Usage::Static);
				inline void resize(size_t size) override { allocate(AFW_NULLPTR, size); }

				AFW_FORCE_INLINE GLuint getGLBuffer() const { return _buffer; }
				size_t size() const override;

				inline void bind() const { GLCall(glBindBuffer(_type, _buffer)); }
				inline void unbind() const { GLCall(glBindBuffer(_type, 0)); }

				inline static AFW_CONSTEXPR GLenum getGLType(Buffer::Type t)
				{
					switch(t)
					{
						case Buffer::Type::Array:
						case Buffer::Type::VertexBuffer: return GL_ARRAY_BUFFER;
						case Buffer::Type::ElementArray:
						case Buffer::Type::IndexBuffer: return GL_ELEMENT_ARRAY_BUFFER;
						case Buffer::Type::PixelPack: return GL_PIXEL_PACK_BUFFER;
						case Buffer::Type::PixelUnpack: return GL_PIXEL_UNPACK_BUFFER;
					}
				}

				inline static AFW_CONSTEXPR GLenum getGLUsage(Buffer::Usage u)
				{
					switch(u)
					{
						case Buffer::Usage::Static: return GL_STATIC_DRAW;
						case Buffer::Usage::Dynamic: return GL_DYNAMIC_DRAW;
					}
				}
			private:
				GLuint _buffer;
				GLenum _type;
			};
		}
	}
}

#endif // AURORAFW_GENGINE_GL_BUFFER_H