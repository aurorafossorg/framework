module aurorafw.metadata.mime;

import aurorafw.metadata.signature;

@property @safe @nogc string toMIME(FileSignature val)
{
	switch(val)
	{
		case FileSignature.PDF: return "application/pdf";
		case FileSignature.JPEG: return "image/jpeg";
		case FileSignature.PNG: return "image/png";
		default: return "application/octet-stream";
	}
}