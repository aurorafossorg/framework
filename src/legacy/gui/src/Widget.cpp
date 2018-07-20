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

#include <AuroraFW/GUI/Widget.h>
#include <AuroraFW/GUI/_GTK.h>

namespace AuroraFW {
	namespace GUI {
		void Widget::setParent(Widget* parent)
		{
			gtk_widget_set_parent(_widget, parent->_widget);
		}

		Widget* Widget::parent() const
		{
			return reinterpret_cast<Widget*>(gtk_widget_get_parent(_widget));
		}

		void Widget::_show()
		{
			gtk_widget_show_all(_widget);
		}

		void Widget::hide()
		{
			gtk_widget_hide(_widget);
		}

		void Widget::setName(const std::string& str)
		{
			gtk_widget_set_name(_widget, str.c_str());
		}

		void Widget::destroy()
		{
			gtk_widget_destroy(_widget);
		}

		void Widget::setHAlign(Align align)
		{
			gtk_widget_set_halign(_widget, static_cast<GtkAlign>(align));
		}

		void Widget::setVAlign(Align align)
		{
			gtk_widget_set_valign(_widget, static_cast<GtkAlign>(align));
		}
	}
}