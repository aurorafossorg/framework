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

#include <AuroraFW/STDL/LibC/Assert.h>
#include <AuroraFW/STDL/LibC/String.h>
#include <AuroraFW/Core/DebugManager.h>

#include <malloc.h>

namespace AuroraFW {
	MemoryAllocator::MemoryAllocator()
		: _stats({0,0,0,0})
	{}

	MemoryAllocator::MemoryAllocator(MemoryStats stats)
		: _stats(stats)
	{}

	MemoryAllocator::~MemoryAllocator()
	{}

	void* MemoryAllocator::allocate(size_t size, MemoryStats &stats)
	{
		stats.add(size);
		#ifdef AFW__VERBOSE
			std::cout << "=!!=\tAllocate with size=" << size << std::endl
				<< "=!!=\tTotal memory Allocated: " << stats.totalAllocated << std::endl
				<< "=!!=\tTotal memory freed: " << stats.totalFreed << std::endl
				<< "=!!=\tMemory currently used: " << stats.currentUsed << std::endl
				<< "=!!=\tTotal allocation: " << stats.totalAllocations << "\n" << std::endl;
		#endif
		size_t asize = size + sizeof(size_t);
		byte_t* ret = (byte_t*)AFW_ALIGNED_ALLOC(asize, 2 * sizeof(size_t));
		//byte_t* ret = (byte_t*)malloc(asize);
		if(ret == AFW_NULLPTR)
			std::cerr << "=##=\tbad alloc" << std::endl;
		memset(ret, 0, asize);
		memcpy(ret, &size, sizeof(size_t));
		ret += sizeof(size_t);
		return ret;
	}

	void* MemoryAllocator::allocate(size_t size, MemoryStats &stats, const char* file, uint line)
	{
		#ifdef AFW__VERBOSE
			std::cout << "=@@=\tallocation at " << file << ":" << line << std::endl;
		#endif

		if(size > 1024 * 1024)
			DebugManager::Log("Large allocation (>1MB) at ", file, ":", line);
		return allocate(size, stats);
	}

	void MemoryAllocator::free(void* block, MemoryStats &stats)
	{
		if(block == AFW_NULLPTR)
#ifdef AFW__VERBOSE
			std::cerr << "=##=\tinvalid pointer (0x0)" << std::endl;
#else
			return;
#endif
		byte_t *mem = (byte_t *)block - sizeof(size_t);
		size_t size = *(size_t *)mem;
		stats.remove(size);
#ifdef AFW__VERBOSE
		std::cout << "=!!=\tDelete a block of memory with size=" << size << std::endl
			<< "=!!=\tTotal memory Allocated: " << stats.totalAllocated << std::endl
			<< "=!!=\tTotal memory freed: " << stats.totalFreed << std::endl
			<< "=!!=\tMemory currently used: " << stats.currentUsed << std::endl
			<< "=!!=\tTotal allocation: " << stats.totalAllocations << "\n" << std::endl;
#endif
		AFW_ALIGNED_FREE(mem);
	}

	#ifdef AFW__VERBOSE
		void MemoryAllocator::free(void* block, MemoryStats &stats, const char* file, uint line)
		{
			std::cout << "=@@=\tdeallocation at " << file << ":" << line << std::endl;
			return free(block, stats);
		}
	#endif
}
