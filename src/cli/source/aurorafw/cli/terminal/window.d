module aurorafw.cli.terminal.window;

import aurorafw.cli.terminal.terminal;

import riverd.ncurses;

import std.exception;

class TerminalWindowException : Exception {
	mixin basicExceptionCtors;
}

@safe
class TerminalWindow {

	@trusted
	this(TerminalWindow twin)
	{
		win = dupwin(twin.win);

		if(win is null)
			throw new TerminalWindowException("fail duplicating the window");
	}

	@trusted
	public this(int rows, int cols, int x, int y)
	{
		win = newwin(rows, cols, y, x);
		box(win, 0, 0);

		if (win is null)
			throw new TerminalWindowException("fail creating new window");
	}

	@trusted
	public this(WINDOW* parent, int rows, int cols, int x, int y)
	{
		if (parent is null)
			throw new TerminalWindowException("null WINDOW*");

		win = subwin(parent, rows, cols, y, x);

		if(win is null)
			throw new TerminalWindowException("fail creating a new subwindow");
	}

	@trusted
	~this()
	{
		delwin(win);
	}

	@trusted
	public void draw()
	{
		wrefresh(win);
	}


	pragma(inline, true) @trusted
	final public int resize(int rows, int cols)
	{
		return wresize(win, rows, cols);
	}


	pragma(inline, true) @trusted
	final public int move(int x, int y)
	{
		return mvwin(win, y, x);
	}

	private WINDOW* win;
}
