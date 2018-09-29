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

module aurorafw.gui.platform.x11.extensions.xf86vmode;

import X = aurorafw.gui.platform.x11.x;
import core.stdc.config;

enum CLKFLAG_PROGRAMABLE = 1;

enum XF86VidModeBadClock = 0;
enum XF86VidModeBadHTimings = 1;
enum XF86VidModeBadVTimings = 2;
enum XF86VidModeModeUnsuitable = 3;
enum XF86VidModeExtensionDisabled = 4;
enum XF86VidModeClientNotLocal = 5;
enum XF86VidModeZoomLocked = 6;
enum XF86VidModeNumberErrors = (XF86VidModeZoomLocked + 1);
enum XF86VM_READ_PERMISSION	= 1;
enum XF86VM_WRITE_PERMISSION = 2;

struct XF86VidModeModeLine {
	ushort hdisplay;
	ushort hsyncstart;
	ushort hsyncend;
	ushort htotal;
	ushort hskew;
	ushort vdisplay;
	ushort vsyncstart;
	ushort vsyncend;
	ushort vtotal;
	uint flags;
	int privsize;
	int *c_private;
}

struct XF86VidModeModeInfo {
	uint dotclock;
	ushort hdisplay;
	ushort hsyncstart;
	ushort hsyncend;
	ushort htotal;
	ushort hskew;
	ushort vdisplay;
	ushort vsyncstart;
	ushort vsyncend;
	ushort vtotal;
	uint flags;
	int privsize;
	int *c_private;
}

struct XF86VidModeSyncRange {
	float hi;
	float lo;
}

struct XF86VidModeMonitor {
	char* vendor;
	char* model;
	float EMPTY;
	char nhsync;
	XF86VidModeSyncRange* hsync;
	char nvsync;
	XF86VidModeSyncRange* vsync;
}

struct XF86VidModeNotifyEvent {
	int type; /* of event */
	c_ulong serial; /* # of last request processed by server */
	X.Bool send_event; /* true if this came from a SendEvent req */
	X.Display *display; /* Display the event was read from */
	X.Window root; /* root window of event screen */
	int state; /* What happened */
	int kind; /* What happened */
	X.Bool forced; /* extents of new region */
	X.Time time; /* event timestamp */
}

extern(C) @nogc nothrow {
	alias da_XF86VidModeQueryExtension = X.Bool function(X.Display*, int*, int*);
	alias da_XF86VidModeGetGammaRamp = X.Bool function(X.Display*,int,int,ushort*,ushort*,ushort*);
	alias da_XF86VidModeSetGammaRamp = X.Bool function(X.Display*,int,int,ushort*,ushort*,ushort*);
	alias da_XF86VidModeGetGammaRampSize = X.Bool function(X.Display*, int, int*);
}
