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

module aurorafw.android.platform.sharedmem_jni;

/**
 * @addtogroup Memory
 * @{
 */

/**
 * @file aurorafw/android/platform/sharedmem_jni.d
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
 * Returns a dup'd FD from the given Java android.os.SharedMemory object. The returned file
 * descriptor has all the same properties & capabilities as the FD returned from
 * ASharedMemory_create(), however the protection flags will be the same as those of the
 * android.os.SharedMemory object.
 *
 * Use close() to release the shared memory region.
 *
 * Available since API level 27.
 *
 * \param env The JNIEnv* pointer
 * \param sharedMemory The Java android.os.SharedMemory object
 * \return file descriptor that denotes the shared memory; -1 if the shared memory object is
 *      already closed, if the JNIEnv or jobject is NULL, or if there are too many open file
 *      descriptors (errno=EMFILE)
 */
int ASharedMemory_dupFromJava (JNIEnv* env, jobject sharedMemory);

// __ANDROID_API__ >= 27

// ANDROID_SHARED_MEMORY_JNI_H

/** @} */
