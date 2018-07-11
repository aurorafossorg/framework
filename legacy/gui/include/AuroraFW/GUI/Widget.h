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

#ifndef AURORAFW_GUI_WIDGET_H
#define AURORAFW_GUI_WIDGET_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/Core/DebugManager.h>
#include <AuroraFW/STDL/STL/String.h>
#include <AuroraFW/CoreLib/Callback.h>
#include <AuroraFW/GUI/Enums.h>
#include <functional>

typedef struct _GtkWidget GtkWidget;

namespace AuroraFW {
	namespace GUI {
		class AFW_API Widget {
		public:
			//Widget();

			void hide();
			inline virtual void show() { _show(); }
			void destroy();
			void setParent(Widget* );
			void setName(const std::string& );

			std::string name() const;
			Widget* parent() const;

			constexpr void setAlign(Orientation , Align );
			void setHAlign(Align );
			void setVAlign(Align );
			void setState(StateType );

			StateType state() const;
			Align halign() const;
			Align valign() const;
			AFW_FORCE_INLINE GtkWidget *getNativeGtkWidget() const { return _widget; }

			template<typename R, typename... Args>
			void connect(const std::string& , R(*)(Args...), void* = AFW_NULLPTR);

			template<typename R, typename... Args>
			inline void connect(const std::string& signal_, std::function<R(Args...)> callback, void* data = AFW_NULLPTR)
			{ connect(signal_, *getCallbackPtr(callback), data); }

		protected:
			void _show();
			GtkWidget* _widget;
		};
	}
}

#include "Widget_impl.h"

#endif // AURORAFW_GUI_WIDGET_H