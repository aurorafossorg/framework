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

#include <AuroraFW/GEngine/RTShaderConverter.h>
#include <AuroraFW/GEngine/SPIR-V/GLSL.h>
#include <vector>
#include <utility>
#include <stdexcept>

namespace AuroraFW::GEngine {
	std::string RTShaderConverter::toGLSL(std::string src, API::RTShader::Language srclang, API::RTShader::LangVersion destlangv)
	{
		switch(srclang)
		{
			case API::RTShader::Language::SPIR_V:
			{
				spirv_cross::CompilerGLSL glsl(std::move(std::vector<uint32_t>(src.c_str(), src.c_str() + strlen(src.c_str())/sizeof(uint32_t))));
				spirv_cross::ShaderResources resources = glsl.get_shader_resources();

				for (auto &resource : resources.sampled_images)
				{
					unsigned set = glsl.get_decoration(resource.id, spv::DecorationDescriptorSet);
					unsigned binding = glsl.get_decoration(resource.id, spv::DecorationBinding);

					glsl.unset_decoration(resource.id, spv::DecorationDescriptorSet);
					glsl.set_decoration(resource.id, spv::DecorationBinding, set * 16 + binding);
				}
				spirv_cross::CompilerGLSL::Options options;
				switch(destlangv)
				{
					case API::RTShader::LangVersion::GLSL330:
					case API::RTShader::LangVersion::GLSL330_CORE:
						options.version = 330;
						options.es = false;
						break;
					default:
						throw std::runtime_error("Invalid destination shading language");
				}
				glsl.set_options(options);

				return glsl.compile();
			}
			case API::RTShader::Language::GLSL: return src;
		}
	}
}