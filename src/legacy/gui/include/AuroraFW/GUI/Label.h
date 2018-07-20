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

#ifndef AURORAFW_GUI_LABEL_H
#define AURORAFW_GUI_LABEL_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/GUI/Widget.h>
#include <AuroraFW/GUI/Window.h>
#include <AuroraFW/GUI/Enums.h>
#include <AuroraFW/CoreLib/Target/Compiler.h>

#ifdef AFW_TARGET_CXX
	#include <cassert>
#elif defined(AFW_TARGET_CC)
	#include <assert.h>
#endif

/* TODO:
** Setters
**	void setSingleLineMode(bool);
**	void setJustify(JustifyMode);
**	void setLength(int);
**	void setMaxLength(int);
**	void setSelection(int, int);
**	void setAngle(double);
**
** Getters
**	bool isSingleLineMode();
**	JustifyMode getJustify();
**	int getLength();
**	int getMaxLength();
**	int getLines();
**	double getAngle();
**
** Signals
** 	> Use g_signal_connect()
**
**	onCursorMove(void);
**	onCopyToClipboard(void);
**	onLinkClick(void);
*/

namespace AuroraFW {
	namespace GUI {
		class AFW_API Label : public Widget {
		public:
			Label(Widget* = AFW_NULLPTR , const std::string& name = "New Label");

			Label(const Label& ) = delete;
			Label& operator=(const Label& ) = delete;

			//Setters
			void setText(std::string);
			void setSelectable(bool);
			void setWrap(bool);
			void setWrapMode(WrapMode);
			void setAlignment(AlignMode);
			void setAlignment(const float, const float);

			//Getters
			std::string getText() const;
			bool isSelectable() const;
			bool isWrap() const;
			WrapMode getWrapMode() const;
			AlignMode getAlignment() const;
			void getAlignment(float& , float& ) const;
			float getXAlignment() const;
			float getYAlignment() const;
		};
	}
}

#endif // AURORAFW_GUI_LABEL_H
