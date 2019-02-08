/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2018 The Android Open Source Project.
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

module aurorafw.android.platform.fdsan;

version (Android):
extern (C):
@system:
nothrow:
@nogc:

/*
 * Error checking for close(2).
 *
 * Mishandling of file descriptor ownership is a common source of errors that
 * can be extremely difficult to diagnose. Mistakes like the following can
 * result in seemingly 'impossible' failures showing up on other threads that
 * happened to try to open a file descriptor between the buggy code's close and
 * fclose:
 *
 *     int print(int fd) {
 *         int rc;
 *         char buf[128];
 *         while ((rc = read(fd, buf, sizeof(buf))) > 0) {
 *             printf("%.*s", rc);
 *         }
 *         close(fd);
 *     }
 *
 *     int bug() {
 *         FILE* f = fopen("foo", "r");
 *         print(fileno(f));
 *         fclose(f);
 *     }
 *
 * To make it easier to find this class of bugs, bionic provides a method to
 * require that file descriptors are closed by their owners. File descriptors
 * can be associated with tags with which they must be closed. This allows
 * objects that conceptually own an fd (FILE*, unique_fd, etc.) to use their
 * own address at the tag, to enforce that closure of the fd must come as a
 * result of their own destruction (fclose, ~unique_fd, etc.)
 *
 * By default, a file descriptor's tag is 0, and close(fd) is equivalent to
 * closing fd with the tag 0.
 */

/*
 * For improved diagnostics, the type of a file descriptors owner can be
 * encoded in the most significant byte of the owner tag. Values of 0 and 0xff
 * are ignored, which allows for raw pointers to be used as owner tags without
 * modification.
 */
enum android_fdsan_owner_type
{
    /*
     * Generic Java or native owners.
     *
     * Generic Java objects always use 255 as their type, using identityHashCode
     * as the value of the tag, leaving bits 33-56 unset. Native pointers are sign
     * extended from 48-bits of virtual address space, and so can have the MSB
     * set to 255 as well. Use the value of bits 49-56 to distinguish between
     * these cases.
     */
    ANDROID_FDSAN_OWNER_TYPE_GENERIC_00 = 0,
    ANDROID_FDSAN_OWNER_TYPE_GENERIC_FF = 255,

    /* FILE* */
    ANDROID_FDSAN_OWNER_TYPE_FILE = 1,

    /* DIR* */
    ANDROID_FDSAN_OWNER_TYPE_DIR = 2,

    /* android::base::unique_fd */
    ANDROID_FDSAN_OWNER_TYPE_UNIQUE_FD = 3,

    /* java.io.FileInputStream */
    ANDROID_FDSAN_OWNER_TYPE_FILEINPUTSTREAM = 251,

    /* java.io.FileOutputStream */
    ANDROID_FDSAN_OWNER_TYPE_FILEOUTPUTSTREAM = 252,

    /* java.io.RandomAccessFile */
    ANDROID_FDSAN_OWNER_TYPE_RANDOMACCESSFILE = 253,

    /* android.os.ParcelFileDescriptor */
    ANDROID_FDSAN_OWNER_TYPE_PARCELFILEDESCRIPTOR = 254
}

/*
 * Create an owner tag with the specified type and least significant 56 bits of tag.
 */

ulong android_fdsan_create_owner_tag (android_fdsan_owner_type type, ulong tag);

/*
 * Exchange a file descriptor's tag.
 *
 * Logs and aborts if the fd's tag does not match expected_tag.
 */
void android_fdsan_exchange_owner_tag (int fd, ulong expected_tag, ulong new_tag);

/*
 * Close a file descriptor with a tag, and resets the tag to 0.
 *
 * Logs and aborts if the tag is incorrect.
 */
int android_fdsan_close_with_tag (int fd, ulong tag);
/* __ANDROID_API__ >= __ANDROID_API_FUTURE__ */

enum android_fdsan_error_level
{
    // No errors.
    ANDROID_FDSAN_ERROR_LEVEL_DISABLED = 0,

    // Warn once(ish) on error, and then downgrade to ANDROID_FDSAN_ERROR_LEVEL_DISABLED.
    ANDROID_FDSAN_ERROR_LEVEL_WARN_ONCE = 1,

    // Warn always on error.
    ANDROID_FDSAN_ERROR_LEVEL_WARN_ALWAYS = 2,

    // Abort on error.
    ANDROID_FDSAN_ERROR_LEVEL_FATAL = 3
}

/*
 * Get the error level.
 */

android_fdsan_error_level android_fdsan_get_error_level ();

/*
 * Set the error level and return the previous state.
 *
 * Error checking is automatically disabled in the child of a fork, to maintain
 * compatibility with code that forks, blindly closes FDs, and then execs.
 *
 * In cases such as the zygote, where the child has no intention of calling
 * exec, call this function to reenable fdsan checks.
 *
 * This function is not thread-safe and does not synchronize with checks of the
 * value, and so should probably only be called in single-threaded contexts
 * (e.g. postfork).
 */
android_fdsan_error_level android_fdsan_set_error_level (android_fdsan_error_level new_level);
/* __ANDROID_API__ >= __ANDROID_API_FUTURE__ */

