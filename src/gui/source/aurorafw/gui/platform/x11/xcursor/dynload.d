module aurorafw.gui.platform.x11.xcursor.dynload;

import aurorafw.core.dylib;

import aurorafw.gui.platform.x11.x;
import aurorafw.gui.platform.x11.xlib;
import core.stdc.stdio;

public import aurorafw.gui.platform.x11.xcursor.types;

extern(C) @nogc nothrow {
	alias da_XcursorImageCreate = XcursorImage* function(int width, int height);
	alias da_XcursorImageDestroy = void function(XcursorImage* image);
	alias da_XcursorImagesCreate = XcursorImages* function(int size);
	alias da_XcursorImagesDestroy = void function(XcursorImages* images);
}

__gshared {
	da_XcursorImageCreate XcursorImageCreate;
	da_XcursorImageDestroy XcursorImageDestroy;
	da_XcursorImagesCreate XcursorImagesCreate;
	da_XcursorImagesDestroy XcursorImagesDestroy;
}
class XCursorDylibLoader : DylibLoader {
	this()
	{
		super([""]);
	}

	override void loadSymbols()
	{
		bindFunc(cast(void**)&XcursorImageCreate,"XcursorImageCreate");
		bindFunc(cast(void**)&XcursorImageDestroy,"XcursorImageDestroy");
		bindFunc(cast(void**)&XcursorImagesCreate,"XcursorImagesCreate");
		bindFunc(cast(void**)&XcursorImagesDestroy,"XcursorImagesDestroy");
	}
}