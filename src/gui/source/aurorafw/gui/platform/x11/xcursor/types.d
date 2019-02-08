/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2002 Keith Packard.
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
http://www.gnu.org/licenses/gpl-3.0.html.

NOTE: All products, services or anything associated to trademarks and
service marks used or referenced on this file are the property of their
respective companies/owners or its subsidiaries. Other names and brands
may be claimed as the property of others.

For more info about intellectual property visit: aurorafoss.org or
directly send an email to: contact (at) aurorafoss.org .

This file is part of X11 Xcursor implementation from X.Org Foundation.
*/

module aurorafw.gui.platform.x11.xcursor.types;

import aurorafw.gui.platform.x11.x;
import aurorafw.gui.platform.x11.xlib;

///
alias XcursorBool = int;
///
alias XcursorUInt = uint;

///
alias XcursorDim = XcursorUInt;
///
alias XcursorPixel = XcursorUInt;

///
enum XcursorTrue = 1;
///
enum XcursorFalse = 0;

/**
 * Cursor files start with a header.  The header
 * contains a magic number, a version number and a
 * table of contents which has type and offset information
 * for the remaining tables in the file.
 *
 * File minor versions increment for compatible changes
 * File major versions increment for incompatible changes (never, we hope)
 *
 * Chunks of the same type are always upward compatible.  Incompatible
 * changes are made with new chunk types; the old data can remain under
 * the old type.  Upward compatible changes can add header data as the
 * header lengths are specified in the file.
 *
 *  File:
 *	FileHeader
 *	LISTofChunk
 *
 *  FileHeader:
 *	CARD32		magic	    magic number
 *	CARD32		header	    bytes in file header
 *	CARD32		version	    file version
 *	CARD32		ntoc	    number of toc entries
 *	LISTofFileToc   toc	    table of contents
 *
 *  FileToc:
 *	CARD32		type	    entry type
 *	CARD32		subtype	    entry subtype (size for images)
 *	CARD32		position    absolute file position
 */

/// "Xcur" LSBFirst
enum XCURSOR_MAGIC = 0x72756358;

///
struct XcursorFileToc {
	/// chunk type
	XcursorUInt type;
	/// subtype (size for images)
	XcursorUInt subtype;
	/// absolute position in file
	XcursorUInt position;
}

///
struct XcursorFileHeader {
	/// magic number
	XcursorUInt magic;
	/// byte length of header
	XcursorUInt header;
	/// file version number
	XcursorUInt version_;
	/// number of toc entries
	XcursorUInt ntoc;
	/// table of contents
	XcursorFileToc* tocs;
}

/**
 * The rest of the file is a list of chunks, each tagged by type
 * and version.
 *
 *  Chunk:
 *	ChunkHeader
 *	<extra type-specific header fields>
 *	<type-specific data>
 *
 *  ChunkHeader:
 *	CARD32	    header	bytes in chunk header + type header
 *	CARD32	    type	chunk type
 *	CARD32	    subtype	chunk subtype
 *	CARD32	    version	chunk type version
 */

enum XCURSOR_CHUNK_HEADER_LEN = 4 * 4;

/// XcursorChunkHeader
struct _XcursorChunkHeader {
	/// bytes in chunk header
	XcursorUInt header;
	/// chunk type
	XcursorUInt type;
	/// chunk subtype (size for images)
	XcursorUInt subtype;
	/// version of this type
	XcursorUInt version_;
}

/*
 * Here's a list of the known chunk types
 */

/**
 * Comments consist of a 4-byte length field followed by
 * UTF-8 encoded text
 *
 *  Comment:
 *	ChunkHeader header	chunk header
 *	CARD32	    length	bytes in text
 *	LISTofCARD8 text	UTF-8 encoded text
 */
enum {
	///
	XCURSOR_COMMENT_TYPE = 0xfffe0001,
	///
	XCURSOR_COMMENT_VERSION = 1,
	///
	XCURSOR_COMMENT_HEADER_LEN = XCURSOR_CHUNK_HEADER_LEN + (1 *4),
	///
	XCURSOR_COMMENT_COPYRIGHT = 1,
	///
	XCURSOR_COMMENT_LICENSE = 2,
	///
	XCURSOR_COMMENT_OTHER = 3,
	///
	XCURSOR_COMMENT_MAX_LEN = 0x100000
}

///
struct XcursorComment {
	///
	XcursorUInt version_;
	///
	XcursorUInt comment_type;
	///
	char* comment;
}

/**
 * Each cursor image occupies a separate image chunk.
 * The length of the image header follows the chunk header
 * so that future versions can extend the header without
 * breaking older applications
 *
 *  Image:
 *	ChunkHeader	header	chunk header
 *	CARD32		width	actual width
 *	CARD32		height	actual height
 *	CARD32		xhot	hot spot x
 *	CARD32		yhot	hot spot y
 *	CARD32		delay	animation delay
 *	LISTofCARD32	pixels	ARGB pixels
 */
enum {
	///
	XCURSOR_IMAGE_TYPE = 0xfffd0002,
	///
	XCURSOR_IMAGE_VERSION = 1,
	///
	XCURSOR_IMAGE_HEADER_LEN = XCURSOR_CHUNK_HEADER_LEN + (5*4),
	/// 32767x32767 max cursor size
	XCURSOR_IMAGE_MAX_SIZE = 0x7fff
}

///
struct XcursorImage {
	/// version of the image data
	XcursorUInt version_;
	/// nominal size for matching
	XcursorDim size;
	/// actual width
	XcursorDim width;
	/// actual height
	XcursorDim height;
	/// hot spot x (must be inside image)
	XcursorDim xhot;
	/// hot spot y (must be inside image)
	XcursorDim yhot;
	/// animation delay to next frame (ms)
	XcursorUInt delay;
	/// pointer to pixels
	XcursorPixel* pixels;
}

/**
 * Other data structures exposed by the library API
 */
struct XcursorImages {
	/// number of images
	int nimage;
	/// array of XcursorImage pointers
	XcursorImage** images;
	/// name used to load images
	char* name;
}

/// Display holding cursors
struct XcursorCursors {
	///
	Display* dpy;
	/// reference count
	int ref_;
	/// number of cursors
	int ncursor;
	/// array of cursors
	Cursor* cursors;
}

///
struct XcursorAnimate {
	/// list of cursors to use
	XcursorCursors* cursors;
	/// which cursor is next
	int sequence;
}

///
struct XcursorFile {
	///
	void* closure;
	extern(C) int function(XcursorFile* file, ubyte* buf, int len) read;
	///
	extern(C) int function(XcursorFile* file, ubyte* buf, int len) write;
	///
	extern(C) int function(XcursorFile* file, long offset, int whence) seek;
}

///
struct XcursorComments {
	/// number of comments
	int ncomment;
	/// array of XcursorComment pointers
	XcursorComment** comments;
}

///
enum XCURSOR_CORE_THEME = "core";
///
enum XCURSOR_BITMAP_HASH_SIZE = 16;

// function types
package extern(C) @nogc nothrow {
	alias da_XcursorImageCreate = XcursorImage* function(int width, int height);
	alias da_XcursorImageDestroy = void function(XcursorImage* image);
	alias da_XcursorImagesCreate = XcursorImages* function(int size);
	alias da_XcursorImagesDestroy = void function(XcursorImages* images);
	alias da_XcursorImageLoadCursor = Cursor function(Display* dpy, const XcursorImage* image);
}