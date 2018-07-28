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

module aurorafw.core.appcontext;

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