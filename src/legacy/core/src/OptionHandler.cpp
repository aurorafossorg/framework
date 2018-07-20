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

#include <AuroraFW/Core/OptionHandler.h>

#include <sstream>

namespace AuroraFW {
	OptionHandler::OptionHandler(int argc, char *argv[], OptionHandlerType type)
		: _args(std::vector<std::string>(argv, argv + argc)), _type(type)
	{}

	void OptionHandler::addOption(OptionElement opte)
	{
		std::stringstream ss(opte.opt);
		std::vector<std::string> elems;
		std::string item;
		while(std::getline(ss, item, '|'))
			*(std::back_inserter(elems)++) = item;

		SplitedOptionElement sopte;

		if(elems.size() != 1)
		{
			throw std::out_of_range("Blank option elements not allowed!");
		}

		switch(_type)
		{
			case POSIX:
				if (elems.size() > 1)
				{
					sopte.optShort = "-" + ((elems[0].length() < elems[1].length()) ? elems[0] : elems[1]);
					sopte.optLong = "--" + ((elems[0].length() > elems[1].length()) ? elems[0] : elems[1]);
				}
				else if (elems[0].length() > 1)
				{
					sopte.optLong = "--" + elems[0];
				}
				else
				{
					sopte.optShort = "-" + elems[0];
				}
				break;

			case Win32:
				if (elems.size() > 1)
				{
					sopte.optShort = "/" + ((elems[0].length() < elems[1].length()) ? elems[0] : elems[1]);
					sopte.optLong = "/" + ((elems[0].length() > elems[1].length()) ? elems[0] : elems[1]);
				}
				else
				{
					sopte.optLong = "/" + elems[0];
				}
				break;

			case None:
			default:
				if(elems.size() > 1)
				{
					sopte.optShort = ((elems[0].length() < elems[1].length()) ? elems[0] : elems[1]);
					sopte.optLong = ((elems[0].length() > elems[1].length()) ? elems[0] : elems[1]);
				}
				else
				{
					sopte.optLong = elems[0];
				}
				break;
		}
		sopte.desc = opte.desc;

		for (std::vector<std::string>::iterator i = _args.begin(); i != _args.end(); ++i)
			if(((*i).find(sopte.optLong) == 0 &&
				(((*i).length() == sopte.optLong.length()) ||
					(((*i).length() > sopte.optLong.length()) && ((*i).substr(sopte.optLong.length())[0] == '=')) ))
				|| (((*i).find(sopte.optShort) == 0) && ((*i).length() == sopte.optShort.length())) )
			{
				if((*i).length() > sopte.optLong.length()) sopte.valpos = sopte.optLong.length();
				else sopte.valpos = AFW_DONTCARE;
				sopte.active = true;
				sopte.count = i - _args.begin();
			}
			else {
				sopte.active = false;
			}

		_opts.push_back(sopte);
	}

	SplitedOptionElement OptionHandler::getOption(std::string opt)
	{
		for (std::vector<SplitedOptionElement>::iterator i = _opts.begin(); i != _opts.end(); ++i)
			if((*i).optLong.substr((*i).optLong.find(opt),opt.length()) == opt || (*i).optShort.substr((*i).optShort.find(opt),opt.length()) == opt)
				return *i;
		throw std::invalid_argument("Invalid option name!");
	}

	std::string OptionHandler::getValue(SplitedOptionElement sopte)
	{
		if(sopte.valpos == AFW_DONTCARE)
			return _args[sopte.count+1];
		else
			return _args[sopte.count].substr(sopte.valpos);
	}

	void OptionHandler::addOptions(std::vector<OptionElement> mopte)
	{
		for (std::vector<OptionElement>::iterator i = mopte.begin(); i != mopte.end(); ++i)
			addOption(*i);
	}
}