module aurorafw.stdx.string;

public import std.string;

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

	return s[offset..end];
}

unittest {
	string s = "Aurora Framework";
	assert(s.substr(1,5)=="urora");
}
