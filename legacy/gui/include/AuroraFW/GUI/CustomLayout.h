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

#ifndef AURORAFW_GUI_CUSTOMLAYOUT_H
#define AURORAFW_GUI_CUSTOMLAYOUT_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>
#include <AuroraFW/Math/Vector2D.h>

namespace AuroraFW {
	namespace GUI {
		class AFW_API CustomLayout {
		public:
			CustomLayout(Widget* );
			void addChild(Widget* , int , int );
			void addChild(Widget* , const Math::Vector2D& );
			void moveChild(Widget* , int , int );
			void moveChild(Widget*, const Math::Vector2D& );

			void setSize(uint , uint);
			void getSize(uint& , uint& );
		};
	}
}

#endif // AURORAFW_GUI_CUSTOMLAYOUT_H