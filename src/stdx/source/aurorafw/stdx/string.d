module aurorafw.stdx.string;

public import std.string;
import aurorafw.unit.assertion;

@safe pure
string substr(string s, ptrdiff_t offset, ptrdiff_t length = -1)
{
	size_t end = void;
	import std.stdio;

	if (offset > 0 && offset > s.length)
		return "";
	if (offset < 0)
		offset = 0;
	if (length < 0)
		end = s.length;
	else
		end = offset + length;
	if(end > s.length)
		end = s.length;

	return s[offset .. end];
}

@safe pure
bool isAlpha(string str)
{
	import std.algorithm : all;
	import std.uni : isAlpha;

	return str.all!(x => isAlpha(x));
}


@safe
@("String: substr")
unittest {
	string s = "Aurora Framework";
	assertEquals("urora", s.substr(1,5));
	assertEquals("urora Framework", s.substr(1));
	assertEquals(s, s.substr(-1, -1));
	assertEquals(s, s.substr(-1));
	assertEquals(s, s.substr(0, ptrdiff_t.max));
	assertEquals("", s.substr(ptrdiff_t.max));
}

@safe pure
@("String: isAlpha")
unittest {
	assert(isAlpha("tunaisgood"));
	assert(!isAlpha("tun41s900d"));
}
