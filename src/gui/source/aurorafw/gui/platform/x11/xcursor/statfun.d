module aurorafw.gui.platform.x11.xcursor.statfun;

import aurorafw.gui.platform.x11.x;
import aurorafw.gui.platform.x11.xlib;
import core.stdc.stdio;

public import aurorafw.gui.platform.x11.xcursor.types;

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