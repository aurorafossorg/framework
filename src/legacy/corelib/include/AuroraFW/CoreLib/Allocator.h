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

#ifndef AURORAFW_CORELIB_ALLOCATOR_H
#define AURORAFW_CORELIB_ALLOCATOR_H

#include <AuroraFW/CoreLib/Target/Compiler.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/CoreLib/MemoryManager.h>
#include <new>
#include <assert.h>

namespace AuroraFW {
	class AFW_API MemoryAllocator {
	public:
		MemoryAllocator();
		MemoryAllocator(MemoryStats );
		~MemoryAllocator();

		inline void* allocate(size_t size) { return allocate(size, _stats); }
		inline void* allocate(size_t size, const char* file, uint line) { return allocate(size, _stats, file, line); }
		static void* allocate(size_t , MemoryStats& );
		static void* allocate(size_t , MemoryStats& , const char* , uint );

		inline void free(void* block) { free(block, _stats); }
		inline void free(void* block, size_t size) { free(block, size, _stats); }
		inline void free(void* block, const char* file, uint line) { free(block, _stats, file, line); }
		inline void free(void* block, size_t size, const char* file, uint line) { free(block, size, _stats, file, line); }
		static void free(void* , MemoryStats& );
		static void free(void* , size_t , MemoryStats& );
		#ifdef AFW__VERBOSE
			static void free(void *block, MemoryStats &stats, const char *, uint);
		#else
			inline static void free(void *block, MemoryStats &stats, const char *, uint) { return free(block, stats); }
		#endif
		static void free(void *block, size_t size, MemoryStats &stats, const char *, uint);

		inline MemoryStats getMemoryStats() const { return _stats; }

	private:
		MemoryStats _stats;
	};
}

#if defined(AFW__DEBUG) && defined(AFW__CUSTOM_ALLOCATOR)
#define AFW_NEW new(__FILE__, __LINE__)
#define AFW_DELETE delete(__FILE__, __LINE__)
#else
#define AFW_NEW new
#define AFW_DELETE delete
#endif

#if AFW__CUSTOM_ALLOCATOR
inline void* operator new(size_t size, const char* file, uint line)
{
	return AuroraFW::MemoryAllocator::allocate(size, AuroraFW::MemoryManager::getMemoryStats(), file, line);
}

inline void* operator new[](size_t size, const char* file, uint line)
{
	return AuroraFW::MemoryAllocator::allocate(size, AuroraFW::MemoryManager::getMemoryStats(), file, line);
}

inline void* operator new(size_t size)
{
	return AuroraFW::MemoryAllocator::allocate(size, AuroraFW::MemoryManager::getMemoryStats());
}

inline void* operator new[](size_t size)
{
	return AuroraFW::MemoryAllocator::allocate(size, AuroraFW::MemoryManager::getMemoryStats());
}

inline void operator delete(void* block) AFW_NOEXCEPT
{
	AuroraFW::MemoryAllocator::free(block, AuroraFW::MemoryManager::getMemoryStats());
}

inline void operator delete[](void* block) AFW_NOEXCEPT
{
	AuroraFW::MemoryAllocator::free(block, AuroraFW::MemoryManager::getMemoryStats());
}

inline void operator delete(void* block, size_t) AFW_NOEXCEPT
{
	AuroraFW::MemoryAllocator::free(block, AuroraFW::MemoryManager::getMemoryStats());
}

inline void operator delete[](void* block, size_t) AFW_NOEXCEPT
{
	AuroraFW::MemoryAllocator::free(block, AuroraFW::MemoryManager::getMemoryStats());
}
#endif

#endif // AURORAFW_CORELIB_ALLOCATOR_H
