/*****************************************************************************
**                                    / _|
**   __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
**  / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
** | (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
**  \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/
**
** Copyright (C) 2018-2019 Aurora Free Open Source Software.
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