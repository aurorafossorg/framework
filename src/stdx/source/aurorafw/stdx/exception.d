module aurorafw.stx.exception;

public import std.exception;

import aurorafw.unit.assertion;

static class NotImplementedException : Exception
{
    mixin basicExceptionCtors;
}

@safe pure
@("Exception: NotImplementedException")
unittest {
	auto shouldThrow = () {
		throw new NotImplementedException("Not yet implemented on this platform!"); };

	assertThrown(shouldThrow());
}
