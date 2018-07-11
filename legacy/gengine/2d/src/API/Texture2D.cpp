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

#include <AuroraFW/GEngine/API/Texture2D.h>
#include <AuroraFW/GEngine/API/Context.h>
#include <AuroraFW/GEngine/GL/Texture2D.h>

namespace AuroraFW::GEngine::API {
	Texture2D* Texture2D::Load(const std::string& path, Texture::Parameters parameters, Texture::LoadOptions loadOptions)
	{
		Texture2D* ret;

		switch(API::Context::getRenderAPI())
		{
			case API::RenderAPI::OpenGL: ret = AFW_NEW GLTexture2D(); break;
			case API::RenderAPI::Vulkan: ret = AFW_NULLPTR;
		}
		ret->_path = path;
		ret->_parameters = parameters;
		ret->_loadOptions = loadOptions;
		return ret;
	}

	Texture2D* Texture2D::Load(const std::string& path, Texture::LoadOptions loadOptions)
	{
		Texture2D* ret;

		switch(API::Context::getRenderAPI())
		{
			case API::RenderAPI::OpenGL: ret = AFW_NEW GLTexture2D(); break;
			case API::RenderAPI::Vulkan: ret = AFW_NULLPTR;
		}
		ret->_path = path;
		ret->_parameters = Texture::Parameters();
		ret->_loadOptions = loadOptions;
		return ret;
	}

	Texture2D* Texture2D::Load(uint width, uint height, Texture::Parameters parameters, Texture::LoadOptions loadOptions)
	{
		Texture2D* ret;

		switch(API::Context::getRenderAPI())
		{
			case API::RenderAPI::OpenGL: ret = AFW_NEW GLTexture2D(); break;
			case API::RenderAPI::Vulkan: ret = AFW_NULLPTR;
		}
		ret->_path = "undefined";
		ret->_parameters = parameters;
		ret->_loadOptions = loadOptions;
		ret->_width = width;
		ret->_height = height;
		return ret;
	}

	Texture2D *Texture2D::Load(uint width, uint height, Color color, Texture::Parameters parameters, Texture::LoadOptions loadOptions)
	{
		Texture2D* ret;

		switch(API::Context::getRenderAPI())
		{
			case API::RenderAPI::OpenGL: ret = AFW_NEW GLTexture2D(); break;
			case API::RenderAPI::Vulkan: ret = AFW_NULLPTR;
		}
		ret->_path = "undefined";
		ret->_parameters = parameters;
		ret->_loadOptions = loadOptions;
		ret->_width = width;
		ret->_height = height;
		ret->setData(color);

		return ret;
	}

	Texture2D *Texture2D::Load(uint width, uint height, void* data, Texture::Parameters parameters, Texture::LoadOptions loadOptions)
	{
		Texture2D* ret;

		switch(API::Context::getRenderAPI())
		{
			case API::RenderAPI::OpenGL: ret = AFW_NEW GLTexture2D(); break;
			case API::RenderAPI::Vulkan: ret = AFW_NULLPTR;
		}
		ret->_path = "undefined";
		ret->_parameters = parameters;
		ret->_loadOptions = loadOptions;
		ret->_width = width;
		ret->_height = height;
		ret->setData(data);

		return ret;
	}

	void Texture2D::setData(Color /*color*/)
	{
		#pragma message ("TODO: Need to be implemented")
	}
}