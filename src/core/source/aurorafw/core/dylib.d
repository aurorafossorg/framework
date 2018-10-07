module aurorafw.core.dylib;

import std.array;
import std.string;

struct DylibVersion
{
	uint major;
	uint minor;
	uint patch;
}

abstract class DylibLoader
{
	this(immutable string libs)
	{
		_libs = libs;
	}

	immutable string _libs;
}