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

module aurorafw.android.platform.storage_manager;

/**
 * @addtogroup Storage
 * @{
 */

/**
 * @file aurorafw/android/platform/storage_manager.d
 */

version (Android):
extern (C):
@system:
nothrow:
@nogc:

struct AStorageManager;
/**
 * {@link AStorageManager} manages application OBB storage, a pointer
 * can be obtained with AStorageManager_new().
 */

/**
 * The different states of a OBB storage passed to AStorageManager_obbCallbackFunc().
 */
enum
{
    /**
     * The OBB container is now mounted and ready for use. Can be returned
     * as the status for callbacks made during asynchronous OBB actions.
     */
    AOBB_STATE_MOUNTED = 1,

    /**
     * The OBB container is now unmounted and not usable. Can be returned
     * as the status for callbacks made during asynchronous OBB actions.
     */
    AOBB_STATE_UNMOUNTED = 2,

    /**
     * There was an internal system error encountered while trying to
     * mount the OBB. Can be returned as the status for callbacks made
     * during asynchronous OBB actions.
     */
    AOBB_STATE_ERROR_INTERNAL = 20,

    /**
     * The OBB could not be mounted by the system. Can be returned as the
     * status for callbacks made during asynchronous OBB actions.
     */
    AOBB_STATE_ERROR_COULD_NOT_MOUNT = 21,

    /**
     * The OBB could not be unmounted. This most likely indicates that a
     * file is in use on the OBB. Can be returned as the status for
     * callbacks made during asynchronous OBB actions.
     */
    AOBB_STATE_ERROR_COULD_NOT_UNMOUNT = 22,

    /**
     * A call was made to unmount the OBB when it was not mounted. Can be
     * returned as the status for callbacks made during asynchronous OBB
     * actions.
     */
    AOBB_STATE_ERROR_NOT_MOUNTED = 23,

    /**
     * The OBB has already been mounted. Can be returned as the status for
     * callbacks made during asynchronous OBB actions.
     */
    AOBB_STATE_ERROR_ALREADY_MOUNTED = 24,

    /**
     * The current application does not have permission to use this OBB.
     * This could be because the OBB indicates it's owned by a different
     * package. Can be returned as the status for callbacks made during
     * asynchronous OBB actions.
     */
    AOBB_STATE_ERROR_PERMISSION_DENIED = 25
}

/**
 * Obtains a new instance of AStorageManager.
 */
AStorageManager* AStorageManager_new ();

/**
 * Release AStorageManager instance.
 */
void AStorageManager_delete (AStorageManager* mgr);

/**
 * Callback function for asynchronous calls made on OBB files.
 *
 * "state" is one of the following constants:
 * - {@link AOBB_STATE_MOUNTED}
 * - {@link AOBB_STATE_UNMOUNTED}
 * - {@link AOBB_STATE_ERROR_INTERNAL}
 * - {@link AOBB_STATE_ERROR_COULD_NOT_MOUNT}
 * - {@link AOBB_STATE_ERROR_COULD_NOT_UNMOUNT}
 * - {@link AOBB_STATE_ERROR_NOT_MOUNTED}
 * - {@link AOBB_STATE_ERROR_ALREADY_MOUNTED}
 * - {@link AOBB_STATE_ERROR_PERMISSION_DENIED}
 */
alias AStorageManager_obbCallbackFunc = void function (const(char)* filename, const int state, void* data);

/**
 * Attempts to mount an OBB file. This is an asynchronous operation.
 */
void AStorageManager_mountObb (
    AStorageManager* mgr,
    const(char)* filename,
    const(char)* key,
    AStorageManager_obbCallbackFunc cb,
    void* data);

/**
 * Attempts to unmount an OBB file. This is an asynchronous operation.
 */
void AStorageManager_unmountObb (
    AStorageManager* mgr,
    const(char)* filename,
    const int force,
    AStorageManager_obbCallbackFunc cb,
    void* data);

/**
 * Check whether an OBB is mounted.
 */
int AStorageManager_isObbMounted (AStorageManager* mgr, const(char)* filename);

/**
 * Get the mounted path for an OBB.
 */
const(char)* AStorageManager_getMountedObbPath (AStorageManager* mgr, const(char)* filename);

// ANDROID_STORAGE_MANAGER_H

/** @} */
