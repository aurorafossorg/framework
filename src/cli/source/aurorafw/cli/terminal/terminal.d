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
import std.uni;
import std.conv;

import core.stdc.errno;
import core.stdc.stdio;

import riverd.ncurses;

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
		term.terminate();
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
		this(term, msg, file, line, next);
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

		initscr();

		// for cell based output (grid-style)
		if(outType == OutputType.CELL)
		{
			saveTitle();
			enableRawMode();
		}
	}

	/** Destructor for Terminal
	 *
	 * This destruct a terminal buffer after terminating it.
	 */
	~this()
	{
		terminate();
	}

	/** Terminate terminal mode
	 *
	 * This function terminate all terminal modes and restore to the normal
	 * mode.
	 */
	package void terminate()
	{
		if(outType == OutputType.CELL)
		{
			disableRawMode(true);
			restoreTitle(true);
		}

		endwin();
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

		cbreak();

		if (tcsetattr(inputDescriptor, TCSAFLUSH, &raw) == -1)
			throw new TerminalDieException(this, "tcsetattr");

		alternateScreen(true);

		keypad(stdscr, true);
		nodelay(stdscr, true);

		noecho();
	}

	public void viewCursor(bool val, bool flush = true)
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


	@safe
	public void setCursorPos(int x = 0, int y = 0, bool flush = false)
	{
		string ret = "\x1b["~to!string(y + 1)~";"~to!string(x + 1)~"H";
		if(flush)
			writeDescriptor(ret);
		else
			writeBuffer(ret);
	}


	@safe
	public void moveXPos(int val = 0, bool flush = false)
	{
		string ret = "\x1b[" ~ to!string(val);

		// check if forward (+) or backward (-)
		if(val > 0)
			ret~= "C";
		else
			ret~= "D";

		if(flush)
			writeDescriptor(ret);
		else
			writeBuffer(ret);
	}


	@safe
	public void moveYPos(int val = 0, bool flush = false)
	{
		string ret = "\x1b[" ~ to!string(val);

		// check if forward (+) or backward (-)
		if(val > 0)
			ret~= 'B';
		else
			ret~= 'A';

		if(flush)
			writeDescriptor(ret);
		else
			writeBuffer(ret);
	}


	@safe
	public void writeBuffer(char[] buf) pure
	{
		buffer ~= buf;
	}


	@safe
	public void writeBuffer(dchar ch) pure
	{
		buffer ~= ch;
	}

	@safe
	public void writeBuffer(string str) pure
	{
		buffer ~= str;
	}

	@safe
	public void writeDescriptor(string str)
	{
		writeDescriptor(str.toStringz, str.length);
	}

	public void flushBuffer()
	{
		refresh();
		if(buffer.length > 0)
		{
			writeDescriptor(buffer.toStringz, buffer.length);
			buffer.length = 0;
		}
	}


	@trusted
	public void writeDescriptor(const(char*) cstr, size_t len)
	{
		//TODO: Check for error handling
		core.sys.posix.unistd.write(outputDescriptor, cstr, len);
	}

	public size_t readCh(ref dchar c)
	{
		size_t nread;
		char[1] buf;

		nread = .read(inputDescriptor, &buf[0], buf.length);
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
			if(nread != 0)
				buf ~= c;
		}
		while (nread != 0);

		return buf;
	}

	public int getWindowSize(ref int rows, ref int cols)
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


	public int getCursorPosition(ref int rows, ref int cols)
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


	public Event pollEvents()
	{
		Event ret;
		if (stdscr is null)
			throw new TerminalDieException(this, "null stdscr");

		int c = getch();
		while(c != -1)
		{
			ret.flags |= processEvent(c);
			++ret.eventsProcessed;

			c = getch();
		}

		if(input.buf.length > 0)
			ret.flags |= EventFlag.InputBuffer;

		if(buffer.length > 0)
			ret.flags |= EventFlag.RawBuffer;

		return ret;
	}


	public bool keyHit()
	{
		int ch = getch();

		if (ch != ERR) {
			ungetch(ch);
			return true;
		} else {
			return false;
		}
	}

	private EventFlag processEvent(int ev)
	{
		KeyboardEvent kret;
		MouseScrollEvent sret;
		EventFlag flags;

		switch(ev)
		{
			// dfmt off
			case KEY_BACKSPACE:
			case 127:
			case '\b':
				kret.key = Keycode.Backspace; break;
			case KEY_SEND: kret.mods = InputModifier.Shift; goto case;
			case KEY_END: kret.key = Keycode.End; break;
			case KEY_SHOME: kret.mods = InputModifier.Shift; goto case;
			case KEY_HOME: kret.key = Keycode.Home; break;
			case KEY_SF: kret.mods = InputModifier.Shift; goto case;
			case KEY_DOWN: kret.key = Keycode.Down; break;
			case KEY_SR: kret.mods = InputModifier.Shift; goto case;
			case KEY_UP: kret.key = Keycode.Up; break;
			case KEY_SLEFT: kret.mods = InputModifier.Shift; goto case;
			case KEY_LEFT: kret.key = Keycode.Left; break;
			case KEY_SRIGHT: kret.mods = InputModifier.Shift; goto case;
			case KEY_RIGHT: kret.key = Keycode.Right; break;
			case KEY_F(1): kret.key = Keycode.F1; break;
			case KEY_F(2): kret.key = Keycode.F2; break;
			case KEY_F(3): kret.key = Keycode.F3; break;
			case KEY_F(4): kret.key = Keycode.F4; break;
			case KEY_F(5): kret.key = Keycode.F5; break;
			case KEY_F(6): kret.key = Keycode.F6; break;
			case KEY_F(7): kret.key = Keycode.F7; break;
			case KEY_F(8): kret.key = Keycode.F8; break;
			case KEY_F(9): kret.key = Keycode.F9; break;
			case KEY_F(10): kret.key = Keycode.F10; break;
			case KEY_F(11): kret.key = Keycode.F11; break;
			case KEY_F(12): kret.key = Keycode.F12; break;
			case KEY_F(13): kret.key = Keycode.F13; break;
			case KEY_F(14): kret.key = Keycode.F14; break;
			case KEY_F(15): kret.key = Keycode.F15; break;
			case KEY_F(16): kret.key = Keycode.F16; break;
			case KEY_F(17): kret.key = Keycode.F17; break;
			case KEY_F(18): kret.key = Keycode.F18; break;
			case KEY_F(19): kret.key = Keycode.F19; break;
			case KEY_F(20): kret.key = Keycode.F20; break;
			case KEY_F(21): kret.key = Keycode.F21; break;
			case KEY_F(22): kret.key = Keycode.F22; break;
			case KEY_F(23): kret.key = Keycode.F23; break;
			case KEY_F(24): kret.key = Keycode.F24; break;
			case KEY_F(25): kret.key = Keycode.F25; break;
			case KEY_ENTER: kret.key = Keycode.Enter; break;
			case KEY_PPAGE: kret.key = Keycode.PageUp; break;
			case KEY_NPAGE: kret.key = Keycode.PageDown; break;
			case KEY_SIC: kret.mods = InputModifier.Shift; goto case;
			case KEY_IC: kret.key = Keycode.Insert; break;
			case KEY_SDC: kret.mods = InputModifier.Shift; goto case;
			case KEY_DC: kret.key = Keycode.Delete; break;
			case KEY_RESIZE: flags |= EventFlag.Resize; break;
			case 560: // CTRL + Up
				kret.key = Keycode.Up;
				kret.mods = InputModifier.Control;
				break;
			case 519: // CTRL + Down
				kret.key = Keycode.Down;
				kret.mods = InputModifier.Control;
				break;

			default:
				kret = processSpecialKeyEvent(ev);
			// dfmt on
		}

		if(input.keyPressedCallback !is null) input.keyPressedCallback(kret);

		return flags;
	}


	private KeyboardEvent processSpecialKeyEvent(int ev) {
		string evbuf = to!string(unctrl(ev));
		KeyboardEvent ret = KeyboardEvent(Keycode.Unknown, InputModifier.None);

		if(evbuf.length == 1 || (evbuf.length > 1 && evbuf[0]!='^'))
		{
			if(isAlpha(evbuf[0]))
			{
				string parsestr = to!string(toUpper(evbuf[0]));
				ret.key = parse!Keycode(parsestr);
			}
			input.buf ~= evbuf;
		}
		else if(evbuf == "^[")
		{
			ret.mods |= InputModifier.Alt;
			evbuf ~= to!string(unctrl(getch()));
			if(evbuf.length == 4 &&
				evbuf[2] == '^' &&
				isAlpha(evbuf[3]))
			{
				ret.mods |= InputModifier.Control;
				string parsestr = to!string(evbuf[3]);
				ret.key = parse!Keycode(parsestr);
			} else if(evbuf.length == 3 && isAlpha(evbuf[2]))
			{
				if(isUpper(evbuf[2]))
					ret.mods |= InputModifier.Shift;
				string parsestr =to!string(toUpper(evbuf[2]));
				ret.key = parse!Keycode(parsestr);
			}
		} else if(evbuf.length == 2 &&
			evbuf[0] == '^' &&
			isAlpha(evbuf[1]))
		{
			ret.mods |= InputModifier.Control;
			string parsestr =to!string(evbuf[1]);
			ret.key = parse!Keycode(parsestr);
		}
		return ret;
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

	struct Input {
		void delegate(immutable KeyboardEvent) keyPressedCallback;
		string buffer()
		{
			string ret = buf;
			buf.length = 0;
			return ret;
		}

		dchar ch()
		{
			if(buf.length > 0)
			{
				dchar ret = buf[0];
				buf = buf[1 .. $];
				return ret;
			}
			else
				return 0;
		}

		public bool isEnable = true;
		private string buf;
	}

	struct Event {
		size_t eventsProcessed;
		ubyte flags;
	}

	enum EventFlag : ubyte {
		None = 0,
		RawBuffer = 1 << 0,
		InputBuffer = 1 << 1,
		Resize = 1 << 2,
	}

	public Input input;

	private immutable OutputType outType;
	private immutable int outputDescriptor;
	private immutable int inputDescriptor;
	private string buffer;
	private bool rawMode = false;

	version(Posix) {
		private termios origTermios;
	} else version(Windows) {
		private HANDLE hConsole;
		private CONSOLE_SCREEN_BUFFER_INFO originalSbi;
	}
}
