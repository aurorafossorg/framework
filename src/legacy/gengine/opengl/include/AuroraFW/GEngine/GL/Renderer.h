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

#ifndef AURORAFW_GENGINE_GL_RENDERER_H
#define AURORAFW_GENGINE_GL_RENDERER_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>
#include <AuroraFW/GEngine/GL/Global.h>

#include <AuroraFW/GEngine/API/Renderer.h>

namespace AuroraFW::GEngine::API {
	class AFW_API GLRenderer : public Renderer
	{
	public:
		GLRenderer();

		void clear(uint ) override;
		void setViewport(uint , uint , uint , uint ) override;
		void setDepthTesting(bool ) override;
		void setBlend(bool ) override;
		void setBlendFunction(BlendFunction , BlendFunction ) override;
		void setBlendEquation(BlendEquation ) override;
		void setClearColor(ColorF) override;
		void draw(const API::VertexArray *, const API::IndexBuffer *, const RTShaderPipeline *) const override;
		void draw(const API::VertexArray* , const API::IndexBuffer* , uint ) const override;

		static unsigned getGLRendererBuffer(unsigned );
		static inline AFW_CONSTEXPR unsigned getGLBlendFunction(BlendFunction bfunc)
		{
			switch(bfunc)
			{
				case BlendFunction::None: return 0;
				case BlendFunction::Zero: return GL_ZERO;
				case BlendFunction::One: return GL_ONE;
				case BlendFunction::SourceAlpha: return GL_SRC_ALPHA;
				case BlendFunction::DestinationAlpha: return GL_DST_ALPHA;
				case BlendFunction::OneMinusSourceAlpha: return GL_ONE_MINUS_SRC_ALPHA;
			}
		}

		static inline AFW_CONSTEXPR unsigned getGLBlendEquation(BlendEquation beq)
		{
			switch(beq)
			{
				case BlendEquation::None: return 0;
				case BlendEquation::Add: return GL_FUNC_ADD;
				case BlendEquation::Subtract: return GL_FUNC_SUBTRACT;
				case BlendEquation::ReverseSubtract: return GL_FUNC_REVERSE_SUBTRACT;
			}
		}
	};
}

#endif // AURORAFW_GENGINE_GL_RENDERER_H