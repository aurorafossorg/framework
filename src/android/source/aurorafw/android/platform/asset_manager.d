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

module aurorafw.android.platform.asset_manager;

import core.sys.posix.sys.types;

version (Android):
extern (C):
@system:
nothrow:
@nogc:

/**
 * @addtogroup Android Asset Manager
 * @{
 */

/** Android Asset Manager
 * @file aurorafw/android/platform/asset_manager.d
 * @brief This file contains interfacing with android ndk
 * android/asset_manager.h .
 *
 * @authors Luís Ferreira <luis@aurorafoss.org>
 * @authors Dan Albert <danalbert@google.com>
 * @authors Johan Euphrosine <proppy@google.com>
 * @authors Mathias Agopian <mathias@google.com>
 */

/**
 * {@link AAssetManager} provides access to an application's raw assets by
 * creating {@link AAsset} objects.
 *
 * AAssetManager is a wrapper to the low-level native implementation
 * of the java {@link AAssetManager}, a pointer can be obtained using
 * AAssetManager_fromJava().
 *
 * The asset hierarchy may be examined like a filesystem, using
 * {@link AAssetDir} objects to peruse a single directory.
 *
 * A native {@link AAssetManager} pointer may be shared across multiple threads.
 */
struct AAssetManager;

/**
 * {@link AAssetDir} provides access to a chunk of the asset hierarchy as if
 * it were a single directory. The contents are populated by the
 * {@link AAssetManager}.
 *
 * The list of files will be sorted in ascending order by ASCII value.
 */
struct AAssetDir;

/**
 * {@link AAsset} provides access to a read-only asset.
 *
 * {@link AAsset} objects are NOT thread-safe, and should not be shared across
 * threads.
 */
struct AAsset;

/** Available access modes for opening assets with {@link AAssetManager_open} */
enum
{
	AASSET_MODE_UNKNOWN,	/** No specific information about how data will be accessed. **/
	AASSET_MODE_RANDOM,		/** Read chunks, and seek forward and backward. */
	AASSET_MODE_STREAMING,	/** Read sequentially, with an occasional forward seek. */
	AASSET_MODE_BUFFER		/** Caller plans to ask for a read-only buffer with all data. */
}


/**
 * Open the named directory within the asset hierarchy.  The directory can then
 * be inspected with the AAssetDir functions.  To open the top-level directory,
 * pass in "" as the dirName.
 *
 * The object returned here should be freed by calling AAssetDir_close().
 */
AAssetDir* AAssetManager_openDir(AAssetManager* mgr, const(char)* dirName);

/**
 * Open an asset.
 *
 * The object returned here should be freed by calling AAsset_close().
 */
AAsset* AAssetManager_open(AAssetManager* mgr, const(char)* filename, int mode);

/**
 * Iterate over the files in an asset directory.  A NULL string is returned
 * when all the file names have been returned.
 *
 * The returned file name is suitable for passing to AAssetManager_open().
 *
 * The string returned here is owned by the AssetDir implementation and is not
 * guaranteed to remain valid if any other calls are made on this AAssetDir
 * instance.
 */
const(char)* AAssetDir_getNextFileName(AAssetDir* assetDir);

/**
 * Reset the iteration state of AAssetDir_getNextFileName() to the beginning.
 */
void AAssetDir_rewind(AAssetDir* assetDir);

/**
 * Close an opened AAssetDir, freeing any related resources.
 */
void AAssetDir_close(AAssetDir* assetDir);

/**
 * Attempt to read 'count' bytes of data from the current offset.
 *
 * Returns the number of bytes read, zero on EOF, or < 0 on error.
 */
int AAsset_read(AAsset* asset, void* buf, size_t count);

/**
 * Seek to the specified offset within the asset data.  'whence' uses the
 * same constants as lseek()/fseek().
 *
 * Returns the new position on success, or (off_t) -1 on error.
 */
off_t AAsset_seek(AAsset* asset, off_t offset, int whence);

/**
 * Seek to the specified offset within the asset data.  'whence' uses the
 * same constants as lseek()/fseek().
 *
 * Uses 64-bit data type for large files as opposed to the 32-bit type used
 * by AAsset_seek.
 *
 * Returns the new position on success, or (off64_t) -1 on error.
 */
off64_t AAsset_seek64(AAsset* asset, off64_t offset, int whence);

/**
 * Close the asset, freeing all associated resources.
 */
void AAsset_close(AAsset* asset);

/**
 * Get a pointer to a buffer holding the entire contents of the assset.
 *
 * Returns NULL on failure.
 */
const(void)* AAsset_getBuffer(AAsset* asset);

/**
 * Report the total size of the asset data.
 */
off_t AAsset_getLength(AAsset* asset);

/**
 * Report the total size of the asset data. Reports the size using a 64-bit
 * number insted of 32-bit as AAsset_getLength.
 */
off64_t AAsset_getLength64(AAsset* asset);

/**
 * Report the total amount of asset data that can be read from the current position.
 */
off_t AAsset_getRemainingLength(AAsset* asset);

/**
 * Report the total amount of asset data that can be read from the current position.
 *
 * Uses a 64-bit number instead of a 32-bit number as AAsset_getRemainingLength does.
 */
off64_t AAsset_getRemainingLength64(AAsset* asset);

/**
 * Open a new file descriptor that can be used to read the asset data. If the
 * start or length cannot be represented by a 32-bit number, it will be
 * truncated. If the file is large, use AAsset_openFileDescriptor64 instead.
 *
 * Returns < 0 if direct fd access is not possible (for example, if the asset is
 * compressed).
 */
int AAsset_openFileDescriptor(AAsset* asset, off_t* outStart, off_t* outLength);

/**
 * Open a new file descriptor that can be used to read the asset data.
 *
 * Uses a 64-bit number for the offset and length instead of 32-bit instead of
 * as AAsset_openFileDescriptor does.
 *
 * Returns < 0 if direct fd access is not possible (for example, if the asset is
 * compressed).
 */
int AAsset_openFileDescriptor64(AAsset* asset, off64_t* outStart, off64_t* outLength);

/**
 * Returns whether this asset's internal buffer is allocated in ordinary RAM (i.e. not
 * mmapped).
 */
int AAsset_isAllocated(AAsset* asset);

/** @} */