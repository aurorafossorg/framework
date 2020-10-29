module aurorafw.cli.terminal.window;

import std.conv : to;
import std.string : fromStringz, toStringz;

import riverd.ncurses;

version (unittest) import aurorafw.unit.assertion;

struct Window
{
	this(
			int _xOrigin,
			int _yOrigin,
			int _width,
			int _height,
			Position p = Position.ORIGIN)
	{
		if (p == Position.CENTER)
			window = newwin(_height, _width, _yOrigin - _height / 2, _xOrigin - _width / 2);
		else
			window = newwin(_height, _width, _yOrigin, _xOrigin);

		setWindowValues();
	}

	~this()
	{
		delwin(window);
	}

	bool opEquals(const Window o) const
	{
		return (_xOrigin == o._xOrigin &&
				_yOrigin == o._yOrigin &&
				_width == o._width &&
				_height == o._height);
	}

	bool opEquals(const WINDOW* o) const
	{
		return (_xOrigin == getbegx(o) &&
				_yOrigin == getbegy(o) &&
				_width == getmaxx(o) &&
				_height == getmaxy(o));
	}

	void opIndexAssign(in char value, in int x, in int y)
	in
	{
		assert(x >= 0 &&
				y >= 0 &&
				x <= _width &&
				y <= _height);
	}
	do
	{
		mvwaddch(window, y, x, value);
	}

	void opIndexAssign(in string value, in int x, in int y)
	in
	{
		assert(x >= 0 &&
				y >= 0 &&
				x <= _width &&
				y <= _height);
	}
	do
	{
		mvwaddstr(window, y, x, toStringz(value));
	}

	void opIndexAssign(in char value, int[2] length, int y)
	in
	{
		assert(length[0] >= 0 &&
				length[1] <= _width &&
				y >= 0 &&
				y <= _height);
	}
	do
	{
		for (int x = length[0]; x <= length[1]; x++)
		{
			this.opIndexAssign(value, x, y);
		}
	}

	void opIndexAssign(in char value, int x, int[2] length)
	in
	{
		assert(x >= 0 &&
				x <= _width &&
				length[0] >= 0 &&
				length[1] <= _height);
	}
	do
	{
		for (int y = length[0]; y <= length[1]; y++)
		{
			this.opIndexAssign(value, x, y);
		}
	}

	void opIndexAssign(in char value, int[2] _width, int[2] _height)
	in
	{
		assert(_width[0] >= 0 &&
				_width[1] <= this._width &&
				_height[0] >= 0 &&
				_height[1] <= this._height);
	}
	do
	{
		for (int y = _height[0]; y <= _height[1]; y++)
		{
			this.opIndexAssign(value, _width, y);
		}
	}

	char opIndex(in int x, in int y)
	in
	{
		assert(x >= _xOrigin &&
				y >= _yOrigin &&
				x <= _width &&
				y <= _height);
	}
	do
	{
		return to!char(mvwinch(window, y, x) & A_CHARTEXT);
	}

	int[2] opSlice(size_t dim)(int start, int end) if (dim >= 0 && dim < 2)
	in
	{
		assert(start >= 0 && end <= this.opDollar!dim);
	}
	do
	{
		return [start, end];
	}

	string opIndex(int[2] length, int y)
	{
		const int n = length[1] - length[0];
		char[] str = new char[n + 1];
		mvwinnstr(window, y, length[0], str.ptr, cast(int)(str.length));
		return str[0 .. $ - 1].dup;
	}

	string[] opIndex(int x, int[2] length)
	{
		const int n = length[1] - length[0];
		string[] str;

		for (int y = length[0]; y < length[1]; y++)
		{
			str ~= to!(string)(to!char(mvwinch(window, y, x) & A_CHARTEXT));
		}
		return str;
	}

	string[] opIndex(int[2] _width, int[2] _height)
	{
		const int yn = _height[1] - _height[0];
		string[] matrix;

		for (int y = _height[0]; y < _height[1]; y++)
		{
			matrix ~= this.opIndex(_width, y);
		}

		return matrix;
	}

	int opDollar(size_t dim : 0)() @property
	{
		return _width;
	}

	int opDollar(size_t dim : 1)() @property
	{
		return _height;
	}

	public enum Position
	{
		ORIGIN,
		CENTER
	}

	private void setWindowValues()
	{
		wrefresh(window);
		_xOrigin = getbegx(window);
		_yOrigin = getbegy(window);
		_width = getmaxx(window);
		_height = getmaxy(window);
	}

	public char readInputCh()
	{
		return to!char(wgetch(window) & A_CHARTEXT);
	}

	public char readInputCh(int x, int y)
	{
		return to!char(mvwgetch(window, y, x) & A_CHARTEXT);
	}

	public string readInputStr()
	{
		char[] str;
		do
		{
			str ~= readInputCh();
		}
		while (str[$ - 1] != '\n' && str[$ - 1] != '\r');

		return fromStringz(str.ptr).dup;
	}

	public string readInputStr(int n)
	{
		char[] str = new char[n];
		wgetnstr(window, str.ptr, n);
		return str.dup;
	}

	public void moveWindow(int x, int y)
	{
		mvwin(window, y, x);
		setWindowValues();
	}

	public void moveCursor(int x, int y)
	{
		wmove(window, y, x);
		setWindowValues();
	}

	public void resizeWindow(int _width, int _height)
	{
		wresize(window, _height, _width);
		setWindowValues();
	}

	public void addCh(in char c)
	{
		waddch(window, c);
	}

	public void addStr(in string str)
	{
		waddstr(window, toStringz(str));
	}

	public void writeFormated(A...)(string fmt, A args)
	{
		wprintw(window, toStringz(fmt), args);
	}

	public void writeFormated(A...)(int[2] coords, string fmt, A args)
	{
		mvwprintw(window, coords[1], coords[0], toStringz(fmt), args);
	}

	public void fill(in char c)
	{
		this.opIndexAssign(c, [0, _width], [0, _height]);
	}

	public void clear()
	{
		wclear(window);
	}

	public int cursorPositionX() const @property
	{
		return getcurx(window);
	}

	public int cursorPositionY() const @property
	{
		return getcury(window);
	}

	public int[2] cursorPosition() const @property
	{
		return [cursorPositionX, cursorPositionY];
	}

	public void xOrigin(int value) @property
	{
		_xOrigin = value;
		wmove(window, _yOrigin, _xOrigin);
	}

	public void yOrigin(int value) @property
	{
		_yOrigin = value;
		wmove(window, _yOrigin, _xOrigin);
	}

	public void width(int value) @property
	{
		resizeWindow(value, _height);
	}

	public void height(int value) @property
	{
		resizeWindow(_width, value);
	}

	public int xCenter() const @property
	{
		return (_xOrigin + _width) / 2;
	}

	public int yCenter() const @property
	{
		return (_yOrigin + _height) / 2;
	}

	public int[2] xyCenter() const @property
	{
		return [xCenter, yCenter];
	}

	public int xEnd() const @property
	{
		return _xOrigin + _width;
	}

	public int yEnd() const @property
	{
		return _yOrigin + _height;
	}

	public int[2] xyEnd() const @property
	{
		return [xEnd, yEnd];
	}

	public WINDOW* window;
	private int _xOrigin, _yOrigin;
	private int _width, _height;
}

@("Window: Comparing windows")
unittest
{
	initscr();

	Window win1 = Window(5, 0, 10, 3);
	Window win2 = Window(5, 0, 10, 3);
	WINDOW* win3 = newwin(3, 10, 0, 5);

	assertTrue(win1 == win2);
	assertTrue(win2 == win3);

	endwin();
}

@("Window: Center position")
unittest
{
	initscr();

	Window win1 = Window(5, 5, 5, 5, Window.Position.CENTER);
	Window win2 = Window(3, 3, 5, 5);

	assertTrue(win1 == win2);

	assertTrue(win1.xCenter == win2.xCenter);
	assertTrue(win1.yCenter == win2.yCenter);
	assertTrue(win1.xyCenter == win2.xyCenter);

	endwin();
}

@("Window: Writing and reading")
unittest
{
	initscr();

	Window win = Window(1, 1, 13, 11);
	win[0, 0] = "Hello World";
	win[1, 2] = 'c';

	assertTrue(win[1, 2] == 'c');

	assertTrue(win[0 .. 11, 0] == "Hello World");
	assertTrue(win[1, 0 .. 3] == ["e", " ", "c"]);

	assertTrue(win[0 .. 13, 0] == win[0 .. $, 0]);

	assertTrue(win[0 .. 11, 0 .. 3] == ["Hello World",
			"           ",
			" c         "]);

	endwin();
}

@("Window: Writing formated")
unittest
{
	initscr();

	Window win = Window(0, 0, 50, 10);
	win.writeFormated([0, 0], "Hello World n. %d!", 3432);

	assertTrue(win[0 .. "Hello World n. 3432!".length, 0] == "Hello World n. 3432!");

	endwin();
}

@("Window: Writing a char n times")
unittest
{
	initscr();

	Window win = Window(0, 0, 10, 10);

	win[0 .. 2, 0] = 'H';
	win[0, 1 .. 3] = 'T';
	win[5 .. $, 5 .. $] = 'O';

	assertTrue(win[0 .. 3, 0] == "HHH");
	assertTrue(win[0, 1 .. 4] == ["T", "T", "T"]);
	assertTrue(win[5 .. $, 5 .. $] == ["OOOOO",
			"OOOOO",
			"OOOOO",
			"OOOOO",
			"OOOOO"]);

	endwin();
}

@("Window: Resizing and moving")
unittest
{
	initscr();

	Window win = Window(0, 0, 5, 5);

	win.resizeWindow(10, 10);
	assertTrue(win == Window(0, 0, 10, 10));

	win.moveWindow(2, 3);
	assertTrue(win == Window(2, 3, 10, 10));

	endwin();
}

@("Window: Cursor movement")
unittest
{
	initscr();

	Window win = Window(0, 0, 10, 10);
	win.moveCursor(5, 7);
	assertTrue(win.cursorPosition == [5, 7]);

	endwin();
}

@("Window: Adding a string or char")
unittest
{
	initscr();

	Window win = Window(0, 0, 10, 10);
	win.addCh('c');
	assertTrue(win[0, 0] == 'c');

	win.addStr("string");
	assertTrue(win[0 .. 6, 0] == "string");

	endwin();
}

@("Window: Fill and clear")
unittest
{
	initscr();

	Window win = Window(0, 0, 3, 3);

	assertTrue(win[0 .. $, 0 .. $] == ["   ",
			"   ",
			"   "]);

	win.fill('F');
	assertTrue(win[0 .. $, 0 .. $] == ["FFF",
			"FFF",
			"FFF"]);

	win.clear();
	assertTrue(win[0 .. $, 0 .. $] == ["   ",
			"   ",
			"   "]);

	endwin();
}

@("Window: Change a single value")
unittest
{
	initscr();

	Window win = Window(0, 0, 10, 10);
	win.xOrigin = 5;
	win.yOrigin = 8;

	assertTrue(win == Window(5, 8, 10, 10));

	win.width = 25;
	win.height = 15;

	assertTrue(win == Window(0, 0, 25, 15));

	assertTrue(win.xEnd == 25);
	assertTrue(win.yEnd == 15);
	assertTrue(win.xyEnd == [25, 15]);

	endwin();
}
