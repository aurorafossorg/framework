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