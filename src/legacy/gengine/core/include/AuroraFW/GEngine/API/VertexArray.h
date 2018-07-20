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

#ifndef AURORAFW_GENGINE_API_VERTEXARRAY_H
#define AURORAFW_GENGINE_API_VERTEXARRAY_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/GEngine/API/Buffer.h>
#include <AuroraFW/GEngine/API/VertexBuffer.h>
#include <AuroraFW/GEngine/API/BufferLayout.h>
#include <vector>

namespace AuroraFW::GEngine::API {
	class AFW_API VertexArray {
	public:
		static VertexArray* Load();
		virtual ~VertexArray() {}

		virtual void addBuffer(const VertexBuffer* , const BufferLayout* ) = 0;
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	protected:
		std::vector<const VertexBuffer*> _buffers;
	};
}

#endif // AURORAFW_GENGINE_API_VERTEXARRAY_H