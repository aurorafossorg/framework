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

#ifndef AURORAFW_CORE_APPLICATIONCONTEXT_H
#define AURORAFW_CORE_APPLICATIONCONTEXT_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/STDL/STL/String.h>
#include <AuroraFW/STDL/STL/Vector.h>

#include <AuroraFW/Core/OptionHandler.h>

namespace AuroraFW {
	class AFW_API ApplicationContext
	{
	public:
		explicit ApplicationContext(const std::string = "AuroraFW Application", int = 0, char** = AFW_NULL);
		virtual ~ApplicationContext();

		virtual void onStart();
		virtual void onClose();
		void start();
		void close();

		std::string getName();
		void setName(std::string );

	private:
		virtual void _internalSetName(std::string );
		virtual void _internalStart();
		virtual void _internalClose();
	
		std::string _name;
		OptionHandler _opts;
	};
}

#endif // AURORAFW_CORE_APPLICATIONCONTEXT_H