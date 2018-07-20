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

#include <AuroraFW/GEngine/Renderable2D.h>

namespace AuroraFW::GEngine {
	Renderable2D::Renderable2D(Math::Vector3D pos, Math::Vector2D size, ColorF color)
		: _pos(pos), _size(size), _color(color)
	{
		//if(_shader != AFW_NULLPTR)
		#if 0
		{
			_vertexarr = std::shared_ptr<API::VertexArray>(API::VertexArray::Load());
			float vertices[] = {
				0, 0, 0,
				0, _size.y, 0,
				_size.x, _size.y, 0,
				_size.x, 0, 0
			};

			float colors[] = {
				_color.r, _color.g, _color.b, _color.a,
				_color.r, _color.g, _color.b, _color.a,
				_color.r, _color.g, _color.b, _color.a,
				_color.r, _color.g, _color.b, _color.a
			};

			API::VertexBuffer* vbo = API::VertexBuffer::Load(vertices, sizeof(vertices));
			API::VertexBuffer* cbo = API::VertexBuffer::Load(colors, sizeof(colors));
			API::BufferLayout vbolayout;
			vbolayout.push<float>(3);
			_vertexarr->addBuffer(vbo, &vbolayout);
			vbolayout.push<float>(4);
			_vertexarr->addBuffer(cbo, &vbolayout);
			delete vbo;
			delete cbo;

			uint indices[] = { 0, 1, 2, 2, 3, 0 };
			_indexbuf = std::shared_ptr<API::IndexBuffer>(API::IndexBuffer::Load(indices, 6));
		}
		#endif
	}

	Renderable2D::~Renderable2D()
	{}
}