/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2008 The Android Open Source Project.
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

module aurorafw.android.platform.api_level;

/**
 * @file aurorafw/android/platform/api_level.d
 * @brief Functions and constants for dealing with multiple API levels.
 */


version (Android):
extern (C):
@system:
nothrow:
@nogc:

/**
 * Magic version number for an Android OS build which has
 * not yet turned into an official release,
 * for comparisons against __ANDROID_API__.
 */
enum __ANDROID_API_FUTURE__ = 10000;

/**
 * `__ANDROID_API__` is the API level being targeted. For the OS,
 * this is `__ANDROID_API_FUTURE__`. For the NDK, this is set by the
 * compiler/build system based on the API level you claimed to target.
 */
enum __ANDROID_API__ = __ANDROID_API_FUTURE__;

enum __ANDROID_API_G__ = 9; /** Names the Gingerbread API level (9), for comparisons against __ANDROID_API__. */
enum __ANDROID_API_I__ = 14; /** Names the Ice-Cream Sandwich API level (14), for comparisons against __ANDROID_API__. */
enum __ANDROID_API_J__ = 16; /** Names the Jellybean API level (16), for comparisons against __ANDROID_API__. */
enum __ANDROID_API_J_MR1__ = 17; /** Names the Jellybean MR1 API level (17), for comparisons against __ANDROID_API__. */
enum __ANDROID_API_J_MR2__ = 18; /** Names the Jellybean MR2 API level (18), for comparisons against __ANDROID_API__. */
enum __ANDROID_API_K__ = 19; /** Names the KitKat API level (19), for comparisons against __ANDROID_API__. */
enum __ANDROID_API_L__ = 21; /** Names the Lollipop API level (21), for comparisons against __ANDROID_API__. */
enum __ANDROID_API_L_MR1__ = 22; /** Names the Lollipop MR1 API level (22), for comparisons against __ANDROID_API__. */
enum __ANDROID_API_M__ = 23; /** Names the Marshmallow API level (23), for comparisons against __ANDROID_API__. */
enum __ANDROID_API_N__ = 24; /** Names the Nougat API level (24), for comparisons against __ANDROID_API__. */
enum __ANDROID_API_N_MR1__ = 25; /** Names the Nougat MR1 API level (25), for comparisons against __ANDROID_API__. */
enum __ANDROID_API_O__ = 26; /** Names the Oreo API level (26), for comparisons against __ANDROID_API__. */
enum __ANDROID_API_O_MR1__ = 27; /** Names the Oreo MR1 API level (27), for comparisons against __ANDROID_API__. */
enum __ANDROID_API_P__ = 28; /** Names the Pie API level (28), for comparisons against __ANDROID_API__. */
enum __ANDROID_API_Q__ = 29; /** Names the "Q" API level (29), for comparisons against __ANDROID_API__. */

/**
 * Returns the `targetSdkVersion` of the caller, or `__ANDROID_API_FUTURE__`
 * if there is no known target SDK version (for code not running in the
 * context of an app).
 *
 * The returned values correspond to the named constants in `<android/api-level.h>`,
 * and is equivalent to the AndroidManifest.xml `targetSdkVersion`.
 *
 * See also android_get_device_api_level().
 *
 * Available since API level 24.
 */
int android_get_application_target_sdk_version();

/**
 * Returns the API level of the device we're actually running on, or -1 on failure.
 * The returned values correspond to the named constants in `<android/api-level.h>`,
 * and is equivalent to the Java `Build.VERSION.SDK_INT` API.
 *
 * See also android_get_application_target_sdk_version().
 */
int android_get_device_api_level();
