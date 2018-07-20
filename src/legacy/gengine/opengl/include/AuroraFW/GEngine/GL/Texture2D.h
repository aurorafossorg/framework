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

#ifndef AURORAFW_GENGINE_GL_TEXTURE2D_H
#define AURORAFW_GENGINE_GL_TEXTURE2D_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>
#include <AuroraFW/GEngine/GL/Global.h>

#include <AuroraFW/GEngine/API/Texture2D.h>

namespace AuroraFW::GEngine::API {
	class AFW_API GLTexture2D : public Texture2D {
	public:
		GLTexture2D();
		~GLTexture2D();

		AFW_FORCE_INLINE GLuint getGLHandleID() const { return _id; }

		void bind(uint = 0) const override;
		void unbind(uint = 0) const override;

		void setData(const void* ) override;

		static uint FormatToGL(Texture::Format format);
		static uint WrapToGL(Texture::Wrap wrap);

	private:
		GLuint _id;
	};
}

#endif // AURORAFW_GENGINE_GL_TEXTURE_H