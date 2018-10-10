module aurorafw.core.dylib;

import std.array;
import std.string;

struct DylibVersion
{
	uint major;
	uint minor;
	uint patch;
}

class DylibLoadException : Exception {
	this(string msg, size_t line = __LINE__, string file = __FILE__)
	{
		super(msg, file, line, null);
	}

	this(string[] names, string[] reasons, size_t line = __LINE__, string file = __FILE__)
	{
		string msg = "Failed to load one or more shared libraries:";
		foreach(i, name; names) {
			msg ~= "\n\t" ~ name ~ " - ";
			if(i < reasons.length)
				msg ~= reasons[i];
			else
				msg ~= "Unknown";
		}
		this(msg, line, file);
	}

	this(string msg, string name = "", size_t line = __LINE__, string file = __FILE__)
	{
		super(msg, file, line, null);
		_name = name;
	}

	pure nothrow @nogc
	@property string name()
	{
		return _name;
	}
	private string _name;
}

class DylibSymbolLoadException : Exception {
	this(string msg, size_t line = __LINE__, string file = __FILE__) {
		super(msg, file, line, null);
	}
	
	this(string lib, string symbol, size_t line = __LINE__, string file = __FILE__)
	{
		_lib = lib;
		_symbol = symbol;
		this("Failed to load symbol " ~ symbol ~ " from shared library " ~ lib, line, file);
	}

	@property string lib()
	{
		return _lib;
	}

	@property string symbol()
	{
		return _symbol;
	}

private:
	string _lib;
	string _symbol;
}

pure struct Dylib
{
	version(Posix) import core.sys.posix.dlfcn;
	else version(Windows) import core.sys.windows.windows;
	void load(string[] names)
	{
		if(isLoaded)
			return;

		string[] fnames;
		string[] freasons;

		foreach(name; names)
		{
			version(Posix) _handle = dlopen(_name.toStringz(), RTLD_NOW);
			if(isLoaded) {
				_name = name;
				break;
			}

			fnames ~= name;
			
			import std.conv : to;

			version(Posix) {
				string err = to!string(dlerror());
				if(err is null)
					err = "Unknown error";
			}
			else version(Windows)
			{
				import std.windows.syserror;
				string err = sysErrorString(GetLastError());
			}

			freasons ~= err;
		}
		if(!isLoaded)
			throw new DylibLoadException(fnames, freasons);
	}

	void* loadSymbol(string name, bool required = true)
	{
		version(Posix) void* sym = dlsym(_handle, name.toStringz());
		else version(Windows) void* sym = GetProcAddress(_handle, name.toStringz());

		if(required && !sym)
		{
			if(_callback !is null)
				required = _callback(name);
			if(required)
				throw new DylibSymbolLoadException(_name, name);
		}

		return sym;
	}

	void unload()
	{
		if(isLoaded)
		{
			version(Posix) dlclose(_handle);
			else version(Windows) FreeLibrary(_handle);
			_handle = null;
		}
	}

	@property bool isLoaded()
	{
		return _handle !is null;
	}

	@property bool delegate(string) missingSymbolCallback()
	{
		return _callback;
	}

	@property void missingSymbolCallback(bool delegate(string) callback)
	{
		_callback = callback;
	}

	@property void missingSymbolCallback(bool function(string) callback)
	{
		import std.functional : toDelegate;
		_callback = toDelegate(callback);
	}

private:
	string _name;
	void* _handle;
	bool delegate(string) _callback;
}

abstract class DylibLoader
{
	this(string libs)
	{
		string[] libs_ = libs.split(",");
		foreach(ref string l; libs_)
			l = l.strip();
		this(libs_);
	}

	this(string[] libs)
	{
		_libs = libs;
		dylib.load(_libs);
		loadSymbols();
	}

	final this(string[] libs, DylibVersion ver)
	{
		configureMinimumVersion(ver);
		this(libs);
	}

	final this(string libs, DylibVersion ver)
	{
		configureMinimumVersion(ver);
		this(libs);
	}

	protected void loadSymbols() {}

	protected void configureMinimumVersion(DylibVersion minVersion)
	{
		assert(0, "DylibVersion is not supported by this loader.");
	}

	protected final void bindFunc(void** ptr, string name, bool required = true)
	{
		void* func = dylib.loadSymbol(name, required);
		*ptr = func;
	}

	@property final string[] libs()
	{
		return _libs;
	}

	Dylib dylib;
	private string[] _libs;
}