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

#include <gtk/gtk.h>
#include <AuroraFW/GUI/Window.h>
#include <AuroraFW/Core/DebugManager.h>
#include <AuroraFW/CLI/Log.h>

namespace AuroraFW
{
	namespace GUI {
		Window::Window(const std::string& name, const int& width, const int& height, const WindowPosition& pos, const WindowType& type)
		{
			DebugManager::Log("creating new window");
			_widget = gtk_window_new((GtkWindowType)type);
			setTitle(name);
			setPos(pos);
			gtk_window_set_default_size(GTK_WINDOW(_widget), width, height);
			connect("destroy", (afw_callback_t)[](){
				gtk_main_quit();
				DebugManager::Log("window is destroyed.");
			});
			DebugManager::Log("window is created.");
		}

		Window::~Window()
		{
			destroy();
		}

		void Window::addWidget(Widget* widget)
		{
			if (widget != AFW_NULLPTR)
				gtk_container_add(GTK_CONTAINER(this->_widget), widget->getNativeGtkWidget());
		}

		void Window::setTitle(const std::string& title)
		{
			DebugManager::Log("setting title on window");
			gtk_window_set_title(GTK_WINDOW(_widget), title.c_str());
		}

		void Window::setPos(const WindowPosition& pos)
		{
			DebugManager::Log("setting window position on window");
			gtk_window_set_position (GTK_WINDOW(_widget), (GtkWindowPosition) pos);
		}

		void Window::setOpacity(double val)
		{
			DebugManager::Log("setting window opacity to: ", val);
			gtk_widget_set_opacity(_widget, val);
		}

		void Window::setResizable(bool val)
		{
			DebugManager::Log("setting window resizable value to:", val);
			gtk_window_set_resizable(GTK_WINDOW(_widget), val);
		}

		void Window::maximize()
		{
			DebugManager::Log("maximizing window");
			gtk_window_maximize(GTK_WINDOW(_widget));
		}

		void Window::unmaximize()
		{
			DebugManager::Log("unmaximizing window");
			gtk_window_unmaximize(GTK_WINDOW(_widget));
		}

		void Window::iconify()
		{
			DebugManager::Log("iconify window");
			gtk_window_iconify(GTK_WINDOW(_widget));
		}

		void Window::deiconify()
		{
			DebugManager::Log("deiconify window");
			gtk_window_deiconify(GTK_WINDOW(_widget));
		}

		void Window::stick()
		{
			DebugManager::Log("sticking window");
			gtk_window_stick(GTK_WINDOW(_widget));
		}

		void Window::unstick()
		{
			DebugManager::Log("unsticking window");
			gtk_window_unstick(GTK_WINDOW(_widget));
		}

		void Window::fullscreen()
		{
			DebugManager::Log("toggle fullscreen mode to the current window");
			gtk_window_fullscreen(GTK_WINDOW(_widget));
		}

		void Window::unfullscreen()
		{
			DebugManager::Log("toggle windowed mode to the current window");
			gtk_window_unfullscreen(GTK_WINDOW(_widget));
		}

		void Window::setIcon(const unsigned char* data, int width, int height, int bpp, bool alpha)
		{
			DebugManager::Log("setting the icon for the current window");
			gtk_window_set_icon(GTK_WINDOW(_widget),
				gdk_pixbuf_new_from_data(data,
					GDK_COLORSPACE_RGB,
					alpha,
					bpp, width, height,
					0, NULL, NULL));
		}

		void Window::close()
		{
			DebugManager::Log("closing window");
			gtk_window_close(GTK_WINDOW(_widget));
		}

		void Window::resize(int w, int h)
		{
			DebugManager::Log("resizing window to: ", w, "*", h);
			gtk_window_resize(GTK_WINDOW(_widget), w, h);
		}

		void Window::move(int x, int y)
		{
			DebugManager::Log("moving window ", x, "(x value), ", y, "(y value)");
			gtk_window_move(GTK_WINDOW(_widget), x, y);
		}

		void Window::show()
		{
			_show();
			gtk_main();
		}
	}
}
