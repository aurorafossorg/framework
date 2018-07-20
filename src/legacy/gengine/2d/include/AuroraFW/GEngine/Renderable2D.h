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

#ifndef AURORAFW_GENGINE_API_RENDERERABLE2D_H
#define AURORAFW_GENGINE_API_RENDERERABLE2D_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/Math/Vector2D.h>
#include <AuroraFW/Math/Vector3D.h>
#include <AuroraFW/Math/Vector4D.h>
#include <AuroraFW/GEngine/API/VertexArray.h>
#include <AuroraFW/GEngine/API/IndexBuffer.h>
#include <AuroraFW/GEngine/API/RTShaderPipeline.h>
#include <AuroraFW/Image/BaseColor.h>
#include <memory>

#define AFW_RENDERER_VERTEX_SIZE sizeof(VertexData)

namespace AuroraFW::GEngine {
	class Renderer2D;

	struct AFW_API VertexData {
		Math::Vector3D vertex;
		ColorF color;
	};

	class AFW_API Renderable2D {
	public:
		Renderable2D(Math::Vector3D, Math::Vector2D , ColorF );
		virtual ~Renderable2D();

		AFW_FORCE_INLINE const Math::Vector3D& pos() const { return _pos; }
		AFW_FORCE_INLINE const Math::Vector2D& size() const { return _size; }
		AFW_FORCE_INLINE ColorF color() const { return _color; }

	protected:
		Math::Vector2D _size;
		Math::Vector3D _pos;
		ColorF _color;

		bool _visible;
	};
}

#endif // AURORAFW_GENGINE_API_RENDERERABLE2D_H