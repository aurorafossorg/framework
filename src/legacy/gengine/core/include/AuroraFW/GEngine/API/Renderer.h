/*****************************************************************************
**                                     __
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

#ifndef AURORAFW_GENGINE_API_RENDERER_H
#define AURORAFW_GENGINE_API_RENDERER_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/GEngine/API/VertexArray.h>
#include <AuroraFW/GEngine/API/IndexBuffer.h>
#include <AuroraFW/GEngine/API/RTShaderPipeline.h>
#include <AuroraFW/Image/BaseColor.h>

namespace AuroraFW::GEngine::API {
	enum class RendererBufferType : unsigned {
		None = 0,
		Color = AFW_BIT(0),
		Depth = AFW_BIT(1),
		Stencil = AFW_BIT(2)
	};

	inline constexpr unsigned operator|(RendererBufferType a, RendererBufferType b) { return static_cast<unsigned>(a) | static_cast<unsigned>(b); }
	inline constexpr unsigned operator&(RendererBufferType a, RendererBufferType b) { return static_cast<unsigned>(a) & static_cast<unsigned>(b); }
	inline constexpr unsigned operator&(unsigned a, RendererBufferType b) { return a & static_cast<unsigned>(b); }

	class AFW_API Renderer
	{
	public:
		enum class BlendFunction : unsigned {
			None,
			Zero,
			One,
			SourceAlpha,
			DestinationAlpha,
			OneMinusSourceAlpha
		};

		enum class BlendEquation : unsigned {
			None,
			Add,
			Subtract,
			ReverseSubtract
		};

		static Renderer* Load();
		
		virtual void clear(uint = RendererBufferType::Color | RendererBufferType::Depth) = 0;
		virtual void setClearColor(ColorF ) = 0;
		virtual void setViewport(uint , uint , uint , uint ) = 0;
		virtual void setDepthTesting(bool ) = 0;
		virtual void setBlend(bool ) = 0;
		virtual void setBlendFunction(BlendFunction , BlendFunction ) = 0;
		virtual void setBlendEquation(BlendEquation ) = 0;
		virtual void draw(const API::VertexArray* , const API::IndexBuffer* , const RTShaderPipeline* ) const = 0;
		virtual void draw(const API::VertexArray* , const API::IndexBuffer* , uint ) const = 0;
	};
}

#endif // AURORAFW_GENGINE_API_RENDERER_H