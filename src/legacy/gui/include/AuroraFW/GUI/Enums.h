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

#ifndef AURORAFW_GUI_ENUMS_H
#define AURORAFW_GUI_ENUMS_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

namespace AuroraFW {
	namespace GUI {
		enum class WrapMode : unsigned
		{
			None,
			Char,
			Word,
			WordChar
		};
		enum class AlignMode : unsigned
		{
			/* TL  TC  TR	| \ | /
			** L   C   R	| < * >
			** BL  BC  BR	| / | \
			*/
			TopLeft,
			TopCenter,
			TopRight,
			Left,
			Center,
			Right,
			BottomLeft,
			BottomCenter,
			BottomRight,
			Custom
		};
		enum class Justification : unsigned
		{
			Left,
			Right,
			Center,
			Fill
		};

		enum class MenuDirectionType : unsigned
		{
			Parent,
			Child,
			Next,
			Prev
		};

		enum class MessageType : unsigned
		{
			Info,
			Warning,
			Question,
			Error,
			Other
		};

		enum class MovementStep : unsigned
		{
			LogicalPositions,
			VisualPositions,
			Words,
			DisplayLines,
			DisplayLineEnds,
			Paragraphs,
			ParagraphEnds,
			Pages,
			BufferEnds,
			HorizontalPages
		};

		enum class ScrollStep : unsigned
		{
			Steps,
			Pages,
			Ends,
			HorizontalSteps,
			HorizontalPages,
			HorizontalEnds
		};

		enum class Orientation : unsigned
		{
			Horizontal,
			Vertical
		};

		enum class PackType : unsigned
		{
			Start,
			End
		};

		enum class ResizeMode : unsigned
		{
			Parent,
			Queue,
			Immediate
		};

		enum class Align : unsigned
		{
			Fill,
			Start,
			End,
			Center,
			Baseline
		};

		enum class BaselinePosition : unsigned
		{
			Top,
			Center,
			Bottom
		};

		enum class PositionType : unsigned
		{
			Left,
			Right,
			Top,
			Bottom
		};

		enum class ReliefStyle : unsigned
		{
			Normal,
			Half,
			None
		};

		enum class ScrollType : unsigned
		{
			None,
			Jump,
			StepBackward,
			StopForward,
			PageBackward,
			PageForward,
			StepUp,
			StepDown,
			PageUp,
			PageDown,
			StepLeft,
			StepRight,
			PageLeft,
			PageRight,
			Start,
			End
		};

		enum class SelectionMode : unsigned
		{
			None,
			Single,
			Browse,
			Multiple
		};

		enum class DeleteType : unsigned
		{
			Chars,
			WordEnds,
			Words,
			DisplayLines,
			DisplayLineEnds,
			ParagraphEnds,
			Paragraphs,
			Whitespace
		};

		enum class DirectionType : unsigned
		{
			TabForward,
			TabBackward,
			Up,
			Down,
			Left,
			Right
		};

		enum class IconSize : unsigned
		{
			Invalid,
			Menu,
			SmallToolbar,
			LargeToolbar,
			Button,
			DND,
			Dialog
		};

		enum class SensitivityType : unsigned
		{
			Auto,
			On,
			Off
		};

		enum class TextDirection : unsigned
		{
			None,
			LTR,
			RTL
		};

		enum class ArrowType : unsigned
		{
			Up,
			Down,
			Left,
			Right,
			None
		};

		enum class StateType : unsigned
		{

		};
	}
}

#endif // AURORAFW_GUI_ENUMS_H
