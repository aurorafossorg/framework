/*
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2010 The Android Open Source Project.
Copyright (C) 2018 Aurora Free Open Source Software.

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
http://www.gnu.org/licenses/gpl-3.0.html.

NOTE: All products, services or anything associated to trademarks and
service marks used or referenced on this file are the property of their
respective companies/owners or its subsidiaries. Other names and brands
may be claimed as the property of others.

For more info about intellectual property visit: aurorafoss.org or
directly send an email to: contact (at) aurorafoss.org .

This file is part of Android Open Source Project implementation.
*/

module aurorafw.android.platform.asset_manager_jni;

import aurorafw.android.platform.asset_manager;
import aurorafw.jni.platform.jni;

version (Android):
extern (C):
@system:
nothrow:
@nogc:

/**
 * @addtogroup Android Asset Manager
 * @{
 */

/** Android Asset Manager for JNI
 * @file aurorafw/android/platform/asset_manager.d
 * @brief This file contains interfacing with android ndk
 * android/asset_manager_jni.h .
 *
 * @authors Luís Ferreira <luis@aurorafoss.org>
 * @authors Johan Euphrosine <proppy@google.com>
 * @authors Mathias Agopian <mathias@google.com>
 */

/**
 * Given a Dalvik AssetManager object, obtain the corresponding native AAssetManager
 * object.  Note that the caller is responsible for obtaining and holding a VM reference
 * to the jobject to prevent its being garbage collected while the native object is
 * in use.
 */
AAssetManager* AAssetManager_fromJava(JNIEnv* env, jobject assetManager);

/**}*/