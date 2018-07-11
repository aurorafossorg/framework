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