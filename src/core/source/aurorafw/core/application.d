module aurorafw.core.application;

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

import core.stdc.stdlib : exit, EXIT_SUCCESS, EXIT_FAILURE;
import aurorafw.core.debugmanager;

struct Application {
public:
	this(immutable shared string[] args, immutable void function(Application) func)
	{
		this.args = args;
		foreach(string str; this.args)
			if(str == "--afw-debug")
			{
				afwDebugFlag = true;
				debug trace(afwDebugFlag, "Debug is now enabled");
			}

		func(this);
	}

	static void exitSuccess() @trusted
	{
		debug trace(afwDebugFlag, "application return success code: ", EXIT_SUCCESS);
		exit(EXIT_SUCCESS);
	}

	static void exitFail() @trusted
	{
		debug trace(afwDebugFlag, "application return error code: ", EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}

	immutable shared string[] args;
}