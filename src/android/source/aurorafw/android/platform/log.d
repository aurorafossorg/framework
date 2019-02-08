/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2009 The Android Open Source Project.
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

module aurorafw.android.platform.log;

import core.stdc.stdarg;

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
 *   exposed by the Android NDK (Native Development Kit) since
 *   platform release 1.5
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
 * @addtogroup Logging
 * @{
 */

/**
 * \file
 *
 * Support routines to send messages to the Android log buffer,
 * which can later be accessed through the `logcat` utility.
 *
 * Each log message must have
 *   - a priority
 *   - a log tag
 *   - some text
 *
 * The tag normally corresponds to the component that emits the log message,
 * and should be reasonably small.
 *
 * Log message text may be truncated to less than an implementation-specific
 * limit (1023 bytes).
 *
 * Note that a newline character ("\n") will be appended automatically to your
 * log message, if not already there. It is not possible to send several
 * messages and have them appear on a single line in logcat.
 *
 * Please use logging in moderation:
 *
 *  - Sending log messages eats CPU and slow down your application and the
 *    system.
 *
 *  - The circular log buffer is pretty small, so sending many messages
 *    will hide other important log messages.
 *
 *  - In release builds, only send log messages to account for exceptional
 *    conditions.
 */

/**
 * Android log priority values, in increasing order of priority.
 */
enum android_LogPriority
{
    /** For internal use only.  */
    ANDROID_LOG_UNKNOWN = 0,
    /** The default priority, for internal use only.  */
    ANDROID_LOG_DEFAULT = 1, /* only for SetMinPriority() */
    /** Verbose logging. Should typically be disabled for a release apk. */
    ANDROID_LOG_VERBOSE = 2,
    /** Debug logging. Should typically be disabled for a release apk. */
    ANDROID_LOG_DEBUG = 3,
    /** Informational logging. Should typically be disabled for a release apk. */
    ANDROID_LOG_INFO = 4,
    /** Warning logging. For use with recoverable failures. */
    ANDROID_LOG_WARN = 5,
    /** Error logging. For use with unrecoverable failures. */
    ANDROID_LOG_ERROR = 6,
    /** Fatal logging. For use when aborting. */
    ANDROID_LOG_FATAL = 7,
    /** For internal use only.  */
    ANDROID_LOG_SILENT = 8 /* only for SetMinPriority(); must be last */
}

/**
 * Writes the constant string `text` to the log, with priority `prio` and tag
 * `tag`.
 */
int __android_log_write (int prio, const(char)* tag, const(char)* text);

/**
 * Writes a formatted string to the log, with priority `prio` and tag `tag`.
 * The details of formatting are the same as for
 * [printf(3)](http://man7.org/linux/man-pages/man3/printf.3.html).
 */
int __android_log_print (int prio, const(char)* tag, const(char)* fmt, ...);

/**
 * Equivalent to `__android_log_print`, but taking a `va_list`.
 * (If `__android_log_print` is like `printf`, this is like `vprintf`.)
 */
int __android_log_vprint (
    int prio,
    const(char)* tag,
    const(char)* fmt,
    va_list ap);

/**
 * Writes an assertion failure to the log (as `ANDROID_LOG_FATAL`) and to
 * stderr, before calling
 * [abort(3)](http://man7.org/linux/man-pages/man3/abort.3.html).
 *
 * If `fmt` is non-null, `cond` is unused. If `fmt` is null, the string
 * `Assertion failed: %s` is used with `cond` as the string argument.
 * If both `fmt` and `cond` are null, a default string is provided.
 *
 * Most callers should use
 * [assert(3)](http://man7.org/linux/man-pages/man3/assert.3.html) from
 * `<assert.h>` instead, or the `__assert` and `__assert2` functions provided by
 * bionic if more control is needed. They support automatically including the
 * source filename and line number more conveniently than this function.
 */
void __android_log_assert (
    const(char)* cond,
    const(char)* tag,
    const(char)* fmt,
    ...);

enum log_id
{
    LOG_ID_MIN = 0,

    LOG_ID_MAIN = 0,
    LOG_ID_RADIO = 1,
    LOG_ID_EVENTS = 2,
    LOG_ID_SYSTEM = 3,
    LOG_ID_CRASH = 4,
    LOG_ID_STATS = 5,
    LOG_ID_SECURITY = 6,
    LOG_ID_KERNEL = 7, /* place last, third-parties can not use it */

    LOG_ID_MAX = 8
}

alias log_id_t = log_id;

/*
 * Send a simple string to the log.
 */
int __android_log_buf_write (
    int bufID,
    int prio,
    const(char)* tag,
    const(char)* text);
int __android_log_buf_print (
    int bufID,
    int prio,
    const(char)* tag,
    const(char)* fmt,
    ...);

/** @} */

/* _ANDROID_LOG_H */
