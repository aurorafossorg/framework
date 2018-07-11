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

#ifndef AURORAFW_GENGINE_API_RTSHADER_H
#define AURORAFW_GENGINE_API_RTSHADER_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/STDL/STL/String.h>
#include <AuroraFW/GEngine/Shader.h>
#include <map>

namespace AuroraFW::GEngine::API {
	class AFW_API RTShader : public Shader {
	public:
		struct Settings {
			bool cached;
		};

		enum class Language {
			Unknown,
			ARB,
			GLSL,
			HLSL,
			CG,
			SPIR,
			SPIR_V,
			AGAL,
			PSSL,
			MSL,
			TGSI
		};

		enum class LangVersion {
			Unknown,
			GLSL110,
			GLSL120,
			GLSL130,
			GLSL140,
			GLSL150,
			GLSL330,
			GLSL330_CORE,
			GLSL400,
			GLSL400_CORE,
			GLSL410,
			GLSL410_CORE,
			GLSL420,
			GLSL420_CORE,
			GLSL430,
			GLSL430_CORE,
			GLSL440,
			GLSL440_CORE,
			GLSL450,
			GLSL450_CORE,
			GLSL460,
			GLSL460_CORE,
			HLSL11,
			HLSL20,
			HLSL20_A,
			HLSL20_B,
			HLSL30,
			HLSL40,
			HLSL41,
			HLSL50,
			SPIR_12,
			SPIR_20,
			SPIRV
		};

		static RTShader* Load(Shader::Type , Settings = {false});
		static RTShader* Load(Shader::Type , std::string , Language, LangVersion , Settings = {false});

		virtual ~RTShader() {}
		AFW_FORCE_INLINE static void Unload(RTShader* ptr) { delete ptr; }

		void compileFromFile(std::string , Language , LangVersion );
		void importCachedFile(std::string , Language );
		void compileFromFile(std::map<Language, std::string> );
		void importCachedSource(const char *, Language );
		void compileFromSource(const char* , Language );

		virtual void importCachedFile(const std::string &) = 0;
		virtual void compileFromFile(const std::string &) = 0;
		virtual void importCachedSource(std::string ) = 0;
		virtual void compileFromSource(std::string ) = 0;
		virtual bool isCompiled() const = 0;
	
	protected:
		Settings _settings;
	};
}

#endif // AURORAFW_GENGINE_API_RTSHADER_H