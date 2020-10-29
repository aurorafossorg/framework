module aurorafw.metadata.jpeg;

enum JPEGVersion
{
	JPEG_CANON_EOS,
	JPEG_SAMSUNG_D500,
	Unknown
}

import std.stdio : File;

@safe
JPEGVersion getJPEGVersion(File file)
{
	char[4] buf = file.rawRead(new char[4]);
	if (buf[3] == 0xE2)
		return JPEGVersion.JPEG_CANON_EOS;
	else if (buf[3] == 0xE3)
		return JPEGVersion.JPEG_SAMSUNG_D500;

	return JPEGVersion.Unknown;
}

@safe pure
string toString(JPEGVersion ver)
{
	final switch (ver)
	{
	case JPEGVersion.JPEG_CANON_EOS:
		return "CANON EOS JPEG Format";
	case JPEGVersion.JPEG_SAMSUNG_D500:
		return "Samsung D500 JPEG Format";
	case JPEGVersion.Unknown:
		return "Unknown";
	}
}

@safe
@("JPEG: Versioning")
unittest
{
	import std.file;

	version (unittest) import aurorafw.unit.assertion;
	import std.conv : to;

	scope (exit)
	{
		assert(exists(deleteme));
		remove(deleteme);
	}

	JPEGVersion version_;
	char[] buf = [0xFF, 0xD8, 0xFF];

	write(deleteme, buf ~ 0xE2);
	version_ = getJPEGVersion(File(deleteme));
	assertEquals(JPEGVersion.JPEG_CANON_EOS, version_);
	assertEquals("CANON EOS JPEG Format", version_.toString);

	write(deleteme, buf ~ 0xE3);
	version_ = getJPEGVersion(File(deleteme));
	assertEquals(JPEGVersion.JPEG_SAMSUNG_D500, version_);
	assertEquals("Samsung D500 JPEG Format", version_.toString);

	write(deleteme, buf ~ 0xFF);
	version_ = getJPEGVersion(File(deleteme));
	assertEquals(JPEGVersion.Unknown, version_);
	assertEquals("Unknown", version_.toString);
}
