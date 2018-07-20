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

#include <AuroraFW/Core/ApplicationContext.h>
#include <AuroraFW/Core/DebugManager.h>

namespace AuroraFW {
	ApplicationContext::ApplicationContext(const std::string name, int argc, char* argv[])
		: _name(name), _opts(OptionHandler(argc, argv))
	{
		_opts.addOption({"afw-debug", "Enable the aurora built-in debug logger"});
		if(_opts.getOption("afw-debug").active)
			DebugManager::enable();

		DebugManager::Log("creating new application");
		DebugManager::Log("application is created.");
	}

	ApplicationContext::~ApplicationContext()
	{
		DebugManager::Log("application is destroyed.");
	}

	void ApplicationContext::start()
	{
		DebugManager::Log("application is starting");
		_internalStart();
		onStart();
		DebugManager::Log("application started");
	}

	void ApplicationContext::close()
	{
		DebugManager::Log("application is closing");
		_internalClose();
		onClose();
		DebugManager::Log("application closed");
	}

	void ApplicationContext::_internalStart()
	{

	}

	void ApplicationContext::_internalClose()
	{

	}

	void ApplicationContext::_internalSetName(std::string )
	{}

	void ApplicationContext::onStart()
	{}

	void ApplicationContext::onClose()
	{}
}