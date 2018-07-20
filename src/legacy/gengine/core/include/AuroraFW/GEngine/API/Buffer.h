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

#ifndef AURORAFW_GENGINE_API_BUFFER_H
#define AURORAFW_GENGINE_API_BUFFER_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

namespace AuroraFW::GEngine::API {
	class AFW_API Buffer {
	public:
		enum class Usage : unsigned
		{
			Static,
			Dynamic
		};

		enum class Type : unsigned
		{
			Array,
			VertexBuffer,
			ElementArray,
			IndexBuffer,
			PixelPack,
			PixelUnpack
		};

		static Buffer* Load(Type );
		static Buffer* Load(Type , const void* , size_t , Usage );

		virtual ~Buffer() {}
		AFW_FORCE_INLINE void Unload(Buffer *i) { delete i; }

		virtual void allocate(const void * , size_t , Buffer::Usage  = Buffer::Usage::Static) = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual void resize(size_t ) = 0;

		virtual size_t size() const = 0;
		AFW_FORCE_INLINE size_t length() const { return size(); }
	};
}

#endif // AURORAFW_GENGINE_API_BUFFER_H

