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

#ifndef AURORAFW_GENGINE_GL_IMGUI_LOADER_H
#define AURORAFW_GENGINE_GL_IMGUI_LOADER_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/GEngine/GL/Global.h>

#include <AuroraFW/GEngine/ImGui/Loader.h>

namespace AuroraFW {
	namespace GEngine {
		class AFW_API GLImGuiLoader : public ImGuiLoader
		{
		public:
			GLImGuiLoader();

			bool createDeviceObjects() override;
			void invalidateDeviceObjects() override;
			void renderDrawLists(ImDrawData *) override;

		private:
			void _Unload() override;
			inline void _internalNewFrame() override { if(!_fontTexture) createDeviceObjects(); }

			uint _fontTexture = 0;
			int _shaderHandle = 0, _vertHandle = 0, _fragHandle = 0;
			int _attribLocationTex = 0, _attribLocationProjMtx = 0;
			int _attribLocationPosition = 0, _attribLocationUV = 0, _attribLocationColor = 0;
			uint _vboHandle = 0, _elementsHandle = 0;
		};
	}
}

#endif // AURORAFW_GENGINE_GL_IMGUI_LOADER_H