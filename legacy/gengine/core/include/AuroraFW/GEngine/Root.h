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

#ifndef AURORAFW_GENGINE_ROOT_H
#define AURORAFW_GENGINE_ROOT_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/GEngine/API/Renderer.h>
#include <AuroraFW/GEngine/RTShaderManager.h>
#include <AuroraFW/GEngine/Input.h>
#include <vector>
#include <memory>

namespace AuroraFW::GEngine {
	struct AFW_API Root {
	public:
		inline API::Renderer* getRenderer(uint pos = 0) { return _renderers[pos].get(); }
		inline void addRenderer(API::Renderer* ptr) { _renderers.push_back(std::unique_ptr<API::Renderer>(ptr)); }

		std::unique_ptr<RTShaderManager> shaderManager;
		std::unique_ptr<InputManager> inputHandler;

	private:
		std::vector<std::unique_ptr<API::Renderer>> _renderers;
	};
}

#endif //AURORAFW_GENGINE_ROOT_H