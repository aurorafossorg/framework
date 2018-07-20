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

#include <AuroraFW/GEngine/GL/IndexBuffer.h>

namespace AuroraFW {
	namespace GEngine {
		namespace API {
			GLIndexBuffer::GLIndexBuffer(uint* data, uint count)
			{
				_count = count;
				GLCall(glGenBuffers(1, &_ibo));
				bind();
				GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, _count * sizeof(GLuint), data, GL_STATIC_DRAW));
			}
			GLIndexBuffer::~GLIndexBuffer()
			{
				GLCall(glDeleteBuffers(1, &_ibo));
			}

			void GLIndexBuffer::bind() const
			{
				GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo));
			}

			void GLIndexBuffer::unbind() const
			{
				GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
			}
		}
	}
}