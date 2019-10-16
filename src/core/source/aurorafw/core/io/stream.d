module aurorafw.core.io.stream;

import core.exception;
import std.exception;

version (unittest) import aurorafw.unit.assertion;

enum Seek
{
	SET, /// beginning of the stream
	CUR, /// current position
	END /// end of the stream
}

class StreamException : Exception
{
	mixin basicExceptionCtors;
}

interface IStream {
	/**
	 * A property that returns the length of the stream
	 *
	 * Returns: The length of the stream in bytes
	 */
	@property ulong length();

	/**
	 * Current position
	 *
	 * Returns: The current positon in the stream
	 */
	@property ulong tell();

	/**
	 * Check if empty
	 *
	 * Returns: True if the stream is empty
	 */
	@property bool empty();

	/**
	 * Seekable
	 *
	 * Returns: True if the stream is seekable
	 */
	@property bool seekable();

	/**
	 * Sets the current position in the stream
	 *
	 * Returns: The current positon in the stream
	 *
	 * Params:
	 *  pos = The number of bytes to offset from origin
	 *  origin = Position used as reference for the offset.
	 */
	ulong seek(in long pos, in Seek origin = Seek.SET);

	/**
	 * Skip n positions in the stream
	 *
	 * Returns: The current position in the stream
	 *
	 * Params:
	 *  n = The number of bytes to skip
	 */
	ulong skip(ulong n);

	/**
	 * Writable
	 *
	 * Returns: True if the stream is writeble
	 */
	@property bool writable();

	/**
	 * Writes an unsigned byte to the stream
	 *
	 * Params:
	 *  b = The ubyte to write to the stream
	 */
	void write(in ubyte b);

	/**
	 * Writes an array of unsigned bytes to the stream
	 *
	 * Params:
	 *  b = The array of ubyte to write to the stream
	 */
	void write(in ubyte[] b);


	/**
	 * Readable
	 *
	 * Returns: True if the stream is readable
	 */
	@property bool readable();

	/**
	 * Reads an unsigned byte from the stream
	 *
	 * Returns: The unsigned byte read from the stream
	 */
	ubyte read();

	/**
	 * Reads an array of ubytes from the stream
	 *
	 * Returns: The array of unsigned bytes read from the stream
	 *
	 * Params:
	 *  n = The number of bytes to read from the stream
	 */
	ubyte[] read(in size_t n);

	/**
	 * Reads the entire stream
	 *
	 * Returns: The array of unsigned bytes read from the stream
	 */
	ubyte[] data();
}

version(unittest)
{
	// assuming the content of the stream is "abc"
	// and the function leave the stream at the beginning
	package void unittest_readable_stream(IStream s)
	{
		assertTrue(s.seekable);
		assertTrue(s.readable);

		assertEquals(3, s.length);
		assertFalse(s.empty);

		assertEquals(0, s.seek(0, Seek.SET));
		assertEquals("abc", s.data);
		assertEquals(0, s.seek(0, Seek.SET));

		assertEquals('a', s.read());
		assertEquals("b", s.read(1));
		assertEquals(1, s.seek(-1, Seek.CUR));
		assertEquals("bc", s.data);
		assertEquals(2, s.seek(-1, Seek.END));
		assertEquals('c', s.read());
		expectThrows!StreamException(s.read());

		assertTrue(s.empty);
		assertEmpty(s.data);

		assertEquals(0, s.seek(0, Seek.SET));
	}

	package void unittest_writable_stream(IStream s)
	{
		assertTrue(s.seekable);
		assertTrue(s.writable);
		ubyte[] arr = ['4', '5'];
		s.seek(0, Seek.END);
		s.write(arr);
		s.write('6');
		if(s.readable)
		{
			s.seek(-3, Seek.END);
			assertEquals(arr ~ '6', s.data);
		}

		assertEquals(0, s.seek(0, Seek.SET));
	}
}
