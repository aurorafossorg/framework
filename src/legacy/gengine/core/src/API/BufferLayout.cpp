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

#include <AuroraFW/GEngine/API/BufferLayout.h>

namespace AuroraFW::GEngine::API {
	BufferLayout::BufferLayout()
		: _stride(AFW_NULLVAL)
	{}

	template<>
	void BufferLayout::push<float>(uint count, bool normalized)
	{
		switch(Context::getRenderAPI())
		{
			case OpenGL: _push(GL_FLOAT, sizeof(float), count, normalized); break;
			case Vulkan:
				#pragma message ("TODO: Need to be implemented")
				break;
#ifdef AFW_TARGET_PLATFORM_WINDOWS
			case Direct3D: _push(DX_TYPE_R32_FLOAT, sizeof(float), count, normalized); break;
#endif
		}
	}

	template<>
	void BufferLayout::push<uint>(uint count, bool normalized)
	{
		switch(Context::getRenderAPI())
		{
			case RenderAPI::OpenGL: _push(GL_UNSIGNED_INT, sizeof(uint), count, normalized); break;
			case RenderAPI::Vulkan:
				#pragma message ("TODO: Need to be implemented")
				break;
#ifdef AFW_TARGET_PLATFORM_WINDOWS
			case RenderAPI::Direct3D: _push(DX_TYPE_R32_UINT, sizeof(uint), count, normalized); break;
#endif
		}
	}

	template<>
	void BufferLayout::push<byte_t>(uint count, bool normalized)
	{
		switch(Context::getRenderAPI())
		{
			case RenderAPI::OpenGL: _push(GL_UNSIGNED_BYTE, sizeof(byte_t), count, normalized); break;
			case RenderAPI::Vulkan:
				#pragma message ("TODO: Need to be implemented")
				break;
#ifdef AFW_TARGET_PLATFORM_WINDOWS
			case RenderAPI::Direct3D: _push(DX_TYPE_R8G8B8A8_UNORM, sizeof(byte) * 4, 1, normalized); break;
#endif
		}
	}

	template<>
	void BufferLayout::push<Math::Vector2D>(uint count, bool normalized)
	{
		switch(Context::getRenderAPI())
		{
			case RenderAPI::OpenGL: _push(GL_FLOAT, sizeof(float), 2, normalized); break;
			case RenderAPI::Vulkan:
				#pragma message ("TODO: Need to be implemented")
				break;
#ifdef AFW_TARGET_PLATFORM_WINDOWS
			case RenderAPI::Direct3D: _push(DX_TYPE_R32G32_FLOAT, sizeof(Math::Vector2D), count, normalized); break;
#endif
		}
	}

	template<>
	void BufferLayout::push<Math::Vector3D>(uint count, bool normalized)
	{
		switch(Context::getRenderAPI())
		{
			case RenderAPI::OpenGL: _push(GL_FLOAT, sizeof(float), 3, normalized); break;
			case RenderAPI::Vulkan:
				#pragma message ("TODO: Need to be implemented")
				break;
#ifdef AFW_TARGET_PLATFORM_WINDOWS
			case RenderAPI::Direct3D: _push(DX_TYPE_R32G32_FLOAT, sizeof(Math::Vector3D), count, normalized); break;
#endif
		}
	}

	template<>
	void BufferLayout::push<Math::Vector4D>(uint count, bool normalized)
	{
		switch(Context::getRenderAPI())
		{
			case RenderAPI::OpenGL: _push(GL_FLOAT, sizeof(float), 4, normalized); break;
			case RenderAPI::Vulkan:
				#pragma message ("TODO: Need to be implemented")
				break;
#ifdef AFW_TARGET_PLATFORM_WINDOWS
			case RenderAPI::Direct3D: _push(DX_TYPE_R32G32_FLOAT, sizeof(Math::Vector4D), count, normalized); break;
#endif
		}
	}

	void BufferLayout::_push(uint type, uint size, uint count, bool normalized)
	{
		_elements.push_back({type, size, count, normalized});
		_stride += size * count;
	}
}