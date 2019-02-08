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