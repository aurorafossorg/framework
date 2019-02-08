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

#include <AuroraFW/GEngine/GL/RTShaderPipeline.h>
#include <AuroraFW/CLI/Log.h>
#include <vector>

namespace AuroraFW::GEngine::API {
	GLRTShaderPipeline::GLRTShaderPipeline(std::vector<RTShader*> shaders)
		: _program(glCreateProgram())
	{
		for(auto const& shader: shaders)
			addShader(reinterpret_cast<GLRTShader*>(shader));
		generate();
	}

	GLRTShaderPipeline::GLRTShaderPipeline()
		: _program(glCreateProgram())
	{}

	void GLRTShaderPipeline::generate()
	{
		GLCall(glLinkProgram(_program));
		GLint isLinked = 0;
		GLCall(glGetProgramiv(_program, GL_LINK_STATUS, (int *)&isLinked));
		if(isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			GLCall(glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &maxLength));

			//The maxLength includes the NULL character
			GLchar* errorLog = static_cast<GLchar*>(malloc(maxLength));
			GLCall(glGetProgramInfoLog(_program, maxLength, &maxLength, errorLog));
			CLI::Log(CLI::Error, errorLog);
			free(errorLog);

			GLCall(glDeleteProgram(_program));

			//Use the infoLog as you see fit.
		}
		GLCall(glValidateProgram(_program));
	}

	void GLRTShaderPipeline::bind() const
	{
		GLCall(glUseProgram(_program));
	}

	void GLRTShaderPipeline::unbind() const
	{
		GLCall(glUseProgram(0));
	}

	void GLRTShaderPipeline::addShader(GLRTShader* shader)
	{
		GLCall(glAttachShader(_program, shader->_shader));
	}

	void GLRTShaderPipeline::setValue(const std::string &name, float val)
	{
		GLCall(glUniform1f(getUniformLocation(name), val));
	}

	void GLRTShaderPipeline::setValue(const std::string &name, const Math::Vector2D& vec)
	{
		GLCall(glUniform2f(getUniformLocation(name), vec.x, vec.y));
	}

	void GLRTShaderPipeline::setValue(const std::string &name, const Math::Vector3D& vec)
	{
		GLCall(glUniform3f(getUniformLocation(name), vec.x, vec.y, vec.z));
	}

	void GLRTShaderPipeline::setValue(const std::string &name, const Math::Vector4D& vec)
	{
		GLCall(glUniform4f(getUniformLocation(name), vec.x, vec.y, vec.z, vec.w));
	}

	void GLRTShaderPipeline::setValue(const std::string &name, int val)
	{
		GLCall(glUniform1i(getUniformLocation(name),val));
	}

	void GLRTShaderPipeline::setValue(const std::string &name, const Math::Matrix4x4& mat)
	{
		GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, (const float*)mat.matrix));
	}

	void GLRTShaderPipeline::setValue(const std::string& , float* , size_t )
	{}

	void GLRTShaderPipeline::setValue(const std::string &, int *, size_t )
	{}

	void GLRTShaderPipeline::setValue(const std::string &, const Math::Vector2D**, size_t )
	{}

	void GLRTShaderPipeline::setValue(const std::string &, const Math::Vector3D**, size_t )
	{}

	void GLRTShaderPipeline::setValue(const std::string &, const Math::Vector4D**, size_t )
	{}

	GLint GLRTShaderPipeline::getUniformLocation(const std::string &name)
	{
		GLCall(GLint ret = glGetUniformLocation(_program, name.c_str()));
		return ret;
	}

	GLint GLRTShaderPipeline::getUniformLocation(const char* name)
	{
		GLCall(GLint ret = glGetUniformLocation(_program, name));
		return ret;
	}
}