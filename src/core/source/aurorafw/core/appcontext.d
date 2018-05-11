module aurorafw.core.appcontext;

/****************************************************************************
** ┌─┐┬ ┬┬─┐┌─┐┬─┐┌─┐  ┌─┐┬─┐┌─┐┌┬┐┌─┐┬ ┬┌─┐┬─┐┬┌─
** ├─┤│ │├┬┘│ │├┬┘├─┤  ├┤ ├┬┘├─┤│││├┤ ││││ │├┬┘├┴┐
** ┴ ┴└─┘┴└─└─┘┴└─┴ ┴  └  ┴└─┴ ┴┴ ┴└─┘└┴┘└─┘┴└─┴ ┴
** A Powerful General Purpose Framework
** More information in: https://aurora-fw.github.io/
**
** Copyright (C) 2018 Aurora Framework, All rights reserved.
**
** This file is part of the Aurora Framework. This framework is free
** software; you can redistribute it and/or modify it under the terms of
** the GNU Lesser General Public License version 3 as published by the
** Free Software Foundation and appearing in the file LICENSE included in
** the packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************/

import aurorafw.core.opt;
import aurorafw.core.debugmanager;

abstract class ApplicationContext {
public:
	final this(string name = "AuroraFW Application", string[] args = null)
	{
		_name = name;
		_opts = OptionHandler(args);
		_opts.add("afw-debug", "Enable the aurora built-in debug logger");
		if(_opts.option("afw-debug").active)
		{
			afwDebugFlag = true;
			debug trace(afwDebugFlag, "Debug is now enabled");
		}

		debug trace(afwDebugFlag, "creating new application");
		debug trace(afwDebugFlag, "application is created.");
	}

	pure ~this() @safe
	{
		debug trace(afwDebugFlag, "application is destroyed.");
	}

	void onStart() @safe;
	void onClose() @safe;

	final void start() @safe
	{
		debug trace(afwDebugFlag, "application is starting");
		_internalStart();
		onStart();
		debug trace(afwDebugFlag, "application started");
	}

	final void close() @safe
	{
		debug trace(afwDebugFlag, "application is closing");
		_internalClose();
		onClose();
		debug trace(afwDebugFlag, "application closed");
	}

	pure @property string name() @safe { return _name; }
	pure @property string name(string name) @safe { return _name = name; }

protected:
	void _internalSetName(string ) @safe;
	void _internalStart() @safe;
	void _internalClose() @safe;

private:
	string _name;
	OptionHandler _opts;
}