/*****************************************************************************
**                                     __
**                                    / _|
**   __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
**  / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
** | (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
**  \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/
**
** Copyright (C) 2018-2019 Aurora Free Open Source Software.
**
** This file is part of the Aurora Free Open Source Software. This
** organization promote free and open source software that you can
** redistribute and/or modify under the terms of the GNU Lesser General
** Public License Version 3 as published by the Free Software Foundation or
** (at your option) any later version approved by the Aurora Free Open Source
** Software Organization. The license is available in the package root path
** as 'LICENSE' file. Please review the following information to ensure the
** GNU Lesser General Public License version 3 requirements will be met:
** https://www.gnu.org/licenses/lgpl.html .
**
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3 or later as published by the Free Software
** Foundation. Please review the following information to ensure the GNU
** General Public License requirements will be met:
** http://www.gnu.org/licenses/gpl-3.0.html.
**
** NOTE: All products, services or anything associated to trademarks and
** service marks used or referenced on this file are the property of their
** respective companies/owners or its subsidiaries. Other names and brands
** may be claimed as the property of others.
**
** For more info about intellectual property visit: aurorafoss.org or
** directly send an email to: contact (at) aurorafoss.org .
*****************************************************************************/

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
