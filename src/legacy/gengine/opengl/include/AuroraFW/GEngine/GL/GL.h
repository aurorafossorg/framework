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

#ifndef AURORAFW_GENGINE_GL_GL_H
#define AURORAFW_GENGINE_GL_GL_H

#include <AuroraFW/Global.h>
#include <AuroraFW/GEngine/GL/Global.h>

#include <AuroraFW/GEngine/GL/Buffer.h>
#include <AuroraFW/GEngine/GL/Types.h>

namespace AuroraFW {
	namespace GEngine {
		namespace GL {
			inline void activeShaderProgram(GLuint pipe, GLuint prog) { GLCall(glActiveShaderProgram(pipe, prog)); }
			inline void activeTexture(GLenum texture) { GLCall(glActiveTexture(texture)); }
			inline const char* getVersion() {
				GLCall(const char* ret = (const char*)glGetString(GL_VERSION));
				return ret;
			}
			inline void clearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a) { GLCall(glClearColor(r, g, b, a)); }
		}
	}
}

#endif // AURORAFW_GENGINE_GL_GL_H