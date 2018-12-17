module app;

import aurorafw.metadata.signature;
import std.stdio : writeln, File;

int main(string[] args)
{
	writeln(detectFileSignature(File(args[1], "r")).toString);
	return 0;
}