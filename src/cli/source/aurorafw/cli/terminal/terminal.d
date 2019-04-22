module aurorafw.cli.terminal.terminal;

import aurorafw.core.input.events;
import aurorafw.core.input.keys;

version(Posix)
{
	import core.sys.posix.unistd;
	import core.sys.posix.termios;
	import core.sys.posix.sys.ioctl;
} else version(Windows)
{
	import core.sys.windows.windows;
}

import std.process;
import std.string;
import std.exception;
import std.utf;
import std.typecons;
import std.file;
import std.stdio;
import std.ascii : isAlpha;
import std.conv;

import core.stdc.errno;
import core.stdc.stdio;

/** Exception for terminal die
 * This exception is thrown when theres a problem with
 * terminal related issue.
 */
class TerminalDieException : Exception {
	/** Terminal Die Exception Constructor
	 * This construct a normal exception and disable
	 * terminal raw mode.
	 * @param term Terminal
	 * @param msg exception message
	 * @param file code file
	 * @param line line code on file
	 * @param next next throwable object
	 */
	this(ref Terminal term, string msg,
		string file = __FILE__, size_t line = __LINE__,
		Throwable next = null)
	{
		term.disableRawMode();
		super(msg, file, line, next);
	}

	/** Terminal Die Exception Constructor
	 * This construct a normal exception and disable
	 * terminal raw mode.
	 * @param term Terminal
	 * @param msg exception message
	 * @param next next throwable object
	 * @param file code file
	 * @param line line code on file
	 */
	this(ref Terminal term, string msg, Throwable next,
		string file = __FILE__, size_t line = __LINE__)
	{
		term.disableRawMode();
		super(msg, file, line, next);
	}
}

// TODO: Switch special writes to termcap codes

/** Terminal Struct
 * This struct represents a terminal buffer and
 * a set of functions to manipulate it under the
 * defined i/o descriptors.
 */
struct Terminal {
	// disable empty and copy constructors
	@disable this();
	@disable this(this);

	/** Terminal Output Type
	 * Enumerates the terminal output type
	 */
	public enum OutputType
	{
		CELL,
		MINIMAL,
		LINEAR
	}

	/** Constructor for Terminal
	 * This construct a terminal buffer with the specified
	 * output type and i/o descriptors
	 * @param outType Output Type
	 * @param outputDescriptor Output descriptor
	 * @param inputDescriptor Input descriptor
	 */
	public this(OutputType outType, int outputDescriptor = STDOUT_FILENO, int inputDescriptor = STDIN_FILENO)
	{
		this.outType = outType;
		this.outputDescriptor = outputDescriptor;
		this.inputDescriptor = inputDescriptor;

		// for cell based output (grid-style)
		if(outType == OutputType.CELL)
		{
			saveTitle();
			enableRawMode();
		}
	}

	/** Destructor for Terminal
	 * This destruct a terminal buffer after disabling the raw mode
	 */
	~this()
	{
		if(outType == OutputType.CELL)
		{
			disableRawMode(true);
			restoreTitle(true);
		}
	}

	public void enableRawMode()
	{
		if(rawMode == true)
			return;
		rawMode = true;

		if (tcgetattr(inputDescriptor, &origTermios) == -1)
			throw new TerminalDieException(this, "tcgetattr");

		termios raw = origTermios;

		raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
		raw.c_oflag &= ~(OPOST);
		raw.c_cflag |= (CS8);
		raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
		raw.c_cc[VMIN] = 0;
		raw.c_cc[VTIME] = 1;

		if (tcsetattr(inputDescriptor, TCSAFLUSH, &raw) == -1)
			throw new TerminalDieException(this, "tcsetattr");

		alternateScreen(true);
	}

	public void viewCursor(bool val, bool flush = false)
	{
		string ret;
		if(val)
			ret = "\x1b[?25h";
		else
			ret = "\x1b[?25l";

		if(flush)
			writeDescriptor(ret);
		else
			writeBuffer(ret);
	}

	public void alternateScreen(bool val, bool flush = false)
	{
		string ret;
		if(val)
			ret = "\x1b[?1049h";
		else
			ret = "\x1b[?1049l";

		if(flush)
			writeDescriptor(ret);
		else
			writeBuffer(ret);
	}

	public void disableRawMode(bool flush = false)
	{
		if(rawMode == false)
			return;
		rawMode = false;

		alternateScreen(false, flush);

		if (tcsetattr(inputDescriptor, TCSAFLUSH, &origTermios) == -1)
			throw new TerminalDieException(this, "tcsetattr");
	}

	public void clear(bool flush = false)
	{
		if(outType == OutputType.CELL)
		{
			string ret = "\x1b[2J\x1b[H";
			if(flush)
				writeDescriptor(ret);
			else
				writeBuffer(ret);
		}
	}
	public void setCursorPos(size_t x = 0, size_t y = 0, bool flush = false)
	{
		string ret = "\x1b["~to!string(y + 1)~";"~to!string(x + 1)~"H";
		if(flush)
			writeDescriptor(ret);
		else
			writeBuffer(ret);
	}

	public void writeBuffer(char[] buf)
	{
		writeBuffer(cast(string)buf);
	}

	public void writeBuffer(string str)
	{
		buffer ~= str;
	}

	public void writeDescriptor(string str)
	{
		writeDescriptor(str.toStringz, str.length);
	}

	public void flushBuffer()
	{
		if(buffer.length>0)
		{
			writeDescriptor(buffer.toStringz, buffer.length);
			buffer.length = 0;
		}
	}

	public void writeDescriptor(const(char*) cstr, size_t len)
	{
		core.sys.posix.unistd.write(outputDescriptor, cstr, len);
	}

	public size_t readCh(ref dchar c)
	{
		size_t nread;
		char[1] buf;

		nread = .read(inputDescriptor, buf.ptr, buf.length);
		if (nread == -1 && errno != EAGAIN)
			throw new TerminalDieException(this, "read");
		if(nread == 0)
			c = 0;
		else
		{
			char[] dbuf;
			foreach (ch; buf[0 .. nread])
				dbuf ~= ch;
			if (dbuf.length && dbuf.length >= dbuf.stride())
				c = dbuf.decodeFront!(Yes.useReplacementDchar);
			else
				c = 0;
		}

		return nread;
	}

	public string readBuffer()
	{
		size_t nread;
		string buf;

		do {
			dchar c;
			nread = readCh(c);
			buf ~= c;
		}
		while (nread != 0);

		return buf;
	}

	public int getWindowSize(ref size_t rows, ref size_t cols)
	{
		winsize ws;

		if (ioctl(outputDescriptor, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
			if (core.sys.posix.unistd.write(outputDescriptor, "\x1b[999C\x1b[999B".toStringz, 12) != 12) return -1;
			return getCursorPosition(rows, cols);
		} else {
			rows = ws.ws_row;
			cols = ws.ws_col;
			return 0;
		}
	}

	public int getCursorPosition(ref size_t rows, ref size_t cols)
	{
		char[32] buf;
		uint i = 0;

		if (core.sys.posix.unistd.write(outputDescriptor, "\x1b[6n".toStringz, 4) != 4) return -1;

		while (i < buf.sizeof - 1) {
			if (.read(inputDescriptor, &buf[i], 1) != 1) break;
			if (buf[i] == 'R') break;
			i++;
		}

		buf[i] = '\0';

		if (buf[0] != '\x1b' || buf[1] != '[') return -1;
		if (sscanf(&buf[2], "%d;%d", &rows, &cols) != 2) return -1;

		return 0;
	}

	@property public bool isRawMode()
	{
		return rawMode;
	}

	public void setTitle(string title)
	{
		version(Windows) {
			SetConsoleTitleA(toStringz(title));
		} else {
			if(terminalInFamily("xterm", "rxvt", "screen"))
				writeBuffer(format("\x1b]0;%s\007", title));
		}
	}

	private void saveTitle(bool flush = false)
	{
		version(Posix)
		{
			if(terminalInFamily("xterm", "rxvt", "screen")) {
				if(flush)
					writeDescriptor("\x1b[22;0t");
				else
					writeBuffer("\x1b[22;0t");
			}
		}
	}

	private void restoreTitle(bool flush = false)
	{
		version(Posix)
		{
			if(terminalInFamily("xterm", "rxvt", "screen"))
			{
				if(flush)
					writeDescriptor("\x1b[23;0t");
				else
					writeBuffer("\x1b[23;0t");
			}
		}
	}

	pragma(inline) public KeyboardEvent[] pullEvents()
	{
		return translatePosixEvents(readBuffer());
	}

	public static KeyboardEvent[] translatePosixEvents(string eseq)
	{
		KeyboardEvent[] kb_events;
		for(int i = 0; i < eseq.length; i++)
		{
			if(isAlpha(eseq[i]))
			{
				auto tmp_str = to!string(toUpper(eseq[0]));
				kb_events ~= KeyboardEvent(
					parse!Keycode(tmp_str),
					InputModifier.None);
			}
		}
		return [KeyboardEvent(Keycode.Unknown, InputModifier.None)];
	}

	version(Posix)
	{
		public static bool terminalInFamily(string[] terms...)
		{
			auto term = environment.get("TERM");
			foreach(t; terms)
				if(indexOf(term, t) != -1)
					return true;
			return false;
		}

		public static bool isMacTerminal()
		{
			auto term = environment.get("TERM");
			return term == "xterm-256color";
		}
	}

	private OutputType outType;
	private int outputDescriptor;
	private int inputDescriptor;
	private string buffer;
	private bool rawMode = false;

	version(Posix) {
		private termios origTermios;
	} else version(Windows) {
		private HANDLE hConsole;
		private CONSOLE_SCREEN_BUFFER_INFO originalSbi;
	}
}
