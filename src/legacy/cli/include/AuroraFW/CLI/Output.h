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

#ifndef INCLUDE_H_AFW_SHELL_OUTPUT
#define INCLUDE_H_AFW_SHELL_OUTPUT

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/STDL/STL/OStream.h>

namespace AuroraFW {
	namespace CLI {
		AFW_API extern std::ostream Output;
		AFW_API extern std::wostream wOutput;

		template<typename _CharT, typename _Traits>
		inline std::basic_ostream<_CharT, _Traits>& EndLine(std::basic_ostream<_CharT, _Traits>& __os)
		{
			return flush(__os.put(__os.widen('\n')));
		}

		template<typename _CharT, typename _Traits>
		inline std::basic_ostream<_CharT, _Traits>& Flush(std::basic_ostream<_CharT, _Traits>& __os)
		{
			return __os.flush();
		}
	}
}

#endif // INCLUDE_H_AFW_SHELL_OUTPUT
