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