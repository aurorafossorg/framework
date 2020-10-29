module aurorafw.core.io.filestream;

import std.stdio;

import aurorafw.core.io.stream;

version (unittest) import aurorafw.unit.assertion;

@safe
class FileStream : IStream
{

	/**
	 * Constructs a FileStream with a given filename and
	 * mode.
	 *
	  * Examples:
	 * --------------------
	 * FileStream foo = new FileStream("tuna.txt", "rb");
	 * --------------------
	 */
	public this(string filename, string mode = "rb")
	{
		fd = File(filename, mode);

		import std.algorithm.searching : canFind;

		_writable = WRITABLE.canFind(mode);
		_readable = READABLE.canFind(mode);
	}

	@property ulong length()
	{
		return fd.size;
	}

	@property ulong tell()
	{
		return fd.tell;
	}

	@property bool empty()
	{
		return (fd.size - fd.tell) <= 0;
	}

	@property bool eof()
	{
		return empty();
	}

	@property bool seekable()
	{
		return true;
	}

	@property bool readable()
	{
		return _readable;
	}

	@property bool writable()
	{
		return _writable;
	}

	ulong skip(ulong n)
	{
		return seek(n, Seek.CUR);
	}

	ulong seek(in long pos, in Seek origin = Seek.SET)
	{
		import std.stdio : SEEK_SET, SEEK_CUR, SEEK_END;

		int orig;
		with (Seek) final switch (origin)
		{
		case SET:
			orig = SEEK_SET;
			break;
		case CUR:
			orig = SEEK_CUR;
			break;
		case END:
			orig = SEEK_END;
			break;
		}

		fd.seek(pos, orig);

		return tell;
	}

	void write(in ubyte b)
	{
		fd.rawWrite([b]);
	}

	void write(in ubyte[] b)
	{
		fd.rawWrite(b);
	}

	ubyte read()
	{
		if ((fd.tell + ubyte.sizeof) > fd.size)
			throw new StreamException("Attempt reading outside of the stream");

		ubyte[1] b;
		fd.rawRead(b);

		return b[0];
	}

	ubyte[] read(in size_t n)
	{
		import std.conv : to;

		auto buf = new ubyte[(fd.tell + n > fd.size) ? (fd.size - fd.tell).to!size_t : n];
		fd.rawRead(buf);

		return buf;
	}

	ubyte[] data()
	{
		import std.conv : to;

		size_t s = (fd.size - fd.tell).to!size_t;
		if (!s)
			return [];

		auto ret = new ubyte[s];
		fd.rawRead(ret);
		return ret;
	}

	private enum READABLE = [
			"r", "w+", "r+", "x+", "c+", "rb", "w+b", "r+b", "x+b", "c+b", "rt", "w+t", "r+t", "x+t", "c+t", "a+"
		];

	private enum WRITABLE = [
			"w", "w+", "r+", "x+", "c+", "wb", "w+b", "r+b", "x+b", "c+b", "w+t", "r+t", "x+t", "c+t", "a", "a+"
		];

	private immutable bool _readable;
	private immutable bool _writable;

	private File fd;
}

version (unittest)
{
	@safe
	private string unittest_deleteme_file()
	{
		import std.file;
		import std.path : buildPath;
		import std.uuid : randomUUID;

		auto dm = buildPath(tempDir(), randomUUID.toString);
		std.file.write(dm, "abc");

		return dm;
	}
}

///
/*@safe*/
@("File Stream: Readable stream")
unittest
{
	import std.file;

	auto dm = unittest_deleteme_file;
	scope (exit)
		std.file.remove(dm);

	FileStream fs = new FileStream(dm);
	unittest_readable_stream(fs);
	assertFalse(fs.writable);
}

///
/*@safe*/
@("File Stream: Writable stream")
unittest
{
	import std.file;

	auto dm = unittest_deleteme_file;
	scope (exit)
		std.file.remove(dm);

	FileStream fs = new FileStream(dm, "w");
	unittest_writable_stream(fs);
	assertFalse(fs.readable);
}

///
/*@safe*/
@("File Stream: Read & Write stream")
unittest
{
	import std.file;

	auto dm = unittest_deleteme_file;
	FileStream fs = new FileStream(dm, "r+");
	scope (exit)
		std.file.remove(dm);
	unittest_readable_stream(fs);
	unittest_writable_stream(fs);
}
