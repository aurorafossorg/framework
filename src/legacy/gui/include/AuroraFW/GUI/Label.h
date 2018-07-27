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
