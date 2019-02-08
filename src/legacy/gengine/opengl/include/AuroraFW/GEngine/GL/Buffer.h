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