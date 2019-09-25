module aurorafw.stdx.array;

public import std.array;
import aurorafw.unit.assertion;

@safe pure
T[] replaceFirst(T)(T[] arr, T from, T to)
{
	foreach(i, ref e; arr)
		if(e == from)
			return arr[0 .. i] ~ to ~ arr[i + 1 .. $];

	return arr;
}


@safe pure
@("Array: replaceFirst")
unittest {
	assertEquals("1est", "Test".replaceFirst('T', '1'));
	assertEquals("test", "test".replaceFirst('T', '1'));
	assertEquals("1Test", "TTest".replaceFirst('T', '1'));
	assertEquals("Tes1", "Test".replaceFirst('t', '1'));
}
