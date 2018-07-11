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

#ifndef AURORAFW_GENGINE_GL_RTSHADERPIPELINE_H
#define AURORAFW_GENGINE_GL_RTSHADERPIPELINE_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/GEngine/GL/Global.h>
#include <AuroraFW/GEngine/GL/RTShader.h>

#include <AuroraFW/GEngine/API/RTShaderPipeline.h>
#include <AuroraFW/GEngine/API/RTShader.h>

#include <AuroraFW/Math/Vector2D.h>
#include <AuroraFW/Math/Vector3D.h>
#include <AuroraFW/Math/Vector4D.h>
#include <AuroraFW/Math/Matrix.h>

namespace AuroraFW::GEngine::API {
	class AFW_API GLRTShaderPipeline : public RTShaderPipeline {
	public:
		GLRTShaderPipeline();
		GLRTShaderPipeline(std::vector<RTShader*> );
		~GLRTShaderPipeline();

		void addShader(GLRTShader* );
		void addShader(GLuint );
		void removeShader(RTShader *);
		void removeShader(GLuint );

		bool addShaderFromSource(Shader::Type , const char *);
		bool addShaderFromSource(Shader::Type , const std::string &);
		bool addShaderFromFile(Shader::Type , const char *);
		bool addShaderFromFile(Shader::Type , const std::string &);
		bool addCachedSourceFile(const char *);
		bool addCachedSourceFile(std::string );

		bool isGenerated();
		void generate();
		static void enableProgram(GLRTShaderPipeline* );
		static void enableProgram(GLuint& );
		static void disableProgram(GLRTShaderPipeline* );
		static void disableProgram(GLuint& );
		void bind() const;
		void unbind() const;

		void setValue(const std::string &, float ) override;
		void setValue(const std::string &, const Math::Vector2D& ) override;
		void setValue(const std::string &, const Math::Vector3D& ) override;
		void setValue(const std::string &, const Math::Vector4D& ) override;
		void setValue(const std::string &, float *, size_t ) override;
		void setValue(const std::string &, const Math::Vector2D**, size_t ) override;
		void setValue(const std::string &, const Math::Vector3D**, size_t ) override;
		void setValue(const std::string &, const Math::Vector4D**, size_t ) override;
		void setValue(const std::string &, int ) override;
		void setValue(const std::string &, int *, size_t ) override;
		void setValue(const std::string &, const Math::Matrix4x4 &) override;
		GLint getUniformLocation(const std::string &);
		GLint getUniformLocation(const char* );

		AFW_FORCE_INLINE GLuint getGLProgram() { return _program; }

	private:
		GLint _generated = GL_FALSE;
		GLuint _program;
	};
}

#endif // AURORAFW_GENGINE_GL_RTSHADERPIPELINE_H
