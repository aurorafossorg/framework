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

#ifndef INCLUDE_H_AFW_INFO_RAM
#define INCLUDE_H_AFW_INFO_RAM

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

namespace AuroraFW {
	namespace IO {
		namespace Info
		{
			struct AFW_API SystemMemory
			{
				size_t totalPhysicalMemory;
				size_t availablePhysicalMemory;

				size_t totalVirtualMemory;
				size_t availableVirtualMemory;
			};

			AFW_API extern size_t getTotalVirtualMemory(); // Total virtual memory size in bytes
			AFW_API extern size_t getUsedVirtualMemory(); // Used virtual memory size in bytes
			AFW_API extern size_t getFreeVirtualMemory(); // Free virtual memory size in bytes
			AFW_API extern size_t getTotalPhysicalMemory(); // Total pysical memory size in bytes
			AFW_API extern size_t getUsedPhysicalMemory(); // Used pysical memory size in bytes
			AFW_API extern size_t getFreePhysicalMemory(); // Free pysical memory size in bytes
			AFW_API extern SystemMemory getSystemMemory();
		}
	}
}

#endif // INCLUDE_H_AFW_INFO_RAM
