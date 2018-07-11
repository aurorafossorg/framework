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

#include <AuroraFW/GEngine/GL/Texture2D.h>
#include <AuroraFW/Image/STB/Image.h>
#include <iostream>

namespace AuroraFW::GEngine::API {
	GLTexture2D::GLTexture2D()
	{
		void* _rawbuf;

		stbi_set_flip_vertically_on_load(1);
		_rawbuf = stbi_load(_path.c_str(), &_width, &_height, &_bpp, 4);

		GLCall(glGenTextures(1, &_id));
		GLCall(glBindTexture(GL_TEXTURE_2D, _id));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _rawbuf));
		unbind();

		if(_rawbuf)
			stbi_image_free(_rawbuf);
	}

	GLTexture2D::~GLTexture2D()
	{
		GLCall(glDeleteTextures(1, &_id));
	}

	void GLTexture2D::bind(uint slot) const
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, _id));
	}

	void GLTexture2D::unbind(uint slot) const
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void GLTexture2D::setData(const void* /*data*/)
	{
		#pragma message ("TODO: Need to be implemented")
	}
}