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

#include <AuroraFW/GEngine/ImGui/Loader.h>
#include <AuroraFW/GEngine/API/Context.h>
#include <AuroraFW/CoreLib/Callback.h>

#include <AuroraFW/GEngine/GL/ImGui/Loader.h>

namespace AuroraFW {
	namespace GEngine {
		ImGuiLoader* ImGuiLoader::Load(Window* win, InputManager* input)
		{
			ImGuiLoader* ret;
			switch(API::Context::getRenderAPI())
			{
				case API::OpenGL: ret = AFW_NEW GLImGuiLoader(); break;
				default: return AFW_NULLPTR;
			}

			ret->_window = win->window;
			ImGuiIO &io = ImGui::GetIO();
			io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB; // Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array.
			io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
			io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
			io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
			io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
			io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
			io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
			io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
			io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
			io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
			io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
			io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
			io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
			io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
			io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
			io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
			io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
			io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
			io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
			io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
			io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

			io.RenderDrawListsFn = AFW_CALLBACK(void (*)(ImDrawData*), ImGuiLoader)(std::bind(&ImGuiLoader::renderDrawLists, ret, std::placeholders::_1));
			io.SetClipboardTextFn = _setClipboardText;
			io.GetClipboardTextFn = _getClipboardText;
			io.ClipboardUserData = ret->_window;
			#ifdef AFW_TARGET_PLATFORM_WINDOWS
				io.ImeWindowHandle = glfwGetWin32Window(ret->_window);
			#endif

			ret->_mouseCursors[ImGuiMouseCursor_Arrow] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
			ret->_mouseCursors[ImGuiMouseCursor_TextInput] = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
			ret->_mouseCursors[ImGuiMouseCursor_ResizeAll] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
			ret->_mouseCursors[ImGuiMouseCursor_ResizeNS] = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
			ret->_mouseCursors[ImGuiMouseCursor_ResizeEW] = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
			ret->_mouseCursors[ImGuiMouseCursor_ResizeNESW] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
			ret->_mouseCursors[ImGuiMouseCursor_ResizeNWSE] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);

			input->addMouseButtonCallback(std::bind(&ImGuiLoader::_mouseButtonCallback, ret, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
			input->addScrollCallback(_scrollCallback);
			input->addKeyCallback(_keyCallback);
			input->addCharCallback(_charCallback);

			return ret;
		}

		void ImGuiLoader::Unload()
		{
			for (ImGuiMouseCursor cursor_n = 0; cursor_n < ImGuiMouseCursor_Count_; cursor_n++)
				glfwDestroyCursor(_mouseCursors[cursor_n]);
			memset(_mouseCursors, 0, sizeof(_mouseCursors));

			invalidateDeviceObjects();

			_Unload();
		}

		void ImGuiLoader::_Unload()
		{}

		void ImGuiLoader::_mouseButtonCallback(InputButton button, InputAction action, InputMod )
		{
			if (action == InputAction::Pressed && button >= InputButton::B1 && button < InputButton::B4)
				_mousePressed[static_cast<int>(button)] = true;
		}

		void ImGuiLoader::_scrollCallback(double x, double y)
		{
			ImGuiIO &io = ImGui::GetIO();
			io.MouseWheelH += (float)x;
			io.MouseWheel += (float)y;
		}

		void ImGuiLoader::_keyCallback(InputKey key, int, InputAction action, InputMod mods)
		{
			ImGuiIO& io = ImGui::GetIO();
			if (action == InputAction::Pressed)
				io.KeysDown[static_cast<int>(key)] = true;
			if (action == InputAction::Released)
				io.KeysDown[static_cast<int>(key)] = false;

			(void)mods; // Modifiers are not reliable across systems
			io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
			io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
			io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
			io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		}

		void ImGuiLoader::_charCallback(uint c)
		{
			ImGuiIO& io = ImGui::GetIO();
			if (c > 0 && c < 0x10000)
				io.AddInputCharacter((unsigned short)c);
		}

		void ImGuiLoader::_setClipboardText(void* udata, const char* txt)
		{
			glfwSetClipboardString((GLFWwindow*)udata, txt);
		}

		const char* ImGuiLoader::_getClipboardText(void* udata)
		{
			return glfwGetClipboardString((GLFWwindow*)udata);
		}

		void ImGuiLoader::newFrame()
		{
			_internalNewFrame();

			ImGuiIO& io = ImGui::GetIO();

			// Setup display size (every frame to accommodate for window resizing)
			int w, h;
			int display_w, display_h;
			glfwGetWindowSize(_window, &w, &h);
			glfwGetFramebufferSize(_window, &display_w, &display_h);
			io.DisplaySize = ImVec2((float)w, (float)h);
			io.DisplayFramebufferScale = ImVec2(w > 0 ? ((float)display_w / w) : 0, h > 0 ? ((float)display_h / h) : 0);

			// Setup time step
			double current_time = glfwGetTime();
			io.DeltaTime = _time > 0.0 ? (float)(current_time - _time) : (float)(1.0f/60.0f);
			_time = current_time;

			// Setup inputs
			// (we already got mouse wheel, keyboard keys & characters from glfw callbacks polled in glfwPollEvents())
			if (glfwGetWindowAttrib(_window, GLFW_FOCUSED))
				if (io.WantMoveMouse)
				{
					glfwSetCursorPos(_window, (double)io.MousePos.x, (double)io.MousePos.y);   // Set mouse position if requested by io.WantMoveMouse flag (used when io.NavMovesTrue is enabled by user and using directional navigation)
				}
				else
				{
					double mouse_x, mouse_y;
					glfwGetCursorPos(_window, &mouse_x, &mouse_y);
					io.MousePos = ImVec2((float)mouse_x, (float)mouse_y);
				}
			else
				io.MousePos = ImVec2(-FLT_MAX,-FLT_MAX);

			for (int i = 0; i < 3; i++)
			{
				// If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
				io.MouseDown[i] = _mousePressed[i] || glfwGetMouseButton(_window, i) != 0;
				_mousePressed[i] = false;
			}

			// Update OS/hardware mouse cursor if imgui isn't drawing a software cursor
			ImGuiMouseCursor cursor = ImGui::GetMouseCursor();
			if (io.MouseDrawCursor || cursor == ImGuiMouseCursor_None)
			{
				glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			}
			else
			{
				glfwSetCursor(_window, _mouseCursors[cursor] ? _mouseCursors[cursor] : _mouseCursors[ImGuiMouseCursor_Arrow]);
				glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}

			// Gamepad navigation mapping [BETA]
			memset(io.NavInputs, 0, sizeof(io.NavInputs));
			if (io.ConfigFlags & ImGuiConfigFlags_NavEnableGamepad)
			{
				// Update gamepad inputs
				#define MAP_BUTTON(NAV_NO, BUTTON_NO) { if (buttons_count > BUTTON_NO && buttons[BUTTON_NO] == GLFW_PRESS) io.NavInputs[NAV_NO] = 1.0f; }
				#define MAP_ANALOG(NAV_NO, AXIS_NO, V0, V1) { float v = (axes_count > AXIS_NO) ? axes[AXIS_NO] : V0; v = (v - V0) / (V1 - V0); if (v > 1.0f) v = 1.0f; if (io.NavInputs[NAV_NO] < v) io.NavInputs[NAV_NO] = v; }
				int axes_count = 0, buttons_count = 0;
				const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axes_count);
				const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttons_count);
				MAP_BUTTON(ImGuiNavInput_Activate, 0); // Cross / A
				MAP_BUTTON(ImGuiNavInput_Cancel, 1); // Circle / B
				MAP_BUTTON(ImGuiNavInput_Menu, 2); // Square / X
				MAP_BUTTON(ImGuiNavInput_Input, 3); // Triangle / Y
				MAP_BUTTON(ImGuiNavInput_DpadLeft, 13); // D-Pad Left
				MAP_BUTTON(ImGuiNavInput_DpadRight, 11); // D-Pad Right
				MAP_BUTTON(ImGuiNavInput_DpadUp, 10); // D-Pad Up
				MAP_BUTTON(ImGuiNavInput_DpadDown, 12); // D-Pad Down
				MAP_BUTTON(ImGuiNavInput_FocusPrev, 4); // L1 / LB
				MAP_BUTTON(ImGuiNavInput_FocusNext, 5); // R1 / RB
				MAP_BUTTON(ImGuiNavInput_TweakSlow, 4); // L1 / LB
				MAP_BUTTON(ImGuiNavInput_TweakFast, 5); // R1 / RB
				MAP_ANALOG(ImGuiNavInput_LStickLeft, 0, -0.3f, -0.9f);
				MAP_ANALOG(ImGuiNavInput_LStickRight, 0, +0.3f, +0.9f);
				MAP_ANALOG(ImGuiNavInput_LStickUp, 1, +0.3f, +0.9f);
				MAP_ANALOG(ImGuiNavInput_LStickDown, 1, -0.3f, -0.9f);
				#undef MAP_BUTTON
				#undef MAP_ANALOG
			}

			// Start the frame. This call will update the io.WantCaptureMouse, io.WantCaptureKeyboard flag that you can use to dispatch inputs (or not) to your application.
			ImGui::NewFrame();
		}
	}
}