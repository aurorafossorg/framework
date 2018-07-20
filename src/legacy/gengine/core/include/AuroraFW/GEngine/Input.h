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

/** @file AuroraFW/GEngine/Input.h
 * Input Header. Contains a class that handles all
 * the input inside a Window object. Also contains
 * all the key codes AuroraFW supports.
 * @since snapshot20170930
 */

#ifndef AURORAFW_GENGINE_INPUT_H
#define AURORAFW_GENGINE_INPUT_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/GEngine/_GLFW.h>
#include <AuroraFW/GEngine/Window.h>

#include <list>
#include <functional>

//Max Array Values

#define AFW_GENGINE_INPUT_MAX_KEYS 316
#define AFW_GENGINE_INPUT_KEY_OFFSET 32
#define AFW_GENGINE_INPUT_MAX_MOUSE_BUTTONS 7
#define AFW_GENGINE_INPUT_MOUSE_BUTTONS_OFFSET 0

namespace AuroraFW {
	namespace GEngine {
		class Window;

		enum class InputAction {
			Pressed,
			Released
		};

		enum class InputKey {
			Unknown = -1,
			Space = 32,
			Apostrophe = 39,
			Comma = 44,
			Minus,
			Period, /* . */
			Slash,
			Num0,
			Num1,
			Num2,
			Num3,
			Num4,
			Num5,
			Num6,
			Num7,
			Num8,
			Num9,
			Semicolon = 59,
			Equal = 61,
			A = 65,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			Y,
			Z,
			LeftBracket, /* [ */
			BackSlash, /* \ */
			RightBracket, /* ] */
			GraveAccent = 96, /* ` */
			World1 = 161, /* non-US #1 */
			World2 = 162, /* non-US #2 */
			Escape = 256,
			Enter,
			Tab,
			Backspace,
			Insert,
			Delete,
			Right,
			Left,
			Down,
			Up,
			PageUp,
			PageDown,
			Home,
			End,
			CapsLock = 280,
			ScrollLock,
			NumLock,
			PrintScreen,
			Pause,
			F1 = 290,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			F13,
			F14,
			F15,
			F16,
			F17,
			F18,
			F19,
			F20,
			F21,
			F22,
			F23,
			F24,
			F25,
			NumPad0 = 320,
			NumPad1,
			NumPad2,
			NumPad3,
			NumPad4,
			NumPad5,
			NumPad6,
			NumPad7,
			NumPad8,
			NumPad9,
			NumPadDecimal,
			NumPadDivide,
			NumPadMultiply,
			NumPadSubtract,
			NumPadAdd,
			NumPadEnter,
			NumPadEqual,
			LeftShift = 340,
			LeftControl,
			LeftAlt,
			LeftSuper,
			RightShift,
			RightControl,
			RightAlt,
			RightSuper,
			Menu,
			Last = Menu
		};

		enum class InputButton {
			B1,
			B2,
			B3,
			B4,
			B5,
			B6,
			B7,
			B8,
			Last = B8,
			Left = B1,
			Right = B2,
			Middle = B3
		};

		enum class InputMod : ushort {
			Shift = AFW_BIT(1),
			Control = AFW_BIT(2),
			Alt = AFW_BIT(3),
			Super = AFW_BIT(4),
			CapsLock = AFW_BIT(5),
			NumLock = AFW_BIT(6)
		};

		inline InputMod operator|(InputMod a, InputMod b) { return InputMod(static_cast<ushort>(a) | static_cast<ushort>(b)); }

		/**
		 * A class that handles user input.
		 * A class that listens to any input ocurred inside a Window object.
		 * @since snapshot20170930
		 */
		class AFW_API InputManager {
		public:
			/**
			 * Constructs an InputManager object associated with the given Window.
			 * @param parent The window's pointer
			 * @see ~InputManager()
			 * @since snapshot20170930
			 */
			InputManager(const Window* );

			/**
			 * Destructs the object
			 * @see InputManager()
			 * @since snapshot20170930
			 */
			~InputManager();

			/**
			 * Checks to see if the given key is being pressed.
			 * @param key The key code to check.
			 * @return <code>true</code> if the key is being pressed. <code>false</code> otherwise.
			 * @see isMouseButtonPressed()
			 * @since snapshot20170930
			 */
			bool isKeyPressed(const InputKey& ) const;

			/**
			 * Checks to see if the given mouse button is being pressed.
			 * @param btn The mouse button code code to check.
			 * @return <code>true</code> if the mouse button is being pressed. <code>false</code> otherwise.
			 * @see isKeyPressed()
			 * @since snapshot20170930
			 */
			bool isMouseButtonPressed(const InputButton& ) const;

			/**
			 * Stores the mouse's current position in the two given variables.
			 * @param x,y The variables to store respectively the mouse's X and Y coordinates.
			 * @see getScrollPosition()
			 * @since snapshot20170930
			 */
			void getMousePosition(double& , double& ) const;

			/**
			 * Not implemented yet, presumably stores the mouse's scroll position in the two given variables.
			 * @see getMousePosition()
			 * @since snapshot20170930
			 */
			void getScrollPosition(const double& , const double& ) const;

			void addKeyCallback(std::function<void(InputKey, int, InputAction, InputMod)> );
			void removeKeyCallback(std::function<void(InputKey, int, InputAction, InputMod)> );
			void addMouseButtonCallback(std::function<void(InputButton, InputAction, InputMod)> );
			void removeMouseButtonCallback(std::function<void(InputButton, InputAction, InputMod)> );
			void addCursorPosCallback(std::function<void( double, double)> );
			void removeCursorPosCallback(std::function<void( double, double)> );
			void addScrollCallback(std::function<void(double,double)> );
			void removeScrollCallback(std::function<void(double,double)> );
			void addCharCallback(std::function<void(uint)> );
			void removeCharCallback(std::function<void(uint)> );

		private:
			static void _keyCallback(GLFWwindow* , int , int , int , int );
			static void _mouseButtonCallback(GLFWwindow* , int , int , int );
			static void _cursorPosCallback(GLFWwindow* , double , double );
			static void _scrollCallback(GLFWwindow* , double , double );
			static void _charCallback(GLFWwindow* , uint );

			const Window* _parent;
			bool _keys[AFW_GENGINE_INPUT_MAX_KEYS + AFW_GENGINE_INPUT_KEY_OFFSET];
			bool _mouseButtons[AFW_GENGINE_INPUT_MAX_MOUSE_BUTTONS + AFW_GENGINE_INPUT_MOUSE_BUTTONS_OFFSET];
			double _mx, _my;
			double _sx, _sy;
			std::list <std::function<void(InputKey, int, InputAction, InputMod)>> _keyCallbacks;
			std::list <std::function<void(InputButton, InputAction, InputMod)>> _mouseButtonCallbacks;
			std::list <std::function<void(double,double)>> _cursorPosCallbacks;
			std::list <std::function<void(double,double)>> _scrollCallbacks;
			std::list <std::function<void( int)>> _cursorEnterCallbacks;
			std::list <std::function<void( uint)>> _charCallbacks;
			std::list <std::function<void( uint, int)>> _charModsCallbacks;
			std::list <std::function<void( int, const char**)>> _dropCallbacks;
			std::list <std::function<void( int, int)>> _joystickCallbacks;
		};
	}
}

#endif // AURORAFW_GENGINE_INPUT_H
