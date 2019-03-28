/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2018-2019 Aurora Free Open Source Software.

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
https://www.gnu.org/licenses/gpl-3.0.html.

NOTE: All products, services or anything associated to trademarks and
service marks used or referenced on this file are the property of their
respective companies/owners or its subsidiaries. Other names and brands
may be claimed as the property of others.

For more info about intellectual property visit: aurorafoss.org or
directly send an email to: contact (at) aurorafoss.org .
*/

module aurorafw.core.opt;

public import aurorafw.stdx.getopt : defaultRuntimeArgs;

class OptionHandlerException : Exception
{
	import std.exception;
	mixin basicExceptionCtors;
}

static assert(is(typeof(new OptionHandlerException("message"))));
static assert(is(typeof(new OptionHandlerException("message", Exception.init))));

struct OptionElement {
	string[] opts;
	string help;
	bool val;
}

enum OptionType {
	Posix,
	Windows,
	None
}

@safe pure @nogc struct OptionHandler {

	this(string[] args, OptionType type = __currentType)
	{
		_args = args;
		_type = type;
	}

	bool read(T)(string opts, string help, T* pval = null)
	{
		OptionElement opte;
		import std.array : split;
		import std.algorithm : sort, any;
		import std.array : array;
		opte.opts = opts.split("|").sort!((a, b) => a.length < b.length)().array();
		opte.val = !is(T == bool);
		opte.help = help;

		if(_opts.any!(o => o.opts == opte.opts)())
			throw new OptionHandlerException("Trying to read the same option name twice");

		_opts ~= opte;

		return true;
	}

private:
	string[] _args;
	OptionElement[] _opts;
	OptionType _type;

	version(Windows) enum OptionType __currentType = OptionType.Windows;
	else enum OptionType __currentType = OptionType.Posix;
}

@system unittest
{
	auto args = ["prog", "--foo", "-b"];
	bool isFoo;
	OptionHandler optHandler = OptionHandler(args);
	optHandler.read("foo|f", "Some information about foo.", &isFoo);
	//assert(isFoo == true);
}
