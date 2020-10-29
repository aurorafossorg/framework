module app;

import aurorafw.metadata.signature;
import aurorafw.metadata.pdf;

int main(string[] args)
{
	import std.stdio : writeln, File;

	File file = File(args[1], "r");
	import std.conv : to;

	writeln(getPDFVersion(file).to!string);

	return 0;
}
