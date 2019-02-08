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