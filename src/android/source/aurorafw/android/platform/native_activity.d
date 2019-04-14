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

module aurorafw.android.platform.native_activity;

import aurorafw.jni.platform.jni;
import aurorafw.android.platform.rect;
import aurorafw.android.platform.asset_manager;
import aurorafw.android.platform.input;
import aurorafw.android.platform.native_window;

version (Android):
extern (C):
@system:
nothrow:
@nogc:

/// TODO: add android Documentation

enum
{
	ANATIVEACTIVITY_SHOW_SOFT_INPUT_IMPLICIT = 1,
	ANATIVEACTIVITY_SHOW_SOFT_INPUT_FORCED = 2
}

enum
{
	ANATIVEACTIVITY_HIDE_SOFT_INPUT_IMPLICIT_ONLY = 1,
	ANATIVEACTIVITY_HIDE_SOFT_INPUT_NOT_ALWAYS = 2
}

struct ANativeActivity
{
	ANativeActivityCallbacks* callbacks;
	JavaVM* vm;
	JNIEnv* env;
	jobject clazz;
	const(char)* internalDataPath;
	const(char)* externalDataPath;
	int sdkVersion;
	void* instance;
	AAssetManager* assetManager;
}

struct ANativeActivityCallbacks
{
	void function(ANativeActivity*) onStart;
	void function(ANativeActivity*) onResume;
	void* function(ANativeActivity*, size_t*) onSaveInstanceState;
	void function(ANativeActivity*) onPause;
	void function(ANativeActivity*) onStop;
	void function(ANativeActivity*) onDestroy;
	void function(ANativeActivity*, int) onWindowFocusChanged;
	void function(ANativeActivity*, ANativeWindow*) onNativeWindowCreated;
	void function(ANativeActivity*, ANativeWindow*) onNativeWindowResized;
	void function(ANativeActivity*, ANativeWindow*) onNativeWindowRedrawNeeded;
	void function(ANativeActivity*, ANativeWindow*) onNativeWindowDestroyed;
	void function(ANativeActivity*, AInputQueue*) onInputQueueCreated;
	void function(ANativeActivity*, AInputQueue*) onInputQueueDestroyed;
	void function(ANativeActivity*, const(ARect)*) onContentRectChanged;
	void function(ANativeActivity*) onConfigurationChanged;
	void function(ANativeActivity*) onLowMemory;
}

void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize);
void ANativeActivity_finish(ANativeActivity* activity);
void ANativeActivity_setWindowFormat(ANativeActivity* activity, int format);
void ANativeActivity_setWindowFlags(ANativeActivity* activity, uint addFlags, uint removeFlags);
void ANativeActivity_showSoftInput(ANativeActivity* activity, uint flags);
void ANativeActivity_hideSoftInput(ANativeActivity* activity, uint flags);
