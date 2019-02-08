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

module aurorafw.android.platform.choreographer;

/**
 * @addtogroup Choreographer
 * @{
 */

/**
 * @file aurorafw/android/platform/choreographer.d
 */

import core.stdc.config;

version (Android):
extern (C):
@system:
nothrow:
@nogc:

struct AChoreographer;

/**
 * Prototype of the function that is called when a new frame is being rendered.
 * It's passed the time that the frame is being rendered as nanoseconds in the
 * CLOCK_MONOTONIC time base, as well as the data pointer provided by the
 * application that registered a callback. All callbacks that run as part of
 * rendering a frame will observe the same frame time, so it should be used
 * whenever events need to be synchronized (e.g. animations).
 */
alias AChoreographer_frameCallback = void function (c_long frameTimeNanos, void* data);

/**
 * Get the AChoreographer instance for the current thread. This must be called
 * on an ALooper thread.
 */
AChoreographer* AChoreographer_getInstance ();

/**
 * Post a callback to be run on the next frame. The data pointer provided will
 * be passed to the callback function when it's called.
 */
void AChoreographer_postFrameCallback (
    AChoreographer* choreographer,
    AChoreographer_frameCallback callback,
    void* data);

/**
 * Post a callback to be run on the frame following the specified delay. The
 * data pointer provided will be passed to the callback function when it's
 * called.
 */
void AChoreographer_postFrameCallbackDelayed (
    AChoreographer* choreographer,
    AChoreographer_frameCallback callback,
    void* data,
    c_long delayMillis);

/* __ANDROID_API__ >= 24 */

// ANDROID_CHOREOGRAPHER_H

/** @} */
