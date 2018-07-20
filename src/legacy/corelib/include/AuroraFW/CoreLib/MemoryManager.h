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

#ifndef AURORAFW_CORELIB_MEMORY_H
#define AURORAFW_CORELIB_MEMORY_H

#include <AuroraFW/CoreLib/Target/Compiler.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>
#include <AuroraFW/CoreLib/Type.h>

namespace AuroraFW {
	struct AFW_API MemoryStats
	{
		void add(size_t );
		void remove(size_t );

		size_t totalAllocated;
		size_t totalFreed;
		size_t currentUsed;
		size_t totalAllocations;
	};

	class AFW_API MemoryManager
	{
		static MemoryStats memStats;

	public:
		inline static MemoryStats& getMemoryStats() { return memStats; }
	};

	//struct AFW_API MemoryNode {
	//	int _ID
	//};


	class AFW_API MemoryLeakTracker {
	public:
		MemoryLeakTracker(const char* path, int line) : _path(path), _line(line) {}
		const char* _path;
		const int _line;
	};
}

#endif // AURORAFW_CORELIB_MEMORY_H
