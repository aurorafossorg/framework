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