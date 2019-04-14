/*
									__
									/ _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2014 The Android Open Source Project.
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

module aurorafw.android.platform.dlext;

version (Android):
extern (C):
@system:
nothrow:
@nogc:

/* for off64_t */

/**
 * @addtogroup libdl Dynamic Linker
 * @{
 */

/**
 * \file
 * Advanced dynamic library opening support. Most users will want to use
 * the standard [dlopen(3)](http://man7.org/linux/man-pages/man3/dlopen.3.html)
 * functionality in `<dlfcn.h>` instead.
 */

/** Bitfield definitions for `android_dlextinfo::flags`. */
enum
{
	/**
	 * When set, the `reserved_addr` and `reserved_size` fields must point to an
	 * already-reserved region of address space which will be used to load the
	 * library if it fits.
	 *
	 * If the reserved region is not large enough, loading will fail.
	 */
	ANDROID_DLEXT_RESERVED_ADDRESS = 1,

	/**
	 * Like `ANDROID_DLEXT_RESERVED_ADDRESS`, but if the reserved region is not large enough,
	 * the linker will choose an available address instead.
	 */
	ANDROID_DLEXT_RESERVED_ADDRESS_HINT = 2,

	/**
	 * When set, write the GNU RELRO section of the mapped library to `relro_fd`
	 * after relocation has been performed, to allow it to be reused by another
	 * process loading the same library at the same address. This implies
	 * `ANDROID_DLEXT_USE_RELRO`.
	 *
	 * This is mainly useful for the system WebView implementation.
	 */
	ANDROID_DLEXT_WRITE_RELRO = 4,

	/**
	 * When set, compare the GNU RELRO section of the mapped library to `relro_fd`
	 * after relocation has been performed, and replace any relocated pages that
	 * are identical with a version mapped from the file.
	 *
	 * This is mainly useful for the system WebView implementation.
	 */
	ANDROID_DLEXT_USE_RELRO = 8,

	/**
	 * Use `library_fd` instead of opening the file by name.
	 * The filename parameter is still used to identify the library.
	 */
	ANDROID_DLEXT_USE_LIBRARY_FD = 16,

	/**
	 * If opening a library using `library_fd` read it starting at `library_fd_offset`.
	 * This is mainly useful for loading a library stored within another file (such as uncompressed
	 * inside a ZIP archive).
	 * This flag is only valid when `ANDROID_DLEXT_USE_LIBRARY_FD` is set.
	 */
	ANDROID_DLEXT_USE_LIBRARY_FD_OFFSET = 32,

	/**
	 * When set, do not use `stat(2)` to check if the library has already been loaded.
	 *
	 * This flag allows forced loading of the library in the case when for some
	 * reason multiple ELF files share the same filename (because the already-loaded
	 * library has been removed and overwritten, for example).
	 *
	 * Note that if the library has the same `DT_SONAME` as an old one and some other
	 * library has the soname in its `DT_NEEDED` list, the first one will be used to resolve any
	 * dependencies.
	 */
	ANDROID_DLEXT_FORCE_LOAD = 64,

	/**
	 * When set, if the minimum `p_vaddr` of the ELF file's `PT_LOAD` segments is non-zero,
	 * the dynamic linker will load it at that address.
	 *
	 * This flag is for ART internal use only.
	 */
	ANDROID_DLEXT_FORCE_FIXED_VADDR = 128,

	/**
	 * Instructs dlopen to load the library at the address specified by reserved_addr.
	 *
	 * The difference between `ANDROID_DLEXT_LOAD_AT_FIXED_ADDRESS` and
	 * `ANDROID_DLEXT_RESERVED_ADDRESS` is that for `ANDROID_DLEXT_LOAD_AT_FIXED_ADDRESS` the linker
	 * reserves memory at `reserved_addr` whereas for `ANDROID_DLEXT_RESERVED_ADDRESS` the linker
	 * relies on the caller to reserve the memory.
	 *
	 * This flag can be used with `ANDROID_DLEXT_FORCE_FIXED_VADDR`. When
	 * `ANDROID_DLEXT_FORCE_FIXED_VADDR` is set and `load_bias` is not 0 (`load_bias` is the
	 * minimum `p_vaddr` of all `PT_LOAD` segments) this flag is ignored because the linker has to
	 * pick one address over the other and this way is more convenient for ART.
	 * Note that `ANDROID_DLEXT_FORCE_FIXED_VADDR` does not generate an error when the minimum
	 * `p_vaddr` is 0.
	 *
	 * Cannot be used with `ANDROID_DLEXT_RESERVED_ADDRESS` or `ANDROID_DLEXT_RESERVED_ADDRESS_HINT`.
	 *
	 * This flag is for ART internal use only.
	 */
	ANDROID_DLEXT_LOAD_AT_FIXED_ADDRESS = 256,

	/**
	 * This flag used to load library in a different namespace. The namespace is
	 * specified in `library_namespace`.
	 *
	 * This flag is for internal use only (since there is no NDK API for namespaces).
	 */
	ANDROID_DLEXT_USE_NAMESPACE = 512,

	/** Mask of valid bits. */
	ANDROID_DLEXT_VALID_FLAG_BITS = 1023
}

struct android_namespace_t;

/** Used to pass Android-specific arguments to `android_dlopen_ext`. */
struct android_dlextinfo
{
	/** A bitmask of `ANDROID_DLEXT_` enum values. */
	ulong flags;

	/** Used by `ANDROID_DLEXT_RESERVED_ADDRESS` and `ANDROID_DLEXT_RESERVED_ADDRESS_HINT`. */
	void* reserved_addr;
	/** Used by `ANDROID_DLEXT_RESERVED_ADDRESS` and `ANDROID_DLEXT_RESERVED_ADDRESS_HINT`. */
	size_t reserved_size;

	/** Used by `ANDROID_DLEXT_WRITE_RELRO` and `ANDROID_DLEXT_USE_RELRO`. */
	int relro_fd;

	/** Used by `ANDROID_DLEXT_USE_LIBRARY_FD`. */
	int library_fd;
	/** Used by `ANDROID_DLEXT_USE_LIBRARY_FD_OFFSET` */
	off64_t library_fd_offset;

	/** Used by `ANDROID_DLEXT_USE_NAMESPACE`. */
	android_namespace_t* library_namespace;
}

/**
 * Opens the given library. The `__filename` and `__flags` arguments are
 * the same as for [dlopen(3)](http://man7.org/linux/man-pages/man3/dlopen.3.html),
 * with the Android-specific flags supplied via the `flags` member of `__info`.
 */

void* android_dlopen_ext (
	const(char)* __filename,
	int __flags,
	const(android_dlextinfo)* __info);
/* __ANDROID_API__ >= 21 */

/** @} */
