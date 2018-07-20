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

#ifndef AURORAFW_GENGINE_GL_VERTEXARRAY_H
#define AURORAFW_GENGINE_GL_VERTEXARRAY_H

#include <AuroraFW/Global.h>

#include <AuroraFW/GEngine/GL/Global.h>

#include <AuroraFW/GEngine/API/VertexArray.h>

namespace AuroraFW::GEngine::API {
		//class AFW_API GLBuffer;
	class AFW_API GLVertexArray : public VertexArray {
	public:
		GLVertexArray();
		~GLVertexArray();

		void addBuffer(const VertexBuffer* , const BufferLayout* ) override;

		inline void bind() const override { GLCall(glBindVertexArray(_vao)); }
		inline void unbind() const override { GLCall(glBindVertexArray(0)); }

	private:
		GLuint _vao;
	};
}

#endif // AURORAFW_GENGINE_GL_VERTEXARRAY_H