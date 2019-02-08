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

#ifndef AURORAFW_GUI_WINDOW_H
#define AURORAFW_GUI_WINDOW_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/GUI/Widget.h>
#include <AuroraFW/GUI/Application.h>
#include <AuroraFW/STDL/STL/IOStream.h>
#include <AuroraFW/STDL/STL/String.h>
#include <AuroraFW/Math/Vector2D.h>
#include <AuroraFW/Image/Image.h>
#include <functional>

namespace AuroraFW {
	namespace GUI {
		class AFW_API Window : public Widget {
			friend class Label;
			friend class Button;
			
		public:

			// Window Types
			enum WindowType
			{
				ToplevelWindow,
				PopupWindow
			};

			// Window Positions
			enum WindowPosition
			{
				NonePosition,
				CenterPosition,
				MousePosition,
				AlwaysCenterPosition,
				CenterParentPosition
			};

			Window(const std::string& = "Aurora Window", const int& = 800, const int& = 600, const WindowPosition& = NonePosition, const WindowType& = ToplevelWindow);
			~Window();

			Window(const Window &) = delete;
			Window &operator=(const Window &) = delete;

			void show() override;
			void addWidget(Widget* );

			void setTitle(const std::string& );
			void setPos(const WindowPosition& );
			void resize(int , int );
			inline void resize(Math::Vector2D& vec) { resize(vec.x, vec.y); }
			void move(int , int );
			inline void move(Math::Vector2D& vec) { move(vec.x, vec.y); }
			void setOpacity(double );
			void setResizable(bool );
			void setIcon(const unsigned char* , int , int , int , bool );
			void setIcon(ImageManager::Image& );
			void setIcon(const char* );
			inline void setIcon(const std::string& str) { setIcon(str.c_str()); }
			void maximize();
			void unmaximize();
			void iconify();
			void deiconify();
			void stick();
			void unstick();
			void fullscreen();
			void unfullscreen();
			void close();

			double getOpacity() const;
			Math::Vector2D getSize() const;
			WindowPosition getPos() const;
			std::string getTitle() const;
			bool isResizable() const;
			bool isMaximized() const;
			bool isFocused() const;

			void start(std::function<void()> = []{});
		};
	}
}

#endif // AURORAFW_GUI_WINDOW_H
