module aurorafw.metadata.pdf;

public import aurorafw.core.versionmanager : toString;
import aurorafw.core.versionmanager : Version;
import std.stdio : File;

enum PDFVersion : Version {
	PDF_1_4=Version(1,4),
	PDF_1_6=Version(1,6),
	PDF_1_7=Version(1,7),
	PDF_2_0=Version(2,0),
	Unknown=Version(0,0)
}

Version getPDFVersion(File file)
{
	char[4] buf = file.rawRead(new char[8])[4..8];
	if(buf == cast(char[])"-1.4") return PDFVersion.PDF_1_4;
	else if(buf == cast(char[])"-1.6") return PDFVersion.PDF_1_6;
	else if(buf == cast(char[])"-1.7") return PDFVersion.PDF_1_7;
	else if(buf == cast(char[])"-2.0") return PDFVersion.PDF_2_0;

	return PDFVersion.Unknown;
}