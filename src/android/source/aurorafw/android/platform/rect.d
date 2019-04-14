/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2010 The Android Open Source Project.
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

module aurorafw.android.platform.rect;

/**
 * @addtogroup NativeActivity Native Activity
 * @{
 */

/**
 * @file aurorafw/android/platform/rect.d
 */

version (Android):
extern (C):
@system:
nothrow:
@nogc:

/**
 * Rectangular window area.
 *
 * This is the NDK equivalent of the android.graphics.Rect class in Java. It is
 * used with {@link ANativeActivityCallbacks::onContentRectChanged} event
 * callback and the ANativeWindow_lock() function.
 *
 * In a valid ARect, left <= right and top <= bottom. ARect with left=0, top=10,
 * right=1, bottom=11 contains only one pixel at x=0, y=10.
 */
struct ARect
{
	/// Minimum X coordinate of the rectangle.
	int left;
	/// Minimum Y coordinate of the rectangle.
	int top;
	/// Maximum X coordinate of the rectangle.
	int right;
	/// Maximum Y coordinate of the rectangle.
	int bottom;
}

// ANDROID_RECT_H

/** @} */
