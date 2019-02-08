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

module aurorafw.android.platform.sync;

/**
 * @addtogroup Sync
 * @{
 */

/**
 * @file aurorafw/android/platform/sync.d
 */

version (Android):
extern (C):
@system:
nothrow:
@nogc:

/* Fences indicate the status of an asynchronous task. They are initially
 * in unsignaled state (0), and make a one-time transition to either signaled
 * (1) or error (< 0) state. A sync file is a collection of one or more fences;
 * the sync file's status is error if any of its fences are in error state,
 * signaled if all of the child fences are signaled, or unsignaled otherwise.
 *
 * Sync files are created by various device APIs in response to submitting
 * tasks to the device. Standard file descriptor lifetime syscalls like dup()
 * and close() are used to manage sync file lifetime.
 *
 * The poll(), ppoll(), or select() syscalls can be used to wait for the sync
 * file to change status, or (with a timeout of zero) to check its status.
 *
 * The functions below provide a few additional sync-specific operations.
 */

/**
 * Merge two sync files.
 *
 * This produces a new sync file with the given name which has the union of the
 * two original sync file's fences; redundant fences may be removed.
 *
 * If one of the input sync files is signaled or invalid, then this function
 * may behave like dup(): the new file descriptor refers to the valid/unsignaled
 * sync file with its original name, rather than a new sync file.
 *
 * The original fences remain valid, and the caller is responsible for closing
 * them.
 *
 * Available since API level 26.
 */
int sync_merge (const(char)* name, int fd1, int fd2);

/**
 * Retrieve detailed information about a sync file and its fences.
 *
 * The returned sync_file_info must be freed by calling sync_file_info_free().
 *
 * Available since API level 26.
 */
sync_file_info_* sync_file_info (int fd);

/**
 * Get the array of fence infos from the sync file's info.
 *
 * The returned array is owned by the parent sync file info, and has
 * info->num_fences entries.
 *
 * Available since API level 26.
 */

// This header should compile in C, but some C++ projects enable
// warnings-as-error for C-style casts.
sync_fence_info* sync_get_fence_info (const(sync_file_info_)* info);

/**
 * Free a struct sync_file_info structure
 *
 * Available since API level 26.
 */
void sync_file_info_free (sync_file_info_* info);

/* __ANDROID_API__ >= 26 */

/* ANDROID_SYNC_H */

/** @} */
