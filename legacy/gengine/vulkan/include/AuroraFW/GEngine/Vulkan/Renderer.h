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

#ifndef AURORAFW_GENGINE_VULKAN_RENDERER_H
#define AURORAFW_GENGINE_VULKAN_RENDERER_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/GEngine/Vulkan/Global.h>
#include <AuroraFW/GEngine/API/Renderer.h>

namespace AuroraFW::GEngine::API {
	class VKRenderer : public Renderer
	{
	public:
		VKRenderer();
		void clear(uint ) override;
		void setViewport(uint , uint , uint , uint ) override;
		void setDepthTesting(bool ) override;
		void setBlend(bool ) override;
		void setBlendFunction(BlendFunction , BlendFunction ) override;
		void setBlendEquation(BlendEquation ) override;
		void setClearColor(ColorF ) override;
		void draw(const API::VertexArray *, const API::IndexBuffer *, const RTShaderPipeline *) const override;
		void draw(const API::VertexArray* , const API::IndexBuffer* , uint ) const override;

	  private:
		
	};
}

#endif // AURORAFW_GENGINE_VULKAN_RENDERER_H