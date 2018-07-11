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

#ifndef AURORAFW_GENGINE_API_BUFFERLAYOUT_H
#define AURORAFW_GENGINE_API_BUFFERLAYOUT_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/STDL/STL/Vector.h>
#include <AuroraFW/CoreLib/TypeInfo.h>
#include <AuroraFW/GEngine/API/Context.h>
#include <AuroraFW/Math/Vector2D.h>
#include <AuroraFW/Math/Vector3D.h>
#include <AuroraFW/Math/Vector4D.h>

#include <stdexcept>

namespace AuroraFW::GEngine::API {
	struct AFW_API BufferElement {
		uint type, size, count, offset;
		bool normalized;
	};

	class AFW_API BufferLayout {
	public:
		BufferLayout();
		
		template<typename T>
		void push(uint , bool = false);

		inline const std::vector<BufferElement>& getElements() const { return _elements; }
		inline uint getStride() const { return _stride; }
	private:
		void _push(uint , uint , uint , bool );
		std::vector<BufferElement> _elements;
		uint _stride;
	};

	template<typename T>
	void BufferLayout::push(uint , bool )
	{
		throw std::runtime_error("Unkown type!");
	}

	template<> void BufferLayout::push<float>(uint count, bool normalized);
	template<> void BufferLayout::push<uint>(uint count, bool normalized);
	template<> void BufferLayout::push<byte_t>(uint count, bool normalized);
	template<> void BufferLayout::push<Math::Vector2D>(uint count, bool normalized);
	template<> void BufferLayout::push<Math::Vector3D>(uint count, bool normalized);
	template<> void BufferLayout::push<Math::Vector4D>(uint count, bool normalized);
}

#endif // AURORAFW_GENGINE_API_BUFFERLAYOUT_H