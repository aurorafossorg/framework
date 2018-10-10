/**
 * Copyright © 2002 Keith Packard
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Keith Packard not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  Keith Packard makes no
 * representations about the suitability of this software for any purpose.  It
 * is provided "as is" without express or implied warranty.
 *
 * KEITH PACKARD DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL KEITH PACKARD BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
module aurorafw.gui.platform.x11.xcursor.xcursor;

import aurorafw.gui.platform.x11.x;
import aurorafw.gui.platform.x11.xlib;
import core.stdc.stdio;

version(AuroraFW_Static_X11_XCursor)
{
	extern(C) {
		/**
		* Manage Image objects
		*/
		XcursorImage* function(int width, int height) XcursorImageCreate;
		///
		void function(XcursorImage* image) XcursorImageDestroy;

		/**
		* Manage Images objects
		*/
		XcursorImages* function(int size) XcursorImagesCreate;
		///
		void function(XcursorImages* images) XcursorImagesDestroy;
		///
		void function(XcursorImages* images, const char* name) XcursorImagesSetName;

		/**
		* Manage Cursor objects
		*/
		XcursorCursors* function(Display* dpy, int size) XcursorCursorsCreate;
		///
		void function(XcursorCursors* cursors) XcursorCursorsDestroy;

		/**
		* Manage Animate objects
		*/
		XcursorAnimate* function(XcursorCursors* cursors) XcursorAnimateCreate;
		///
		void function(XcursorAnimate* animate) XcursorAnimateDestroy;
		///
		Cursor function(XcursorAnimate* animate) XcursorAnimateNext;

		/**
		* Manage Comment objects
		*/
		XcursorComment* function(XcursorUInt comment_type, int length) XcursorCommentCreate;
		///
		void function(XcursorComment* comment) XcursorCommentDestroy;
		///
		XcursorComments* function(int size) XcursorCommentsCreate;
		///
		void function(XcursorComments* comments) XcursorCommentsDestroy;

		/**
		* XcursorFile/Image APIs
		*/
		XcursorImage* function(XcursorFile* file, int size) XcursorXcFileLoadImage;
		///
		XcursorImages* function(XcursorFile* file, int size) XcursorXcFileLoadImages;
		///
		XcursorImages* function(XcursorFile* file) XcursorXcFileLoadAllImages;
		///
		XcursorBool function(XcursorFile* file, XcursorComments** commentsp, XcursorImages** imagesp) XcursorXcFileLoad;
		///
		XcursorBool function(XcursorFile* file, const XcursorComments* comments, const XcursorImages* images) XcursorXcFileSave;

		/**
		* FILE/Image APIs
		*/
		XcursorImage* function(FILE* file, int size) XcursorFileLoadImage;
		///
		XcursorImages* function(FILE* file, int size) XcursorFileLoadImages;
		///
		XcursorImages* function(FILE* file) XcursorFileLoadAllImages;
		///
		XcursorBool function(FILE* file, XcursorComments** commentsp, XcursorImages** imagesp) XcursorFileLoad;
		///
		XcursorBool function(FILE* file, const XcursorImages* images) XcursorFileSaveImages;
		///
		XcursorBool function(FILE* file, const XcursorComments* comments, const XcursorImages* images) XcursorFileSave;

		/**
		* Filename/Image APIs
		*/
		XcursorImage* function(const char* filename, int size) XcursorFilenameLoadImage;
		///
		XcursorImages* function(const char* filename, int size) XcursorFilenameLoadImages;
		///
		XcursorImages* function(const char* filename) XcursorFilenameLoadAllImages;
		///
		XcursorBool function(const char* file, XcursorComments** commentsp, XcursorImages** imagesp) XcursorFilenameLoad;
		///
		XcursorBool function(const char* filename, const XcursorImages* images) XcursorFilenameSaveImages;
		///
		XcursorBool function(const char* file, const XcursorComments* comments, const XcursorImages* images) XcursorFilenameSave;

		/**
		* Library/Image APIs
		*/
		XcursorImage* function(const char* library, const char* theme, int size) XcursorLibraryLoadImage;
		///
		XcursorImages* function(const char* library, const char* theme, int size) XcursorLibraryLoadImages;

		/**
		* Library/shape API
		*/
		const char* function() XcursorLibraryPath;
		///
		int function(const char* library) XcursorLibraryShape;

		/**
		* Image/Cursor APIs
		*/
		Cursor function(Display* dpy, const XcursorImage* image) XcursorImageLoadCursor;
		///
		XcursorCursors* function(Display* dpy, const XcursorImages* images) XcursorImagesLoadCursors;
		///
		Cursor function(Display* dpy, const XcursorImages* images) XcursorImagesLoadCursor;

		/**
		* Filename/Cursor APIs
		*/
		Cursor function(Display* dpy, const char* file) XcursorFilenameLoadCursor;
		///
		XcursorCursors* function(Display* dpy, const char* file) XcursorFilenameLoadCursors;

		/**
		* Library/Cursor APIs
		*/
		Cursor function(Display* dpy, const char* file) XcursorLibraryLoadCursor;
		///
		XcursorCursors* function(Display* dpy, const char* file) XcursorLibraryLoadCursors;

		/**
		* Shape/Image APIs
		*/
		XcursorImage* function(uint shape, const char* theme, int size) XcursorShapeLoadImage;
		///
		XcursorImages* function(uint shape, const char* theme, int size) XcursorShapeLoadImages;

		/**
		* Shape/Cursor APIs
		*/
		Cursor function(Display* dpy, uint shape) XcursorShapeLoadCursor;
		///
		XcursorCursors* function(Display* dpy, uint shape) XcursorShapeLoadCursors;

		/**
		* This is the function called by Xlib when attempting to
		* load cursors from XCreateGlyphCursor.  The interface must
		* not change as Xlib loads 'libXcursor.so' instead of
		* a specific major version
		*/
		Cursor function(Display* dpy, Font source_font, Font mask_font, uint source_char, uint mask_char, const XColor* foreground, const XColor* background) XcursorTryShapeCursor;
		///
		void function(Display* dpy,Pixmap pid, uint width, uint height) XcursorNoticeCreateBitmap;
		///
		void function(Display* dpy, Drawable draw, XImage* image) XcursorNoticePutBitmap;
		///
		Cursor function(Display* dpy, Pixmap source, Pixmap mask, XColor* foreground, XColor* background, uint x, uint y) XcursorTryShapeBitmapCursor;
		///
		void function(XImage* image, ubyte[XCURSOR_BITMAP_HASH_SIZE] hash) XcursorImageHash;

		/**
		* Display information APIs
		*/
		XcursorBool function(Display* dpy) XcursorSupportsARGB;
		///
		XcursorBool function(Display* dpy) XcursorSupportsAnim;
		///
		XcursorBool function(Display* dpy, int size) XcursorSetDefaultSize;
		///
		int function(Display* dpy) XcursorGetDefaultSize;
		///
		XcursorBool function(Display* dpy, const char* theme) XcursorSetTheme;
		///
		char* function(Display* dpy) XcursorGetTheme;
		///
		XcursorBool function(Display* dpy) XcursorGetThemeCore;
		///
		XcursorBool function(Display* dpy, XcursorBool theme_core) XcursorSetThemeCore;
	}
} else {
	import aurorafw.core.dylib;

	extern(C) @nogc nothrow {
		alias da_XcursorImageCreate = XcursorImage* function(int width, int height);
	}

	__gshared {
		da_XcursorImageCreate XcursorImageCreate;
	}
	class X11XCursorDylibLoader : DylibLoader {
		this()
		{
			super([""]);
		}

		override void loadSymbols()
		{
			bindFunc(cast(void**)&XcursorImageCreate,"XcursorImageCreate");
		}
	}
}


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
