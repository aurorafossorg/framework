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

#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif

#include <AuroraFW/CLI/Color.h>
#include <AuroraFW/CLI/Log.h>
#include <AuroraFW/CoreLib/Target/System.h>

namespace AuroraFW {
	namespace CLI {
		void setColor(const Color& color, const ColorType& type)
		{
			#ifdef AFW_TARGET_PLATFORM_WINDOWS
				// TODO: Needs to be tested!
				unsigned char colr_id_tmp;
				if(type == ColorType::Background)
				{
					switch(color)
					{
						case Color::Black : colr_id_tmp = 0x0046; break;
						case Color::Blue : colr_id_tmp = 0x0010; break;
						case Color::Green : colr_id_tmp = 0x0020; break;
						case Color::Cyan : colr_id_tmp = 0x0030; break;
						case Color::Red : colr_id_tmp = 0x0040; break;
						case Color::Magenta : colr_id_tmp = 0x0050; break;
						case Color::Yellow : colr_id_tmp = 0x0060; break;
						case Color::LightGrey : colr_id_tmp = 0x0070; break;
						case Color::DarkGrey : colr_id_tmp = 0x0080; break;
						case Color::LightBlue : colr_id_tmp = 0x0090; break;
						case Color::LightGreen : colr_id_tmp = 0x00A0; break;
						case Color::LightCyan : colr_id_tmp = 0x00B0; break;
						case Color::LightRed : colr_id_tmp = 0x00C0; break;
						case Color::LightMagenta : colr_id_tmp = 0x00D0; break;
						case Color::LightYellow : colr_id_tmp = 0x00E0; break;
						case Color::White : colr_id_tmp = 0x00F0; break;
						default : colr_id_tmp = 0x0046;
					}
				}
				else if(type == ColorType::Foreground)
				{
					colr_id_tmp = (unsigned)(char) color;
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colr_id_tmp);
			#elif defined(AFW_TARGET_ENVIRONMENT_UNIX)
			int colr_tmp = 0;
			switch(color)
			{
				case Color::Black : colr_tmp = 0; break;
				case Color::Blue : colr_tmp = 4; break;
				case Color::Green : colr_tmp = 2; break;
				case Color::Cyan : colr_tmp = 6; break;
				case Color::Red : colr_tmp = 1; break;
				case Color::Magenta : colr_tmp = 5; break;
				case Color::Yellow : colr_tmp = 3; break;
				case Color::LightGrey : colr_tmp = 7; break;
				case Color::DarkGrey : colr_tmp = 10; break;
				case Color::LightBlue : colr_tmp = 14; break;
				case Color::LightGreen : colr_tmp = 12; break;
				case Color::LightCyan : colr_tmp = 16; break;
				case Color::LightRed : colr_tmp = 11; break;
				case Color::LightMagenta : colr_tmp = 15; break;
				case Color::LightYellow : colr_tmp = 13; break;
				case Color::White : colr_tmp = 17; break;
			}
			if(type == ColorType::Background)
			{
				if(std::to_string(colr_tmp).length()==2)
				{
					Output << "\033[4" << std::to_string(colr_tmp)[1] << "m";
				}
				else
				{
					Output << "\033[4" << colr_tmp << "m";
				}
			}
			else if(type == ColorType::Foreground)
			{
				if(std::to_string(colr_tmp).length()==2)
				{
					std::cout << "\033[1;3" << std::to_string(colr_tmp)[1] << "m";
				}
				else
				{
					std::cout << "\033[3" << colr_tmp << "m";
				}
			}
			#endif
		}
		void resetColor()
		{
			#ifdef AFW_TARGET_PLATFORM_WINDOWS
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | 0);
			#elif defined(AFW_TARGET_UNIX)
			Output << "\033[0m";
			#endif
		}
	}
}
