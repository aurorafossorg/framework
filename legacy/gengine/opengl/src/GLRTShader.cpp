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

#include <AuroraFW/GEngine/GL/RTShader.h>
#include <AuroraFW/STDL/STL/String.h>
#include <AuroraFW/STDL/STL/Vector.h>
#include <AuroraFW/IO/File.h>
#include <AuroraFW/CLI/Log.h>

#include <stdexcept>

namespace AuroraFW::GEngine::API {
	void GLRTShader::init() {
		switch(_type)
		{
			case Shader::Type::Vertex:
				_shader = glCreateShader(GL_VERTEX_SHADER);
				break;
			case Shader::Type::Fragment:
				_shader = glCreateShader(GL_FRAGMENT_SHADER);
				break;
			case Shader::Type::Geometry:
				_shader = glCreateShader(GL_GEOMETRY_SHADER);
				break;
			case Shader::Type::TessellationControl:
				_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
				break;
			case Shader::Type::TessellationEvaluation:
				_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
				break;
			case Shader::Type::Compute:
				_shader = glCreateShader(GL_COMPUTE_SHADER);
				break;
			case Shader::Type::Unknown:
			default:
				throw std::runtime_error("Can't load the shader.");
				break;
		};
	}

	GLRTShader::GLRTShader(Shader::Type type)
		: _type(type)
	{
		init();
	}

	GLRTShader::~GLRTShader()
	{
		if(_type != Shader::Type::Cached)
			GLCall(glDeleteShader(_shader));
	}

	GLint GLRTShader::getGLInfo(GLParameter param)
	{
		GLint ret;
		GLCall(glGetShaderiv(_shader, static_cast<GLenum>(param), &ret));
		return ret;
	}

	void GLRTShader::compileFromSource(std::string src)
	{
		const char *c_str = src.c_str();
		GLCall(glShaderSource(_shader, 1, &c_str, AFW_NULL));
		GLCall(glCompileShader(_shader));
		_compiled = getGLInfo(GLParameter::CompileStatus);
		if(_compiled == GL_FALSE)
		{
			GLint maxLength = getGLInfo(GLParameter::LogLength);
			GLchar* errorLog = static_cast<GLchar*>(malloc(maxLength));
			GLCall(glGetShaderInfoLog(_shader, maxLength, &maxLength, errorLog));
			CLI::Log(CLI::Error, errorLog);
			free(errorLog);

			GLCall(glDeleteShader(_shader));
		}
	}

	void GLRTShader::compileFromFile(const std::string &)
	{}

	void GLRTShader::importCachedFile(const std::string& )
	{}

	void GLRTShader::importCachedSource(std::string )
	{}
}