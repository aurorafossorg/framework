/*****************************************************************************
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