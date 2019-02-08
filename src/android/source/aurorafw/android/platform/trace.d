/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2015 The Android Open Source Project.
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

module aurorafw.android.platform.trace;

/**
 * @addtogroup Tracing
 * @{
 */

/**
 * @file aurorafw/android/platform/trace.d
 * @brief Writes trace events to the system trace buffer.
 *
 * These trace events can be collected and visualized using the Systrace tool.
 * For information about using the Systrace tool, read <a href="https://developer.android.com/studio/profile/systrace.html">Analyzing UI Performance with Systrace</a>.
 *
 * Available since API level 23.
 */

version (Android):
extern (C):
@system:
nothrow:
@nogc:

/**
 * Returns true if tracing is enabled. Use this to avoid expensive computation only necessary
 * when tracing is enabled.
 *
 * Available since API level 23.
 */
bool ATrace_isEnabled ();

/**
 * Writes a tracing message to indicate that the given section of code has begun. This call must be
 * followed by a corresponding call to {@link ATrace_endSection} on the same thread.
 *
 * Note: At this time the vertical bar character '|' and newline character '\\n' are used internally
 * by the tracing mechanism. If \p sectionName contains these characters they will be replaced with a
 * space character in the trace.
 *
 * Available since API level 23.
 */
void ATrace_beginSection (const(char)* sectionName);

/**
 * Writes a tracing message to indicate that a given section of code has ended. This call must be
 * preceeded by a corresponding call to {@link ATrace_beginSection} on the same thread. Calling this method
 * will mark the end of the most recently begun section of code, so care must be taken to ensure
 * that {@link ATrace_beginSection}/{@link ATrace_endSection} pairs are properly nested and called from the same thread.
 *
 * Available since API level 23.
 */
void ATrace_endSection ();

/* __ANDROID_API__ >= 23 */

// ANDROID_NATIVE_TRACE_H

/** @} */
