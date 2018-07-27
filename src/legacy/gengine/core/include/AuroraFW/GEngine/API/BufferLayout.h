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