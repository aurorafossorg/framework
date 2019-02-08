/*****************************************************************************
**                                     __
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

#include <AuroraFW/GUI/_GTK.h>

#include <AuroraFW/GUI/Label.h>
#include <AuroraFW/GUI/Window.h>
#include <AuroraFW/CLI/Log.h>
#include <AuroraFW/Core/DebugManager.h>

namespace AuroraFW
{
	namespace GUI {
		Label::Label(Widget* parent, const std::string& name)
		{
			DebugManager::Log("creating new label");
			_widget = gtk_label_new(name.c_str());
			setParent(parent);
			DebugManager::Log("label is created");
		}

		//Settings
		void Label::setText(std::string text)
		{
			DebugManager::Log("setting text on label");
			gtk_label_set_text(reinterpret_cast<GtkLabel*>(_widget), text.c_str());
		}

		std::string Label::getText() const
		{
			DebugManager::Log("getting text from label");
			return std::string(gtk_label_get_text (reinterpret_cast<GtkLabel*>(_widget)));
		}

		void Label::setSelectable(bool value)
		{
			DebugManager::Log("setting selectable property on label");
			gtk_label_set_selectable(reinterpret_cast<GtkLabel*>(_widget), value);
		}

		bool Label::isSelectable() const
		{
			DebugManager::Log("getting selectable property from label");
			return gtk_label_get_selectable(reinterpret_cast<GtkLabel*>(_widget));
		}

		void Label::setWrap(bool value)
		{
			DebugManager::Log("setting wrap property on label");
			gtk_label_set_line_wrap(reinterpret_cast<GtkLabel*>(_widget), value);
		}

		bool Label::isWrap() const
		{
			DebugManager::Log("getting wrap property from label");
			return gtk_label_get_line_wrap(reinterpret_cast<GtkLabel*>(_widget));
		}

		void Label::setWrapMode(WrapMode mode)
		{
			DebugManager::Log("setting wrap mode property on label");
			gtk_label_set_line_wrap_mode(reinterpret_cast<GtkLabel*>(_widget), (PangoWrapMode)mode);
		}

		WrapMode Label::getWrapMode() const
		{
			DebugManager::Log("getting wrap mode property from label");
			return (WrapMode)gtk_label_get_line_wrap_mode(reinterpret_cast<GtkLabel*>(_widget));
		}

		void Label::setAlignment(AlignMode mode)
		{
			switch(mode)
			{
				case AlignMode::TopLeft :
					DebugManager::Log("setting alignment mode to 'TopLeft' property from label");
					gtk_label_set_xalign(reinterpret_cast<GtkLabel*>(_widget), 0);
					gtk_label_set_yalign(reinterpret_cast<GtkLabel*>(_widget), 0);
					break;
				case AlignMode::TopCenter :
					DebugManager::Log("setting alignment mode to 'TopCenter' property from label");
					gtk_label_set_xalign(reinterpret_cast<GtkLabel*>(_widget), 0.5);
					gtk_label_set_yalign(reinterpret_cast<GtkLabel*>(_widget), 0);
					break;
				case AlignMode::TopRight :
					DebugManager::Log("setting alignment mode to 'TopRight' property from label");
					gtk_label_set_xalign(reinterpret_cast<GtkLabel*>(_widget), 1);
					gtk_label_set_yalign(reinterpret_cast<GtkLabel*>(_widget), 0);
					break;
				case AlignMode::Left :
					DebugManager::Log("setting alignment mode to 'Left' property from label");
					gtk_label_set_xalign(reinterpret_cast<GtkLabel*>(_widget), 0);
					gtk_label_set_yalign(reinterpret_cast<GtkLabel*>(_widget), 0.5);
					break;
				case AlignMode::Center :
					DebugManager::Log("setting alignment mode to 'Center' property from label");
					gtk_label_set_xalign(reinterpret_cast<GtkLabel*>(_widget), 0.5);
					gtk_label_set_yalign(reinterpret_cast<GtkLabel*>(_widget), 0.5);
					break;
				case AlignMode::Right :
					DebugManager::Log("setting alignment mode to 'Right' property from label");
					gtk_label_set_xalign(reinterpret_cast<GtkLabel*>(_widget), 1);
					gtk_label_set_yalign(reinterpret_cast<GtkLabel*>(_widget), 0.5);
					break;
				case AlignMode::BottomLeft :
					DebugManager::Log("setting alignment mode to 'BottomLeft' property from label");
					gtk_label_set_xalign(reinterpret_cast<GtkLabel*>(_widget), 0);
					gtk_label_set_yalign(reinterpret_cast<GtkLabel*>(_widget), 1);
					break;
				case AlignMode::BottomCenter :
					DebugManager::Log("setting alignment mode to 'BottomCenter' property from label");
					gtk_label_set_xalign(reinterpret_cast<GtkLabel*>(_widget), 0.5);
					gtk_label_set_yalign(reinterpret_cast<GtkLabel*>(_widget), 1);
					break;
				case AlignMode::BottomRight :
					DebugManager::Log("setting alignment mode to 'BottomRight' property from label");
					gtk_label_set_xalign(reinterpret_cast<GtkLabel*>(_widget), 1);
					gtk_label_set_yalign(reinterpret_cast<GtkLabel*>(_widget), 1);
					break;
				case AlignMode::Custom : break;
			}
		}

		void Label::setAlignment(const float x, const float y)
		// x and y is acceptable between 0 and 1
		// x value for horizontal	| x >>
		// y value for vertical		| y \/
		{
			DebugManager::Log("setting alignment mode to ", x, "(x value) and ", y, "(y value) ", "property from label");
			gtk_label_set_xalign(reinterpret_cast<GtkLabel*>(_widget), x);
			gtk_label_set_yalign(reinterpret_cast<GtkLabel*>(_widget), y);
		}

		AlignMode Label::getAlignment() const
		{
			const float x = gtk_label_get_xalign(reinterpret_cast<GtkLabel*>(_widget));
			const float y = gtk_label_get_yalign(reinterpret_cast<GtkLabel*>(_widget));
			DebugManager::Log("getting alignment mode property from label: ", x, "(x value) and ", y, "(y value)");
			if(y == 0.0f)
			{
				if(x == 0.0f) return AlignMode::TopLeft;
				else if(x == 0.5f) return AlignMode::TopCenter;
				else if(x == 1.0f) return AlignMode::TopRight;
			}
			else if (y == 0.5f)
			{
				if(x == 0.0f) return AlignMode::Left;
				else if(x == 0.5f) return AlignMode::Center;
				else if(x == 1.0f) return AlignMode::Right;
			}
			else if (y == 1.0f)
			{
				if(x == 0.0f) return AlignMode::BottomLeft;
				else if(x == 0.5f) return AlignMode::BottomCenter;
				else if(x == 1.0f) return AlignMode::BottomRight;
			}
			return AlignMode::Custom;
		}

		void Label::getAlignment(float& x, float& y) const
		{
			x = gtk_label_get_xalign(reinterpret_cast<GtkLabel*>(_widget));
			y = gtk_label_get_yalign(reinterpret_cast<GtkLabel*>(_widget));
		}

		float Label::getXAlignment() const
		{
			DebugManager::Log("getting alignment mode property from label: ", gtk_label_get_xalign(reinterpret_cast<GtkLabel*>(_widget)), "(x value)");
			return gtk_label_get_xalign(reinterpret_cast<GtkLabel*>(_widget));
		}

		float Label::getYAlignment() const
		{
			DebugManager::Log("getting alignment mode property from label: ", gtk_label_get_yalign(reinterpret_cast<GtkLabel*>(_widget)), "(y value)");
			return gtk_label_get_yalign(reinterpret_cast<GtkLabel*>(_widget));
		}
	}
}
