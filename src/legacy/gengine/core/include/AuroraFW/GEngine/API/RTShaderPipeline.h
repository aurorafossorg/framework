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