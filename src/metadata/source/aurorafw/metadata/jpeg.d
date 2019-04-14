module aurorafw.metadata.jpeg;

enum JPEGVersion {
	JPEG_CANON_EOS,
	JPEG_SAMSUNG_D500,
	Unknown
}

import std.stdio : File;

JPEGVersion getJPEGVersion(File file)
{
	char[4] buf = file.rawRead(new char[4]);
	if(buf[3] == 0xE2) return JPEGVersion.JPEG_CANON_EOS;
	else if(buf[3] == 0xE3) return JPEGVersion.JPEG_SAMSUNG_D500;

	return JPEGVersion.Unknown;
}

string toString(JPEGVersion ver)
{
	final switch(ver)
	{
		case JPEGVersion.JPEG_CANON_EOS: return "CANON EOS JPEG Format";
		case JPEGVersion.JPEG_SAMSUNG_D500: return "Samsung D500 JPEG Format";
		case JPEGVersion.Unknown: return "Unknown";
	}
}
