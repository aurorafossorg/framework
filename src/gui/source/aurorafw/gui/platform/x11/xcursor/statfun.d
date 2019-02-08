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

module aurorafw.gui.platform.x11.xcursor.statfun;

import aurorafw.gui.platform.x11.x;
import aurorafw.gui.platform.x11.xlib;

public import aurorafw.gui.platform.x11.xcursor.types;

extern(C) @nogc nothrow {
	/**
	* Manage Image objects
	*/
	XcursorImage* XcursorImageCreate(int width, int height);
	///
	void XcursorImageDestroy(XcursorImage* image);

	/**
	* Manage Images objects
	*/
	XcursorImages* XcursorImagesCreate(int size);
	///
	void XcursorImagesDestroy(XcursorImages* images);
	///
	void XcursorImagesSetName(XcursorImages* images, const char* name);

	/**
	* Manage Cursor objects
	*/
	XcursorCursors* XcursorCursorsCreate(Display* dpy, int size);
	///
	void XcursorCursorsDestroy(XcursorCursors* cursors);

	/**
	* Manage Animate objects
	*/
	XcursorAnimate* XcursorAnimateCreate(XcursorCursors* cursors);
	///
	void XcursorAnimateDestroy(XcursorAnimate* animate);
	///
	Cursor XcursorAnimateNext(XcursorAnimate* animate);

	//TODO: Change to C-like function style.

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