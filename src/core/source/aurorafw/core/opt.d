/*
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2018 Aurora Free Open Source Software.

This file is part of the Aurora Free Open Source Software. This
organization promote free and open source software that you can
redistribute and/or modify under the terms of the GNU Lesser General
Public License Version 3 as published by the Free Software Foundation or
(at your option) any later version approved by the Aurora Free Open Source
Software Organization. The license is available in the package root path
as 'LICENSE' file. Please review the following information to ensure the
GNU Lesser General Public License version 3 requirements will be met:
https://www.gnu.org/licenses/lgpl.html .

Alternatively, this file may be used under the terms of the GNU General
Public License version 3 or later as published by the Free Software
Foundation. Please review the following information to ensure the GNU
General Public License requirements will be met:
http://www.gnu.org/licenses/gpl-3.0.html.

NOTE: All products, services or anything associated to trademarks and
service marks used or referenced on this file are the property of their
respective companies/owners or its subsidiaries. Other names and brands
may be claimed as the property of others.

For more info about intellectual property visit: aurorafoss.org or
directly send an email to: contact (at) aurorafoss.org .
*/

module aurorafw.core.opt;

import aurorafw.core.debugmanager : debugMsgPrefix;
import std.algorithm.searching : find;
import std.range.primitives : empty;

@safe pure struct OptionHandler {
	struct Element {
		string opt;
		string desc;
	}

	struct SplitedElement {
		bool active;
		size_t count;

	private:
		string optLong;
		string optShort;
		string desc;

		ptrdiff_t valpos;
	}

	enum OptionType {
		Posix,
		Windows,
		None
	}

	this(string[] args, OptionType type = __currentType)
	{
		_args = args;
		_type = type;
	}

	void add(Element opte)
	{
		import std.array : split;
		immutable string[] elems = split(opte.opt, "|");
		SplitedElement sopte;

		assert(elems.length == 1, "Blank option elements not allowed!");

		switch(_type)
		{
			case OptionType.Posix:
				if(elems.length > 1)
				{
					sopte.optShort = "-" ~ ((elems[0].length < elems[1].length) ? elems[0] : elems[1]);
					sopte.optLong = "--" ~ ((elems[0].length > elems[1].length) ? elems[0] : elems[1]);
				}
				else if (elems[0].length > 1)
				{
					sopte.optLong = "--" ~ elems[0];
				}
				else
				{
					sopte.optShort = "-" ~ elems[0];
				}
				break;
			
			case OptionType.Windows:
				if (elems.length > 1)
				{
					sopte.optShort = "/" ~ ((elems[0].length < elems[1].length) ? elems[0] : elems[1]);
					sopte.optLong = "/" ~ ((elems[0].length > elems[1].length) ? elems[0] : elems[1]);
				}
				else
				{
					sopte.optLong = "/" ~ elems[0];
				}
				break;
			
			case OptionType.None:
			default:
				if(elems.length > 1)
				{
					sopte.optShort = ((elems[0].length < elems[1].length) ? elems[0] : elems[1]);
					sopte.optLong = ((elems[0].length > elems[1].length) ? elems[0] : elems[1]);
				}
				else
				{
					sopte.optLong = elems[0];
				}
				break;
		}
		sopte.desc = opte.desc;

		foreach(size_t i, string arg; _args)
			if((find(arg, sopte.optLong).empty &&
				((arg.length == sopte.optLong.length) ||
					((arg.length > sopte.optLong.length) && (arg[sopte.optLong.length .. arg.length][0] == '=')) ))
				|| (find(arg, sopte.optShort).empty && (arg.length == sopte.optShort.length )) )
			{
				if(arg.length > sopte.optLong.length) sopte.valpos = sopte.optLong.length;
				else sopte.valpos = -1;
				sopte.active = true;
				sopte.count = i;
			}
			else {
				sopte.active = false;
			}

		_opts ~= sopte;
	}

	pragma(inline, true) void add(string opt, string desc) { add(Element(opt, desc)); }

	void add(Element[] mopte)
	{
		foreach(Element opte; mopte)
			add(opte);
	}

	SplitedElement option(string opt)
	{
		foreach(SplitedElement sopte; _opts)
			if(!find(sopte.optLong, opt).empty || !find(sopte.optShort, opt).empty)
				return sopte;

		assert(0, "Invalid option name!");
	}

	string value(SplitedElement sopte)
	{
		if(sopte.valpos == -1)
			return _args[sopte.count+1];
		else
			return _args[sopte.count][sopte.valpos .. _args[sopte.count].length];
	}

	pragma(inline, true) string value(string opt) { return value(option(opt)); }

	void print(string fmt = "  %s\t%s\t\t%s") @safe
	{
		pragma(msg, debugMsgPrefix, "FIXME: Need to be implemented");
	}

private:
	string[] _args;
	SplitedElement[] _opts;
	OptionType _type;

	version(Windows) enum OptionType __currentType = OptionType.Windows;
	else enum OptionType __currentType = OptionType.Posix;
}