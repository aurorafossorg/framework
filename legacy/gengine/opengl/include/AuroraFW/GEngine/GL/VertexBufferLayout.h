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

#ifndef AURORAFW_GENGINE_GL_VERTEXBUFFERLAYOUT_H
#define AURORAFW_GENGINE_GL_VERTEXBUFFERLAYOUT_H

#include <AuroraFW/Global.h>

#include <AuroraFW/GEngine/GL/Global.h>

#include <AuroraFW/GEngine/GL/VertexBufferElement.h>
#include <AuroraFW/STDL/STL/Vector.h>

namespace AuroraFW {
	namespace GEngine {
		class AFW_API GLVertexBufferLayout {
		public:
			GLVertexBufferLayout()
				: _stride(0) {}

			template <typename T>
			void push(uint count);

			inline const std::vector<GLVertexBufferElement> getElements() const { return _elements; }
			inline uint getStride() const { return _stride; }

		private:
			std::vector<GLVertexBufferElement> _elements;
			uint _stride;
		};

		template <typename T>
		void GLVertexBufferLayout::push(uint count) { AFW_DEBUGBREAK(); }

		template <>
		void GLVertexBufferLayout::push<float>(uint count)
		{
			_elements.push_back({GL_FLOAT, count, GL_FALSE});
			_stride += GLVertexBufferElement::sizeOf(GL_FLOAT) * count;
		}

		template <>
		void GLVertexBufferLayout::push<uint>(uint count)
		{
			_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
			_stride += GLVertexBufferElement::sizeOf(GL_UNSIGNED_INT) * count;
		}

		template <>
		void GLVertexBufferLayout::push<byte_t>(uint count)
		{
			_elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
			_stride += GLVertexBufferElement::sizeOf(GL_UNSIGNED_BYTE) * count;
		}
	}


}

#endif // AURORAFW_GENGINE_GL_VERTEXBUFFERLAYOUT_H