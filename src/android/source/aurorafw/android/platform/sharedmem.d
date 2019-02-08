/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2017 The Android Open Source Project.
Copyright (C) 2018-2019 Aurora Free Open Source Software.

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
https://www.gnu.org/licenses/gpl-3.0.html.

NOTE: All products, services or anything associated to trademarks and
service marks used or referenced on this file are the property of their
respective companies/owners or its subsidiaries. Other names and brands
may be claimed as the property of others.

For more info about intellectual property visit: aurorafoss.org or
directly send an email to: contact (at) aurorafoss.org .

This file has bindings for an existing code, part of The Android Open Source
Project implementation. Check it out at android.googlesource.com .
*/

module aurorafw.android.platform.sharedmem;

/**
 * @addtogroup Memory
 * @{
 */

/**
 * @file aurorafw/android/platform/sharedmem.d
 * @brief Shared memory buffers that can be shared across process.
 */

version (Android):
extern (C):
@system:
nothrow:
@nogc:

/******************************************************************
 *
 * IMPORTANT NOTICE:
 *
 *   This file is part of Android's set of stable system headers
 *   exposed by the Android NDK (Native Development Kit).
 *
 *   Third-party source AND binary code relies on the definitions
 *   here to be FROZEN ON ALL UPCOMING PLATFORM RELEASES.
 *
 *   - DO NOT MODIFY ENUMS (EXCEPT IF YOU ADD NEW 32-BIT VALUES)
 *   - DO NOT MODIFY CONSTANTS OR FUNCTIONAL MACROS
 *   - DO NOT CHANGE THE SIGNATURE OF FUNCTIONS IN ANY WAY
 *   - DO NOT CHANGE THE LAYOUT OR SIZE OF STRUCTURES
 */

/**
 * Create a shared memory region.
 *
 * Create shared memory region and returns an file descriptor.  The resulting file descriptor can be
 * mmap'ed to process memory space with PROT_READ | PROT_WRITE | PROT_EXEC. Access to shared memory
 * region can be restricted with {@link ASharedMemory_setProt}.
 *
 * Use close() to release the shared memory region.
 *
 * Available since API level 26.
 *
 * \param name an optional name.
 * \param size size of the shared memory region
 * \return file descriptor that denotes the shared memory; error code on failure.
 */
int ASharedMemory_create (const(char)* name, size_t size);

/**
 * Get the size of the shared memory region.
 *
 * Available since API level 26.
 *
 * \param fd file descriptor of the shared memory region
 * \return size in bytes; 0 if fd is not a valid shared memory file descriptor.
 */
size_t ASharedMemory_getSize (int fd);

/**
 * Restrict access of shared memory region.
 *
 * This function restricts access of a shared memory region. Access can only be removed. The effect
 * applies globally to all file descriptors in all processes across the system that refer to this
 * shared memory region. Existing memory mapped regions are not affected.
 *
 * It is a common use case to create a shared memory region, map it read/write locally to intialize
 * content, and then send the shared memory to another process with read only access. Code example
 * as below (error handling omited).
 *
 *
 *     int fd = ASharedMemory_create("memory", 128);
 *
 *     // By default it has PROT_READ | PROT_WRITE | PROT_EXEC.
 *     char *buffer = (char *) mmap(NULL, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
 *
 *     strcpy(buffer, "This is an example."); // trivially initialize content
 *
 *     // limit access to read only
 *     ASharedMemory_setProt(fd, PROT_READ);
 *
 *     // share fd with another process here and the other process can only map with PROT_READ.
 *
 * Available since API level 26.
 *
 * \param fd   file descriptor of the shared memory region.
 * \param prot any bitwise-or'ed combination of PROT_READ, PROT_WRITE, PROT_EXEC denoting
 *             updated access. Note access can only be removed, but not added back.
 * \return 0 for success, error code on failure.
 */
int ASharedMemory_setProt (int fd, int prot);

// __ANDROID_API__ >= 26

// ANDROID_SHARED_MEMORY_H

/** @} */
