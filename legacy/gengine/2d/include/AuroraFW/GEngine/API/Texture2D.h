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

#ifndef AURORAFW_GENGINE_API_TEXTURE2D_H
#define AURORAFW_GENGINE_API_TEXTURE2D_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/GEngine/API/Texture.h>
#include <AuroraFW/Image/BaseColor.h>

namespace AuroraFW::GEngine::API {
	class AFW_API Texture2D : public Texture {
	public:
		static Texture2D* Load(const std::string &, Texture::Parameters = Texture::Parameters(), Texture::LoadOptions = Texture::LoadOptions());
		static Texture2D* Load(const std::string &, Texture::LoadOptions );
		static Texture2D* Load(uint , uint , Texture::Parameters = Texture::Parameters(), Texture::LoadOptions = Texture::LoadOptions());
		static Texture2D* Load(uint , uint , Color , Texture::Parameters = Texture::Parameters(), Texture::LoadOptions = Texture::LoadOptions());
		static Texture2D* Load(uint , uint , void* , Texture::Parameters = Texture::Parameters(), Texture::LoadOptions = Texture::LoadOptions());

		void setData(Color );
		virtual void setData(const void *) = 0;

		AFW_FORCE_INLINE uint width() const { return static_cast<uint>(_width); }
		AFW_FORCE_INLINE uint height() const { return static_cast<uint>(_height); }
		AFW_FORCE_INLINE uint bpp() const { return static_cast<uint>(_bpp); }
	
	protected:
		int _width, _height, _bpp;
		Texture::Parameters _parameters;
		Texture::LoadOptions _loadOptions;
	};
}

#endif // AURORAFW_GENGINE_API_TEXTURE2D_H