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

module aurorafw.android.platform.surface_texture_jni;

/**
 * @addtogroup SurfaceTexture
 * @{
 */

/**
 * @file aurorafw/android/platform/surface_texture_jni.d
 */

version (Android):
extern (C):
@system:
nothrow:
@nogc:

/**
 * Get a reference to the native ASurfaceTexture from the corresponding java object.
 *
 * The caller must keep a reference to the Java SurfaceTexture during the lifetime of the returned
 * ASurfaceTexture. Failing to do so could result in the ASurfaceTexture to stop functioning
 * properly once the Java object gets finalized.
 * However, this will not result in program termination.
 *
 * \param env JNI environment
 * \param surfacetexture Instance of Java SurfaceTexture object
 * \return native ASurfaceTexture reference or nullptr if the java object is not a SurfaceTexture.
 *         The returned reference MUST BE released when it's no longer needed using
 *         ASurfaceTexture_release().
 */
ASurfaceTexture* ASurfaceTexture_fromSurfaceTexture (JNIEnv* env, jobject surfacetexture);

/* ANDROID_NATIVE_SURFACE_TEXTURE_JNI_H */
