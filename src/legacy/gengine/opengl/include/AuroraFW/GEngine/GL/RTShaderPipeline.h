/*****************************************************************************
**                                    / _|
**   __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
**  / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
** | (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
**  \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/
**
** Copyright (C) 2018 Aurora Free Open Source Software.
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
