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

module aurorafw.android.platform.bitmap;

/**
 * @addtogroup Bitmap
 * @{
 */

/**
 * @file aurorafw/android/platform/bitmap.d
 */

version (Android):
extern (C):
@system:
nothrow:
@nogc:

/** AndroidBitmap functions result code. */
enum
{
	/** Operation was successful. */
	ANDROID_BITMAP_RESULT_SUCCESS = 0,
	/** Bad parameter. */
	ANDROID_BITMAP_RESULT_BAD_PARAMETER = -1,
	/** JNI exception occured. */
	ANDROID_BITMAP_RESULT_JNI_EXCEPTION = -2,
	/** Allocation failed. */
	ANDROID_BITMAP_RESULT_ALLOCATION_FAILED = -3
}

/** Backward compatibility: this macro used to be misspelled. */
enum ANDROID_BITMAP_RESUT_SUCCESS = ANDROID_BITMAP_RESULT_SUCCESS;

/** Bitmap pixel format. */
enum AndroidBitmapFormat
{
	/** No format. */
	ANDROID_BITMAP_FORMAT_NONE = 0,
	/** Red: 8 bits, Green: 8 bits, Blue: 8 bits, Alpha: 8 bits. **/
	ANDROID_BITMAP_FORMAT_RGBA_8888 = 1,
	/** Red: 5 bits, Green: 6 bits, Blue: 5 bits. **/
	ANDROID_BITMAP_FORMAT_RGB_565 = 4,
	/** Deprecated in API level 13. Because of the poor quality of this configuration, it is advised to use ARGB_8888 instead. **/
	ANDROID_BITMAP_FORMAT_RGBA_4444 = 7,
	/** Alpha: 8 bits. */
	ANDROID_BITMAP_FORMAT_A_8 = 8
}

/** Bitmap info, see AndroidBitmap_getInfo(). */
struct AndroidBitmapInfo
{
	/** The bitmap width in pixels. */
	uint width;
	/** The bitmap height in pixels. */
	uint height;
	/** The number of byte per row. */
	uint stride;
	/** The bitmap pixel format. See {@link AndroidBitmapFormat} */
	int format;
	/** Unused. */
	uint flags; // 0 for now
}

/**
 * Given a java bitmap object, fill out the AndroidBitmapInfo struct for it.
 * If the call fails, the info parameter will be ignored.
 */
int AndroidBitmap_getInfo (
	JNIEnv* env,
	jobject jbitmap,
	AndroidBitmapInfo* info);

/**
 * Given a java bitmap object, attempt to lock the pixel address.
 * Locking will ensure that the memory for the pixels will not move
 * until the unlockPixels call, and ensure that, if the pixels had been
 * previously purged, they will have been restored.
 *
 * If this call succeeds, it must be balanced by a call to
 * AndroidBitmap_unlockPixels, after which time the address of the pixels should
 * no longer be used.
 *
 * If this succeeds, *addrPtr will be set to the pixel address. If the call
 * fails, addrPtr will be ignored.
 */
int AndroidBitmap_lockPixels (JNIEnv* env, jobject jbitmap, void** addrPtr);

/**
 * Call this to balance a successful call to AndroidBitmap_lockPixels.
 */
int AndroidBitmap_unlockPixels (JNIEnv* env, jobject jbitmap);

/** @} */
