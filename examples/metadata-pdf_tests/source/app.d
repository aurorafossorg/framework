module app;

import aurorafw.metadata.signature;
import aurorafw.metadata.pdf;

int main(string[] args)
{
	import std.stdio : writeln, File;

	File file = File(args[1], "r");
	writeln(getPDFVersion(file).toString(false));

	return 0;
}