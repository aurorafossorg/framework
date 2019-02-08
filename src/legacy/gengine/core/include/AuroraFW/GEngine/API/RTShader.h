/*****************************************************************************
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