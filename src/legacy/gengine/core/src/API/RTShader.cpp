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