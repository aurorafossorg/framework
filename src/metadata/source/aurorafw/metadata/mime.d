module aurorafw.metadata.mime;

import aurorafw.metadata.signature;
version(unittest) import aurorafw.unit.assertion;

@safe pure @nogc nothrow
string toMIME(FileSignature val)
{
	switch(val)
	{
		case FileSignature.PDF: return "application/pdf";
		case FileSignature.JPEG: return "image/jpeg";
		case FileSignature.PNG: return "image/png";

		case FileSignature.Unknown:
		default: return "application/octet-stream";
	}
}

@safe
@("MIME Type: from File signature")
unittest
{
	assertEquals("application/pdf", FileSignature.PDF.toMIME);
	assertEquals("image/jpeg", FileSignature.JPEG.toMIME);
	assertEquals("image/png", FileSignature.PNG.toMIME);
	assertEquals("application/octet-stream", FileSignature.Unknown.toMIME);
}
