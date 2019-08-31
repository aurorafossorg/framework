module aurorafw.stdx.string;

public import std.string;

@safe pure
string substr(string s, ptrdiff_t offset, ptrdiff_t length)
{
	size_t end = void;
	if (offset > s.length)
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
pragma(inline) bool isAlpha(string str)
{
	import std.algorithm : all;
	import std.uni : isAlpha;

	return str.all!(x => isAlpha(x));
}

@safe
@("String: substr")
unittest {
	string s = "Aurora Framework";
	assert(s.substr(1,5)=="urora");
}

@safe
@("String: isAlpha")
unittest {
	assert(isAlpha("tunaisgood"));
	assert(!isAlpha("tun41s900d"));
}
