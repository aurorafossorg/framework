/*
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2018 Aurora Free Open Source Software.

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
*/

module aurorafw.gui.api.x11.x;

alias int Bool;
alias int Status;
alias uint VisualID;
alias byte* XPointer;

alias void Display;
alias uint XID;
alias XID Window;
alias XID Drawable;
alias XID Font;
alias XID Pixmap;
alias XID Cursor;
alias XID Colormap;
alias XID GContext;
alias XID KeySym;

struct XExtData {
	int number;
	XExtData* next;
	extern( C ) int function( XExtData* ) free_private;
	XPointer private_data;
}

struct Visual {
	XExtData* ext_data;
	VisualID visualid;
	int _class;
	uint red_mask, green_mask, blue_mask;
	int bits_per_rgb;
	int map_entries;
}

struct XVisualInfo {
	Visual *visual;
	VisualID visualid;
	int screen;
	int depth;
	int _class;
	uint red_mask;
	uint green_mask;
	uint blue_mask;
	int colormap_size;
	int bits_per_rgb;
}

alias uint Mask;
alias uint Atom;
alias uint Time;
alias ubyte KeyCode;

/*****************************************************************
 * RESERVED RESOURCE AND CONSTANT DEFINITIONS
 *****************************************************************/

enum None               = 0;        /* universal null resource or null atom */

enum ParentRelative     = 1L;	/* background pixmap in CreateWindow
				    and ChangeWindowAttributes */

enum CopyFromParent     = 0L;	/* border pixmap in CreateWindow
				       and ChangeWindowAttributes
				   special VisualID and special window
				       class passed to CreateWindow */

enum PointerWindow      = 0L;	/* destination window in SendEvent */
enum InputFocus         = 1L;	/* destination window in SendEvent */

enum PointerRoot        = 1L;	/* focus window in SetInputFocus */

enum AnyPropertyType    = 0L;	/* special Atom, passed to GetProperty */

enum AnyKey             = 0L;	/* special Key Code, passed to GrabKey */

enum AnyButton          = 0L;	/* special Button Code, passed to GrabButton */

enum AllTemporary       = 0L;	/* special Resource ID passed to KillClient */

enum CurrentTime        = 0L;	/* special Time */

enum NoSymbol           = 0L;	/* special KeySym */

/*****************************************************************
 * EVENT DEFINITIONS
 *****************************************************************/

/* Input Event Masks. Used as event-mask window attribute and as arguments
   to Grab requests.  Not to be confused with event names.  */

enum NoEventMask                = 0L;
enum KeyPressMask               = (1L<<0);
enum KeyReleaseMask             = (1L<<1);
enum ButtonPressMask            = (1L<<2);
enum ButtonReleaseMask          = (1L<<3);
enum EnterWindowMask            = (1L<<4);
enum LeaveWindowMask            = (1L<<5);
enum PointerMotionMask          = (1L<<6);
enum PointerMotionHintMask      = (1L<<7);
enum Button1MotionMask          = (1L<<8);
enum Button2MotionMask          = (1L<<9);
enum Button3MotionMask          = (1L<<10);
enum Button4MotionMask          = (1L<<11);
enum Button5MotionMask          = (1L<<12);
enum ButtonMotionMask           = (1L<<13);
enum KeymapStateMask            = (1L<<14);
enum ExposureMask               = (1L<<15);
enum VisibilityChangeMask       = (1L<<16);
enum StructureNotifyMask        = (1L<<17);
enum ResizeRedirectMask         = (1L<<18);
enum SubstructureNotifyMask     = (1L<<19);
enum SubstructureRedirectMask   = (1L<<20);
enum FocusChangeMask            = (1L<<21);
enum PropertyChangeMask         = (1L<<22);
enum ColormapChangeMask         = (1L<<23);
enum OwnerGrabButtonMask        = (1L<<24);

/* Event names.  Used in "type" field in XEvent structures.  Not to be
confused with event masks above.  They start from 2 because 0 and 1
are reserved in the protocol for errors and replies. */

enum KeyPress           = 2;
enum KeyRelease         = 3;
enum ButtonPress        = 4;
enum ButtonRelease      = 5;
enum MotionNotify       = 6;
enum EnterNotify        = 7;
enum LeaveNotify        = 8;
enum FocusIn            = 9;
enum FocusOut           = 10;
enum KeymapNotify       = 11;
enum Expose             = 12;
enum GraphicsExpose     = 13;
enum NoExpose           = 14;
enum VisibilityNotify   = 15;
enum CreateNotify       = 16;
enum DestroyNotify      = 17;
enum UnmapNotify        = 18;
enum MapNotify          = 19;
enum MapRequest         = 20;
enum ReparentNotify     = 21;
enum ConfigureNotify    = 22;
enum ConfigureRequest   = 23;
enum GravityNotify      = 24;
enum ResizeRequest      = 25;
enum CirculateNotify    = 26;
enum CirculateRequest   = 27;
enum PropertyNotify     = 28;
enum SelectionClear     = 29;
enum SelectionRequest   = 30;
enum SelectionNotify    = 31;
enum ColormapNotify     = 32;
enum ClientMessage      = 33;
enum MappingNotify      = 34;
enum GenericEvent       = 35;
enum LASTEvent          = 36;	/* must be bigger than any event # */


/* Key masks. Used as modifiers to GrabButton and GrabKey, results of QueryPointer,
   state in various key-, mouse-, and button-related events. */

enum ShiftMask          = (1<<0);
enum LockMask           = (1<<1);
enum ControlMask        = (1<<2);
enum Mod1Mask           = (1<<3);
enum Mod2Mask           = (1<<4);
enum Mod3Mask           = (1<<5);
enum Mod4Mask           = (1<<6);
enum Mod5Mask           = (1<<7);

/* modifier names.  Used to build a SetModifierMapping request or
   to read a GetModifierMapping request.  These correspond to the
   masks defined above. */
enum ShiftMapIndex          = 0;
enum LockMapIndex           = 1;
enum ControlMapIndex        = 2;
enum Mod1MapIndex           = 3;
enum Mod2MapIndex           = 4;
enum Mod3MapIndex           = 5;
enum Mod4MapIndex           = 6;
enum Mod5MapIndex           = 7;


/* button masks.  Used in same manner as Key masks above. Not to be confused
   with button names below. */

enum Button1Mask    = (1<<8);
enum Button2Mask    = (1<<9);
enum Button3Mask    = (1<<10);
enum Button4Mask    = (1<<11);
enum Button5Mask    = (1<<12);

enum AnyModifier    = (1<<15);  /* used in GrabButton, GrabKey */


/* button names. Used as arguments to GrabButton and as detail in ButtonPress
   and ButtonRelease events.  Not to be confused with button masks above.
   Note that 0 is already defined above as "AnyButton".  */

enum Button1            = 1;
enum Button2            = 2;
enum Button3            = 3;
enum Button4            = 4;
enum Button5            = 5;

/* Notify modes */

enum NotifyNormal       = 0;
enum NotifyGrab         = 1;
enum NotifyUngrab       = 2;
enum NotifyWhileGrabbed = 3;

enum NotifyHint         = 1;	/* for MotionNotify events */

/* Notify detail */

enum NotifyAncestor         = 0;
enum NotifyVirtual          = 1;
enum NotifyInferior         = 2;
enum NotifyNonlinear        = 3;
enum NotifyNonlinearVirtual = 4;
enum NotifyPointer          = 5;
enum NotifyPointerRoot      = 6;
enum NotifyDetailNone       = 7;

/* Visibility notify */

enum VisibilityUnobscured           = 0;
enum VisibilityPartiallyObscured    = 1;
enum VisibilityFullyObscured        = 2;

/* Circulation request */

enum PlaceOnTop         = 0;
enum PlaceOnBottom      = 1;

/* protocol families */

enum FamilyInternet         = 0;	/* IPv4 */
enum FamilyDECnet           = 1;
enum FamilyChaos            = 2;
enum FamilyInternet6        = 6;	/* IPv6 */

/* authentication families not tied to a specific protocol */
enum FamilyServerInterpreted    = 5;

/* Property notification */

enum PropertyNewValue       = 0;
enum PropertyDelete         = 1;

/* Color Map notification */

enum ColormapUninstalled        = 0;
enum ColormapInstalled          = 1;

/* GrabPointer, GrabButton, GrabKeyboard, GrabKey Modes */

enum GrabModeSync           = 0;
enum GrabModeAsync          = 1;

/* GrabPointer, GrabKeyboard reply status */

enum GrabSuccess        = 0;
enum AlreadyGrabbed     = 1;
enum GrabInvalidTime    = 2;
enum GrabNotViewable    = 3;
enum GrabFrozen         = 4;

/* AllowEvents modes */

enum AsyncPointer       = 0;
enum SyncPointer        = 1;
enum ReplayPointer      = 2;
enum AsyncKeyboard      = 3;
enum SyncKeyboard       = 4;
enum ReplayKeyboard     = 5;
enum AsyncBoth          = 6;
enum SyncBoth           = 7;

/* Used in SetInputFocus, GetInputFocus */

enum RevertToNone           = None;
enum RevertToPointerRoot    = PointerRoot;
enum RevertToParent         = 2;

/*****************************************************************
 * ERROR CODES
 *****************************************************************/

enum Success            = 0;	/* everything's okay */
enum BadRequest         = 1;	/* bad request code */
enum BadValue           = 2;	/* int parameter out of range */
enum BadWindow          = 3;	/* parameter not a Window */
enum BadPixmap          = 4;	/* parameter not a Pixmap */
enum BadAtom            = 5;	/* parameter not an Atom */
enum BadCursor          = 6;	/* parameter not a Cursor */
enum BadFont            = 7;	/* parameter not a Font */
enum BadMatch           = 8;	/* parameter mismatch */
enum BadDrawable        = 9;	/* parameter not a Pixmap or Window */
enum BadAccess          = 10;	/* depending on context:
				 - key/button already grabbed
				 - attempt to free an illegal
				   cmap entry
				- attempt to store into a read-only
				   color map entry.
 				- attempt to modify the access control
				   list from other than the local host.
				*/
enum BadAlloc       = 11;	/* insufficient resources */
enum BadColor       = 12;	/* no such colormap */
enum BadGC          = 13;	/* parameter not a GC */
enum BadIDChoice            = 14;	/* choice not in range or already used */
enum BadName            = 15;	/* font or color name doesn't exist */
enum BadLength          = 16;	/* Request length incorrect */
enum BadImplementation          = 17;	/* server is defective */

enum FirstExtensionError            = 128;
enum LastExtensionError         = 255;

/*****************************************************************
 * WINDOW DEFINITIONS
 *****************************************************************/

/* Window classes used by CreateWindow */
/* Note that CopyFromParent is already defined as 0 above */

enum InputOutput            = 1;
enum InputOnly          = 2;

/* Window attributes for CreateWindow and ChangeWindowAttributes */

enum CWBackPixmap           = (1L<<0);
enum CWBackPixel            = (1L<<1);
enum CWBorderPixmap         = (1L<<2);
enum CWBorderPixel          = (1L<<3);
enum CWBitGravity           = (1L<<4);
enum CWWinGravity           = (1L<<5);
enum CWBackingStore         = (1L<<6);
enum CWBackingPlanes            = (1L<<7);
enum CWBackingPixel         = (1L<<8);
enum CWOverrideRedirect         = (1L<<9);
enum CWSaveUnder            = (1L<<10);
enum CWEventMask            = (1L<<11);
enum CWDontPropagate            = (1L<<12);
enum CWColormap         = (1L<<13);
enum CWCursor           = (1L<<14);

/* ConfigureWindow structure */

enum CWX            = (1<<0);
enum CWY            = (1<<1);
enum CWWidth            = (1<<2);
enum CWHeight           = (1<<3);
enum CWBorderWidth          = (1<<4);
enum CWSibling          = (1<<5);
enum CWStackMode            = (1<<6);


/* Bit Gravity */

enum ForgetGravity          = 0;
enum NorthWestGravity           = 1;
enum NorthGravity           = 2;
enum NorthEastGravity           = 3;
enum WestGravity            = 4;
enum CenterGravity          = 5;
enum EastGravity            = 6;
enum SouthWestGravity           = 7;
enum SouthGravity           = 8;
enum SouthEastGravity           = 9;
enum StaticGravity          = 10;

/* Window gravity + bit gravity above */

enum UnmapGravity           = 0;

/* Used in CreateWindow for backing-store hint */

enum NotUseful          = 0;
enum WhenMapped         = 1;
enum Always         = 2;

/* Used in GetWindowAttributes reply */

enum IsUnmapped         = 0;
enum IsUnviewable           = 1;
enum IsViewable         = 2;

/* Used in ChangeSaveSet */

enum SetModeInsert          = 0;
enum SetModeDelete          = 1;

/* Used in ChangeCloseDownMode */

enum DestroyAll         = 0;
enum RetainPermanent            = 1;
enum RetainTemporary            = 2;

/* Window stacking method (in configureWindow) */

enum Above          = 0;
enum Below          = 1;
enum TopIf          = 2;
enum BottomIf           = 3;
enum Opposite           = 4;

/* Circulation direction */

enum RaiseLowest            = 0;
enum LowerHighest           = 1;

/* Property modes */

enum PropModeReplace            = 0;
enum PropModePrepend            = 1;
enum PropModeAppend         = 2;

/*****************************************************************
 * GRAPHICS DEFINITIONS
 *****************************************************************/

/* graphics functions, as in GC.alu */

enum	GXclear         = 0x0;		/* 0 */
enum GXand          = 0x1;		/* src AND dst */
enum GXandReverse           = 0x2;		/* src AND NOT dst */
enum GXcopy         = 0x3;		/* src */
enum GXandInverted          = 0x4;		/* NOT src AND dst */
enum	GXnoop          = 0x5;		/* dst */
enum GXxor          = 0x6;		/* src XOR dst */
enum GXor           = 0x7;		/* src OR dst */
enum GXnor          = 0x8;		/* NOT src AND NOT dst */
enum GXequiv            = 0x9;		/* NOT src XOR dst */
enum GXinvert           = 0xa;		/* NOT dst */
enum GXorReverse            = 0xb;		/* src OR NOT dst */
enum GXcopyInverted         = 0xc;		/* NOT src */
enum GXorInverted           = 0xd;		/* NOT src OR dst */
enum GXnand         = 0xe;		/* NOT src OR NOT dst */
enum GXset          = 0xf;		/* 1 */

/* LineStyle */

enum LineSolid          = 0;
enum LineOnOffDash          = 1;
enum LineDoubleDash         = 2;

/* capStyle */

enum CapNotLast         = 0;
enum CapButt            = 1;
enum CapRound           = 2;
enum CapProjecting          = 3;

/* joinStyle */

enum JoinMiter          = 0;
enum JoinRound          = 1;
enum JoinBevel          = 2;

/* fillStyle */

enum FillSolid          = 0;
enum FillTiled          = 1;
enum FillStippled           = 2;
enum FillOpaqueStippled         = 3;

/* fillRule */

enum EvenOddRule            = 0;
enum WindingRule            = 1;

/* subwindow mode */

enum ClipByChildren         = 0;
enum IncludeInferiors           = 1;

/* SetClipRectangles ordering */

enum Unsorted           = 0;
enum YSorted            = 1;
enum YXSorted           = 2;
enum YXBanded           = 3;

/* CoordinateMode for drawing routines */

enum CoordModeOrigin            = 0;	/* relative to the origin */
enum CoordModePrevious          = 1;	/* relative to previous point */

/* Polygon shapes */

enum Complex            = 0;	/* paths may intersect */
enum Nonconvex          = 1;	/* no paths intersect, but not convex */
enum Convex         = 2;	/* wholly convex */

/* Arc modes for PolyFillArc */

enum ArcChord           = 0;	/* join endpoints of arc */
enum ArcPieSlice            = 1;	/* join endpoints to center of arc */

/* GC components: masks used in CreateGC, CopyGC, ChangeGC, OR'ed into
   GC.stateChanges */

enum GCFunction         = (1L<<0);
enum GCPlaneMask            = (1L<<1);
enum GCForeground           = (1L<<2);
enum GCBackground           = (1L<<3);
enum GCLineWidth            = (1L<<4);
enum GCLineStyle            = (1L<<5);
enum GCCapStyle         = (1L<<6);
enum GCJoinStyle            = (1L<<7);
enum GCFillStyle            = (1L<<8);
enum GCFillRule         = (1L<<9);
enum GCTile         = (1L<<10);
enum GCStipple          = (1L<<11);
enum GCTileStipXOrigin          = (1L<<12);
enum GCTileStipYOrigin          = (1L<<13);
enum GCFont         = (1L<<14);
enum GCSubwindowMode            = (1L<<15);
enum GCGraphicsExposures            = (1L<<16);
enum GCClipXOrigin          = (1L<<17);
enum GCClipYOrigin          = (1L<<18);
enum GCClipMask         = (1L<<19);
enum GCDashOffset           = (1L<<20);
enum GCDashList         = (1L<<21);
enum GCArcMode          = (1L<<22);

enum GCLastBit          = 22;
/*****************************************************************
 * FONTS
 *****************************************************************/

/* used in QueryFont -- draw direction */

enum FontLeftToRight            = 0;
enum FontRightToLeft            = 1;

enum FontChange         = 255;

/*****************************************************************
 *  IMAGING
 *****************************************************************/

/* ImageFormat -- PutImage, GetImage */

enum XYBitmap           = 0;	/* depth 1, XYFormat */
enum XYPixmap           = 1;	/* depth == drawable depth */
enum ZPixmap            = 2;	/* depth == drawable depth */

/*****************************************************************
 *  COLOR MAP STUFF
 *****************************************************************/

/* For CreateColormap */

enum AllocNone          = 0;	/* create map with no entries */
enum AllocAll           = 1;	/* allocate entire map writeable */


/* Flags used in StoreNamedColor, StoreColors */

enum DoRed          = (1<<0);
enum DoGreen            = (1<<1);
enum DoBlue         = (1<<2);

/*****************************************************************
 * CURSOR STUFF
 *****************************************************************/

/* QueryBestSize Class */

enum CursorShape            = 0;	/* largest size that can be displayed */
enum TileShape          = 1;	/* size tiled fastest */
enum StippleShape           = 2;	/* size stippled fastest */

/*****************************************************************
 * KEYBOARD/POINTER STUFF
 *****************************************************************/

enum AutoRepeatModeOff          = 0;
enum AutoRepeatModeOn           = 1;
enum AutoRepeatModeDefault          = 2;

enum LedModeOff         = 0;
enum LedModeOn          = 1;

/* masks for ChangeKeyboardControl */

enum KBKeyClickPercent          = (1L<<0);
enum KBBellPercent          = (1L<<1);
enum KBBellPitch            = (1L<<2);
enum KBBellDuration         = (1L<<3);
enum KBLed          = (1L<<4);
enum KBLedMode          = (1L<<5);
enum KBKey          = (1L<<6);
enum KBAutoRepeatMode           = (1L<<7);

enum MappingSuccess         = 0;
enum MappingBusy            = 1;
enum MappingFailed          = 2;

enum MappingModifier            = 0;
enum MappingKeyboard            = 1;
enum MappingPointer         = 2;

/*****************************************************************
 * SCREEN SAVER STUFF
 *****************************************************************/

enum DontPreferBlanking         = 0;
enum PreferBlanking         = 1;
enum DefaultBlanking            = 2;

enum DisableScreenSaver         = 0;
enum DisableScreenInterval          = 0;

enum DontAllowExposures         = 0;
enum AllowExposures         = 1;
enum DefaultExposures           = 2;

/* for ForceScreenSaver */

enum ScreenSaverReset           = 0;
enum ScreenSaverActive          = 1;

/*****************************************************************
 * HOSTS AND CONNECTIONS
 *****************************************************************/

/* for ChangeHosts */

enum HostInsert         = 0;
enum HostDelete         = 1;

/* for ChangeAccessControl */

enum EnableAccess           = 1;
enum DisableAccess          = 0;

/* Display classes  used in opening the connection
 * Note that the statically allocated ones are even numbered and the
 * dynamically changeable ones are odd numbered */

enum StaticGray         = 0;
enum GrayScale          = 1;
enum StaticColor            = 2;
enum PseudoColor            = 3;
enum TrueColor          = 4;
enum DirectColor            = 5;


/* Byte order  used in imageByteOrder and bitmapBitOrder */

enum LSBFirst           = 0;
enum MSBFirst = 1;