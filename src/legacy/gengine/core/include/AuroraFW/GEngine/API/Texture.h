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

#ifndef AURORAFW_GENGINE_API_TEXTURE_H
#define AURORAFW_GENGINE_API_TEXTURE_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/STDL/STL/String.h>

namespace AuroraFW::GEngine::API {
	class AFW_API Texture {
	public:
		virtual ~Texture() {}

		struct AFW_API LoadOptions
		{
			bool flipX;
			bool flipY;

			LoadOptions()
			{
				flipX = false;
				flipY = false;
			}

			LoadOptions(bool flipX, bool flipY)
				: flipX(flipX), flipY(flipY)
			{}
		};

		enum class AFW_API Wrap
		{
			None = 0,
			Repeat,
			Clamp,
			MirroredRepeat,
			ClampToEdge,
			ClampToBorder
		};

		enum class AFW_API Filter
		{
			None = 0,
			Linear,
			Nearest
		};

		enum class AFW_API Format
		{
			None = 0,
			RGB,
			RGBA,
			Luminance,
			LuminanceAlpha
		};

		struct AFW_API Parameters
		{
			Texture::Format format;
			Texture::Filter filter;
			Texture::Wrap wrap;

			Parameters()
			{
				format = Texture::Format::RGBA;
				filter = Texture::Filter::Linear;
				wrap = Texture::Wrap::Clamp;
			}

			Parameters(Texture::Format format, Texture::Filter filter, Texture::Wrap wrap)
				: format(format), filter(filter), wrap(wrap)
			{}

			Parameters(Texture::Filter filter)
				: format(Texture::Format::RGBA), filter(filter), wrap(Texture::Wrap::Clamp)
			{}

			Parameters(Texture::Filter filter, Texture::Wrap wrap)
				: format(Texture::Format::RGBA), filter(filter), wrap(wrap)
			{}
		};

		virtual void bind(uint = 0) const = 0;
		virtual void unbind(uint = 0) const = 0;

		AFW_FORCE_INLINE const std::string& path() const { return _path; }

		static byte_t getStrideFromFormat(Texture::Format format);
		AFW_FORCE_INLINE static void setWrap(Texture::Wrap mode) { _wrapmode = mode; }
		AFW_FORCE_INLINE static void setFilter(Texture::Filter mode) { _filtermode = mode; }

	protected:
		std::string _path;

		static Texture::Wrap _wrapmode;
		static Texture::Filter _filtermode;
	};
}

#endif // AURORAFW_GENGINE_API_TEXTURE_H