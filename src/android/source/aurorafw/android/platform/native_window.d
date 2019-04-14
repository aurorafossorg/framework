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

module aurorafw.android.platform.native_window;

/**
 * @addtogroup NativeActivity Native Activity
 * @{
 */

/**
 * @file aurorafw/android/platform/native_window.d
 * @brief API for accessing a native window.
 */

version (Android):
extern (C):
@system:
nothrow:
@nogc:

/**
 * Legacy window pixel format names, kept for backwards compatibility.
 * New code and APIs should use AHARDWAREBUFFER_FORMAT_*.
 */
enum
{
	// NOTE: these values must match the values from graphics/common/x.x/types.hal

	/** Red: 8 bits, Green: 8 bits, Blue: 8 bits, Alpha: 8 bits. **/
	WINDOW_FORMAT_RGBA_8888 = 1,
	/** Red: 8 bits, Green: 8 bits, Blue: 8 bits, Unused: 8 bits. **/
	WINDOW_FORMAT_RGBX_8888 = 2,
	/** Red: 5 bits, Green: 6 bits, Blue: 5 bits. **/
	WINDOW_FORMAT_RGB_565 = 4
}

/**
 * Transforms that can be applied to buffers as they are displayed to a window.
 *
 * Supported transforms are any combination of horizontal mirror, vertical
 * mirror, and clockwise 90 degree rotation, in that order. Rotations of 180
 * and 270 degrees are made up of those basic transforms.
 */
enum ANativeWindowTransform
{
	ANATIVEWINDOW_TRANSFORM_IDENTITY = 0,
	ANATIVEWINDOW_TRANSFORM_MIRROR_HORIZONTAL = 1,
	ANATIVEWINDOW_TRANSFORM_MIRROR_VERTICAL = 2,
	ANATIVEWINDOW_TRANSFORM_ROTATE_90 = 4,

	ANATIVEWINDOW_TRANSFORM_ROTATE_180 = 3,
	ANATIVEWINDOW_TRANSFORM_ROTATE_270 = 7
}

struct ANativeWindow;
/**
 * Opaque type that provides access to a native window.
 *
 * A pointer can be obtained using {@link ANativeWindow_fromSurface()}.
 */

/**
 * Struct that represents a windows buffer.
 *
 * A pointer can be obtained using {@link ANativeWindow_lock()}.
 */
struct ANativeWindow_Buffer
{
	/// The number of pixels that are shown horizontally.
	int width;

	/// The number of pixels that are shown vertically.
	int height;

	/// The number of *pixels* that a line in the buffer takes in
	/// memory. This may be >= width.
	int stride;

	/// The format of the buffer. One of AHARDWAREBUFFER_FORMAT_*
	int format;

	/// The actual bits.
	void* bits;

	/// Do not touch.
	uint[6] reserved;
}

/**
 * Acquire a reference on the given {@link ANativeWindow} object. This prevents the object
 * from being deleted until the reference is removed.
 */
void ANativeWindow_acquire (ANativeWindow* window);

/**
 * Remove a reference that was previously acquired with {@link ANativeWindow_acquire()}.
 */
void ANativeWindow_release (ANativeWindow* window);

/**
 * Return the current width in pixels of the window surface.
 *
 * \return negative value on error.
 */
int ANativeWindow_getWidth (ANativeWindow* window);

/**
 * Return the current height in pixels of the window surface.
 *
 * \return a negative value on error.
 */
int ANativeWindow_getHeight (ANativeWindow* window);

/**
 * Return the current pixel format (AHARDWAREBUFFER_FORMAT_*) of the window surface.
 *
 * \return a negative value on error.
 */
int ANativeWindow_getFormat (ANativeWindow* window);

/**
 * Change the format and size of the window buffers.
 *
 * The width and height control the number of pixels in the buffers, not the
 * dimensions of the window on screen. If these are different than the
 * window's physical size, then its buffer will be scaled to match that size
 * when compositing it to the screen. The width and height must be either both zero
 * or both non-zero.
 *
 * For all of these parameters, if 0 is supplied then the window's base
 * value will come back in force.
 *
 * \param width width of the buffers in pixels.
 * \param height height of the buffers in pixels.
 * \param format one of AHARDWAREBUFFER_FORMAT_* constants.
 * \return 0 for success, or a negative value on error.
 */
int ANativeWindow_setBuffersGeometry (
	ANativeWindow* window,
	int width,
	int height,
	int format);

/**
 * Lock the window's next drawing surface for writing.
 * inOutDirtyBounds is used as an in/out parameter, upon entering the
 * function, it contains the dirty region, that is, the region the caller
 * intends to redraw. When the function returns, inOutDirtyBounds is updated
 * with the actual area the caller needs to redraw -- this region is often
 * extended by {@link ANativeWindow_lock}.
 *
 * \return 0 for success, or a negative value on error.
 */
int ANativeWindow_lock (
	ANativeWindow* window,
	ANativeWindow_Buffer* outBuffer,
	ARect* inOutDirtyBounds);

/**
 * Unlock the window's drawing surface after previously locking it,
 * posting the new buffer to the display.
 *
 * \return 0 for success, or a negative value on error.
 */
int ANativeWindow_unlockAndPost (ANativeWindow* window);

/**
 * Set a transform that will be applied to future buffers posted to the window.
 *
 * \param transform combination of {@link ANativeWindowTransform} flags
 * \return 0 for success, or -EINVAL if \p transform is invalid
 */
int ANativeWindow_setBuffersTransform (ANativeWindow* window, int transform);

// __ANDROID_API__ >= 26

/**
 * All buffers queued after this call will be associated with the dataSpace
 * parameter specified.
 *
 * dataSpace specifies additional information about the buffer.
 * For example, it can be used to convey the color space of the image data in
 * the buffer, or it can be used to indicate that the buffers contain depth
 * measurement data instead of color images. The default dataSpace is 0,
 * ADATASPACE_UNKNOWN, unless it has been overridden by the producer.
 *
 * \param dataSpace data space of all buffers queued after this call.
 * \return 0 for success, -EINVAL if window is invalid or the dataspace is not
 * supported.
 */
int ANativeWindow_setBuffersDataSpace (ANativeWindow* window, int dataSpace);

/**
 * Get the dataspace of the buffers in window.
 * \return the dataspace of buffers in window, ADATASPACE_UNKNOWN is returned if
 * dataspace is unknown, or -EINVAL if window is invalid.
 */
int ANativeWindow_getBuffersDataSpace (ANativeWindow* window);

// __ANDROID_API__ >= 28

// ANDROID_NATIVE_WINDOW_H

/** @} */
