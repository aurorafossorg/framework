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

#ifndef AURORAFW_GENGINE_API_RENDERER2D_H
#define AURORAFW_GENGINE_API_RENDERER2D_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/GEngine/Renderable2D.h>
#include <AuroraFW/GEngine/API/Renderer.h>
#include <deque>

namespace AuroraFW::GEngine {
	class AFW_API Renderer2D {
	public:
		Renderer2D(API::Renderer* , uint width , uint height );
		Renderer2D(API::Renderer* , const Math::Vector2D& );

		void push(const Math::Matrix4x4& , bool = false);
		void pop();
		//void setCamera(Camera* );

		void begin();
		void submit(const Renderable2D* );
		void end();
		void present();

	private:
		API::Renderer* _renderer;
		std::unique_ptr<API::VertexBuffer> _vbo;
		std::unique_ptr<API::VertexArray> _vao;
		std::unique_ptr<API::IndexBuffer> _ibo;

		size_t _count;
		size_t _debug_count;
		VertexData* _buffer;
	};
}

#endif // AURORAFW_GENGINE_API_RENDERER2D_H