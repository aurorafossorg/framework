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