/*****************************************************************************
**                                    / _|
**   __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
**  / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
** | (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
**  \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/
**
** Copyright (C) 2018 Aurora Free Open Source Software.
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