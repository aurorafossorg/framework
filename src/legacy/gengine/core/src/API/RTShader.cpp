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

#include <AuroraFW/GEngine/API/RTShader.h>
#include <AuroraFW/GEngine/GL/RTShader.h>
#include <AuroraFW/GEngine/API/Context.h>
#include <AuroraFW/GEngine/RTShaderConverter.h>
#include <AuroraFW/IO/File.h>
#include <iostream>

namespace AuroraFW::GEngine::API {
	RTShader* RTShader::Load(Shader::Type type, Settings)
	{
		switch(API::Context::getRenderAPI())
		{
			case API::RenderAPI::OpenGL: return AFW_NEW GLRTShader(type);
		}
	}

	RTShader* RTShader::Load(Shader::Type type, std::string path, Language lang, LangVersion langVersion, Settings)
	{
		RTShader* ret;
		switch(API::Context::getRenderAPI())
		{
			case API::RenderAPI::OpenGL: ret = AFW_NEW GLRTShader(type);
		}
		ret->compileFromFile(path, lang, langVersion);
		return ret;
	}

	

	void RTShader::compileFromFile(std::string path, RTShader::Language lang, RTShader::LangVersion langVersion)
	{
		switch (API::Context::getRenderAPI())
		{
			case API::RenderAPI::OpenGL:
				compileFromSource(RTShaderConverter::toGLSL(IO::readFile(path), lang, langVersion));
				break;
			case API::RenderAPI::Vulkan:
				#pragma message ("TODO: Need to be implemented")
				break;
			}
	}
}