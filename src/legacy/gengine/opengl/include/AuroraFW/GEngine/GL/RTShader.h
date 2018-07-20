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

#ifndef AURORAFW_GENGINE_GL_RTSHADER_H
#define AURORAFW_GENGINE_GL_RTSHADER_H

#include <AuroraFW/Global.h>
#include <AuroraFW/GEngine/GL/Global.h>

#include <AuroraFW/STDL/STL/String.h>
#include <AuroraFW/GEngine/API/RTShader.h>

namespace AuroraFW::GEngine::API {
	class GLRTShaderPipeline;

	class AFW_API GLRTShader : public RTShader
	{
	friend GLRTShaderPipeline;
	public:
		enum class GLParameter : GLenum {
			Type = GL_SHADER_TYPE,
			DeleteStatus = GL_DELETE_STATUS,
			CompileStatus = GL_COMPILE_STATUS,
			LogLength = GL_INFO_LOG_LENGTH,
			SourceLength = GL_SHADER_SOURCE_LENGTH
		};

		enum class GLType : GLenum {
			Unknown = 0x31,
			Cached = 0x32,
			Vertex = 0x1,
			Fragment = 0x2,
			Geometry = 0x4,
			TessellationControl = 0x8,
			TessellationEvaluation = 0x10,
			Compute = 0x20
		};

		GLRTShader(Shader::Type);
		~GLRTShader();

		static GLuint importCachedSourceFileShader(std::string );
		static GLuint importCachedSourceFileShader(const char* );
		static GLuint compileShaderFromSource(std::string& );
		static GLuint compileShaderFromSource(const char* );
		static GLuint compileShaderFromFile(std::string );
		static GLuint compileShaderFromFile(const char* );
		static GLint getShaderInfo(GLuint, GLParameter );

		void importCachedFile(const std::string& ) override;
		void importCachedSource(std::string ) override;
		void compileFromSource(std::string ) override;
		void compileFromFile(const std::string& ) override;
		AFW_FORCE_INLINE bool isCompiled() const override { return _compiled; }

		GLuint getGLShader();
		GLint getGLInfo(GLParameter );

	private:
		void init();
		GLuint _shader;
		Shader::Type _type;
		GLint _compiled = GL_FALSE;
	};
}

#endif // AURORAFW_GENGINE_GL_RTSHADER_H