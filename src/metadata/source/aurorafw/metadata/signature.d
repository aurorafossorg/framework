module aurorafw.metadata.signature;

import std.conv : to;
import std.stdio : File;

import std.algorithm.comparison;

enum FileSignature {
	PDF,
	JPEG,
	JPG=JPEG,
	PNG,
	IMG,
	ISO,
	DOC,
	DOCX,
	Unknown
}
FileSignature detectFileSignature(File file)
{
	char[8] buf = file.rawRead(new char[8]);
	if(buf[0..3] == cast(char[])[0xFF, 0xD8, 0xFF])
		return FileSignature.JPEG;
	else if(buf[0..4] == cast(char[])[0x25, 0x50, 0x44, 0x46])
		return FileSignature.PDF;
	else if(buf[0..5] == cast(char[])[0x43, 0x44, 0x30, 0x30, 0x31])
		return FileSignature.ISO;
	else if(buf[0..8] == cast(char[])[0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A])
		return FileSignature.PNG;
	else
		return FileSignature.Unknown;
}

@property @safe string toString(FileSignature val)
{
	switch(val)
	{
		case FileSignature.PDF: return "Portable Document Format";
		case FileSignature.ISO: return "ISO-9660 CD Disc Image";
		case FileSignature.JPEG: return "Joint Photographic Experts Group";
		case FileSignature.PNG: return "Portable Network Graphics";
		default: return to!string(val);
	}
}
