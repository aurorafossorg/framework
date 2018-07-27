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

#ifndef AURORAFW_GENGINE_API_RTSHADERPIPELINE_H
#define AURORAFW_GENGINE_API_RTSHADERPIPELINE_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>
#include <AuroraFW/STDL/STL/String.h>
#include <AuroraFW/Math/Vector2D.h>
#include <AuroraFW/Math/Vector3D.h>
#include <AuroraFW/Math/Vector4D.h>
#include <AuroraFW/GEngine/API/RTShader.h>

#include <AuroraFW/STDL/STL/Vector.h>

namespace AuroraFW::GEngine::API {
	class AFW_API RTShaderPipeline {
	public:
		static RTShaderPipeline* Load(std::vector<RTShader*> );

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void generate() = 0;

		virtual void setValue(const std::string& , float ) = 0;
		virtual void setValue(const std::string& , const Math::Vector2D& ) = 0;
		virtual void setValue(const std::string& , const Math::Vector3D& ) = 0;
		virtual void setValue(const std::string& , const Math::Vector4D& ) = 0;
		virtual void setValue(const std::string& , float* , size_t ) = 0;
		virtual void setValue(const std::string &, const Math::Vector2D**, size_t ) = 0;
		virtual void setValue(const std::string &, const Math::Vector3D**, size_t ) = 0;
		virtual void setValue(const std::string &, const Math::Vector4D**, size_t ) = 0;
		virtual void setValue(const std::string &, int ) = 0;
		virtual void setValue(const std::string &, int *, size_t ) = 0;
		virtual void setValue(const std::string &, const Math::Matrix4x4 &) = 0;
		AFW_FORCE_INLINE bool isGenerated() const { return _generated; }

	protected:
		bool _generated = false;
	};
}

#endif // AURORAFW_GENGINE_API_RTSHADERPIPELINE_H