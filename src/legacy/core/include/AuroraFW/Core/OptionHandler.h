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

#ifndef AURORAFW_CORE_OPTIONHANDLER_H
#define AURORAFW_CORE_OPTIONHANDLER_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <exception>
#include <vector>
#include <map>

namespace AuroraFW {
	class OptionHandler;

	struct AFW_API SplitedOptionElement {
		friend OptionHandler;

		bool active;
		int count;
	private:
		std::string optLong;
		std::string optShort;
		std::string desc;

		int valpos;
	};

	struct AFW_API OptionElement
	{
		std::string opt;
		std::string desc;
	};

	enum OptionHandlerType
	{
		POSIX,
		Win32,
		None
	};

	class AFW_API OptionHandler {
	public:
		OptionHandler(int , char** ,
#if defined(AFW_TARGET_PLATFORM_WINDOWS) && !defined(AFW_TARGET_ENVIRONMENT_POSIX)
			OptionHandlerType = Win32);
#else
			OptionHandlerType = POSIX);
#endif

		void addOption(OptionElement);
		inline void addOption(std::string opt, std::string desc) { addOption({opt, desc}); }
		void addOptions(std::vector<OptionElement> );

		SplitedOptionElement getOption(std::string );
		std::string getValue(SplitedOptionElement);
		inline std::string getValue(std::string opt) { return getValue(getOption(opt)); }

		void printOptions(std::string = "  %s\t%s\t\t%s");

	private:
		std::vector<std::string> _args;
		std::vector<SplitedOptionElement> _opts;
		OptionHandlerType _type;
	};
}

#endif // AURORAFW_CORE_OPTIONHANDLER_H