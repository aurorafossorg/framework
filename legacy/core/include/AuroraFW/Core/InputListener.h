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

#ifndef AURORAFW_CORE_INPUTLISTENER_H
#define AURORAFW_CORE_INPUTLISTENER_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/GEngine/Input.h>

namespace AuroraFW {
	struct AFW_API KeyboardEvent {
		int key, scancode;
		ushort mods;
	};

	struct AFW_API MouseButtonEvent {
		int btn;
		ushort mods;
	};

	struct AFW_API MouseMotionEvent {
		double xpos, ypos;
	};

	struct AFW_API MouseScrollEvent {
		double xoffset, yoffset;
	};

	class AFW_API InputListener {
	public:
		virtual ~InputListener();
		virtual bool keyPressed(const KeyboardEvent& );
		virtual bool keyReleased(const KeyboardEvent& );
		virtual bool mousePressed(const MouseButtonEvent& );
		virtual bool mouseReleased(const MouseButtonEvent& );
		virtual bool mouseMoved(const MouseMotionEvent& );
		virtual bool mouseScrolled(const MouseScrollEvent& );
	};
}

#endif // AURORAFW_CORE_INPUTLISTENER_H