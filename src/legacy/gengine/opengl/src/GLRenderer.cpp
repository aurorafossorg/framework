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

#include <AuroraFW/GEngine/GL/Renderer.h>
namespace AuroraFW::GEngine::API {
	GLRenderer::GLRenderer()
	{}

	unsigned GLRenderer::getGLRendererBuffer(unsigned buf)
	{
		unsigned ret = 0;
		if (buf & RendererBufferType::Color)
			ret |= GL_COLOR_BUFFER_BIT;
		if (buf & RendererBufferType::Depth)
			ret |= GL_DEPTH_BUFFER_BIT;
		if (buf & RendererBufferType::Stencil)
			ret |= GL_STENCIL_BUFFER_BIT;
		return ret;
	}

	void GLRenderer::clear(uint buf)
	{
		GLCall(glClear(getGLRendererBuffer(buf)));
	}

	void GLRenderer::setViewport(uint x, uint y, uint width, uint height)
	{
		GLCall(glViewport(x, y, width, height));
	}

	void GLRenderer::setDepthTesting(bool val)
	{
		if(val) {
			GLCall(glEnable(GL_DEPTH_TEST));
		}
		else {
			GLCall(glDisable(GL_DEPTH_TEST));
		}
	}

	void GLRenderer::setBlend(bool val)
	{
		if(val) {
			GLCall(glEnable(GL_BLEND));
		}
		else {
			GLCall(glDisable(GL_BLEND));
		}
	}
	
	void GLRenderer::setClearColor(ColorF color)
	{
		GLCall(glClearColor(color.r, color.g, color.b, color.a));
	}

	void GLRenderer::draw(const API::VertexArray* vao, const API::IndexBuffer* ibo, const RTShaderPipeline* shader) const
	{
		shader->bind();
		vao->bind();
		ibo->bind();
		GLCall(glDrawElements(GL_TRIANGLES, ibo->count(), GL_UNSIGNED_INT, AFW_NULLPTR));
#ifdef AFW__DEBUG
		ibo->unbind();
		vao->unbind();
		shader->unbind();
#endif // AFW__DEBUG
	}

	void GLRenderer::draw(const API::VertexArray* vao, const API::IndexBuffer* ibo, uint count) const
	{
		vao->bind();
		ibo->bind();
		GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, AFW_NULLPTR));
#ifdef AFW__DEBUG
		ibo->unbind();
		vao->unbind();
#endif // AFW__DEBUG
	}

	void GLRenderer::setBlendFunction(BlendFunction src, BlendFunction dest)
	{
		GLCall(glBlendFunc(getGLBlendFunction(src), getGLBlendFunction(dest)));
	}

	void GLRenderer::setBlendEquation(BlendEquation eq)
	{
		GLCall(glBlendEquation(getGLBlendEquation(eq)));
	}
}