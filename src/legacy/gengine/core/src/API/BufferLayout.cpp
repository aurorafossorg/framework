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