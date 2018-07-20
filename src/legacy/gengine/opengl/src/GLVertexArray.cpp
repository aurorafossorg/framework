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

#include <AuroraFW/GEngine/GL/VertexArray.h>
#include <AuroraFW/Core/DebugManager.h>

namespace AuroraFW::GEngine::API {
	GLVertexArray::GLVertexArray()
	{
		GLCall(glGenVertexArrays(1, &_vao));
	}

	GLVertexArray::~GLVertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &_vao));
	}

	void GLVertexArray::addBuffer(const VertexBuffer* buf, const BufferLayout* layout)
	{
		_buffers.push_back(buf);
		DebugManager::Log("Add buffer into a VAO");
		bind();
		const std::vector<BufferElement> &elements = layout->getElements();
		size_t offset = 0;
		for (uint i = 0; i < _buffers.size(); i++)
		{
			_buffers[i]->bind();
			const BufferElement &element = elements[i];
			DebugManager::Log("VertexArray[", i, ", ", _buffers[i], "] = ", element.count, ", ", element.type, ", ", element.normalized, ", ", layout->getStride(), ", ", offset, ", ", element.size);
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, element.count, element.type,
				(uint)element.normalized, 0/*layout->getStride()*/, /*(const void *)offset*/0));
			offset += element.count * element.size;
			_buffers[i]->unbind();
		}
#ifdef AFW__DEBUG
		unbind();
#endif // AFW__DEBUG
	}
}