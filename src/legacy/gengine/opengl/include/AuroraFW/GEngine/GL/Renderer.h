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