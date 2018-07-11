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

#ifndef AURORAFW_GENGINE_IMGUI_LOADER_H
#define AURORAFW_GENGINE_IMGUI_LOADER_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/GEngine/Window.h>
#include <AuroraFW/GEngine/ImGui/ImGui.h>

#include <AuroraFW/GEngine/Input.h>

namespace AuroraFW {
	namespace GEngine {
		class AFW_API ImGuiLoader {
		public:
			static ImGuiLoader* Load(Window* , InputManager* );
			void Unload();

			void newFrame();
			virtual bool createDeviceObjects() = 0;
			virtual void invalidateDeviceObjects() = 0;
			virtual void renderDrawLists(ImDrawData *) = 0;

		private:
			virtual void _Unload();
			void _mouseButtonCallback( InputButton , InputAction , InputMod );
			static void _scrollCallback( double , double );
			static void _keyCallback( InputKey , int , InputAction , InputMod );
			static void _charCallback( uint );

			virtual void _internalNewFrame() = 0;
			static void _setClipboardText(void* , const char* );
			static const char* _getClipboardText(void *);

			GLFWwindow* _window = AFW_NULLPTR;
			InputManager* _input = AFW_NULLPTR;
			double _time = 0.0f;
			bool _mousePressed[3] = {false, false, false};
			GLFWcursor *_mouseCursors[ImGuiMouseCursor_Count_] = {0};
		};
	}
}

#endif // AURORAFW_GENGINE_IMGUI_LOADER_H