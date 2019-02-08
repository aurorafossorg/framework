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

version (Android):
extern (C):
@system:
nothrow:
@nogc:

/*
 * Magic version number for a current development build, which has
 * not yet turned into an official release.
 */

enum __ANDROID_API_FUTURE__ = 10000;

enum __ANDROID_API__ = __ANDROID_API_FUTURE__;

enum __ANDROID_API_G__ = 9;
enum __ANDROID_API_I__ = 14;
enum __ANDROID_API_J__ = 16;
enum __ANDROID_API_J_MR1__ = 17;
enum __ANDROID_API_J_MR2__ = 18;
enum __ANDROID_API_K__ = 19;
enum __ANDROID_API_L__ = 21;
enum __ANDROID_API_L_MR1__ = 22;
enum __ANDROID_API_M__ = 23;
enum __ANDROID_API_N__ = 24;
enum __ANDROID_API_N_MR1__ = 25;
enum __ANDROID_API_O__ = 26;
enum __ANDROID_API_O_MR1__ = 27;
enum __ANDROID_API_P__ = 28;

