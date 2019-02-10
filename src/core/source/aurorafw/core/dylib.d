/*
									__
								   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright © 2013-2016, Mike Parker.
Copyright © 2016, 渡世白玉.
Copyright © 2018-2019, Aurora Free Open Source Software.

This file is part of the Aurora Free Open Source Software. This
organization promote free and open source software that you can
redistribute and/or modify under the terms of the GNU Lesser General
Public License Version 3 as published by the Free Software Foundation or
(at your option) any later version approved by the Aurora Free Open Source
Software Organization. The license is available in the package root path
as 'LICENSE' file. Please review the following information to ensure the
GNU Lesser General Public License version 3 requirements will be met:
https://www.gnu.org/licenses/lgpl.html .

Alternatively, this file may be used under the terms of the GNU General
Public License version 3 or later as published by the Free Software
Foundation. Please review the following information to ensure the GNU
General Public License requirements will be met:
https://www.gnu.org/licenses/gpl-3.0.html.

NOTE: All products, services or anything associated to trademarks and
service marks used or referenced on this file are the property of their
respective companies/owners or its subsidiaries. Other names and brands
may be claimed as the property of others.

For more info about intellectual property visit: aurorafoss.org or
directly send an email to: contact (at) aurorafoss.org .

This file is an improvement of an existing code, part of DerelictUtil
from DerelictOrg. Check it out at derelictorg.github.io .

This file is an improvement of an existing code, developed by 渡世白玉
and available on github at https://github.com/huntlabs/DerelictUtil .
*/

module aurorafw.core.dylib;

import std.array;
import std.string;
import std.traits;

version(Posix) import core.sys.posix.dlfcn;
else version(Windows) import core.sys.windows.windows;


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
	void load(string[] names)
	{
		if(isLoaded)
			return;

		string[] fnames;
		string[] freasons;

		foreach(name; names)
		{
			import std.stdio;
			import std.conv;

			version(Posix) _handle = dlopen(name.toStringz(), RTLD_NOW);
			else version(Windows) _handle = LoadLibraryA(name.toStringz());
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

	protected final void bindFunc(TFUN)(ref TFUN fun, string name, bool required = true)
		if(isFunctionPointer!(TFUN))
	{
		void* func = dylib.loadSymbol(name, required);
		fun = cast(TFUN)func;
	}

	protected final void bindFunc_stdcall(Func)(ref Func f, string unmangledName)
	{
		version(Win32) {
			import std.format : format;
			import std.traits : ParameterTypeTuple;

			// get type-tuple of parameters
			ParameterTypeTuple!f params;

			size_t sizeOfParametersOnStack(A...)(A args)
			{
				size_t sum = 0;
				foreach (arg; args) {
					sum += arg.sizeof;

					// align on 32-bit stack
					if (sum % 4 != 0)
						sum += 4 - (sum % 4);
				}
				return sum;
			}
			unmangledName = format("_%s@%s", unmangledName, sizeOfParametersOnStack(params));
		}
		bindFunc(cast(void**)&f, unmangledName);
	}

	@property final string[] libs()
	{
		return _libs;
	}

	Dylib dylib;
	private string[] _libs;
}

template DylibBuildLoadSymbols(alias T, bool required = false)
{
	string _buildLoadSymbols(alias T, bool required = false)()
	{
		static if(required)
			enum dthrow = "true";
		else
			enum dthrow = "false";

		string bindlist = "\n{";
		foreach(mem; __traits(derivedMembers, T))
		{
			static if( isFunctionPointer!(__traits(getMember, T, mem)) /*&& !is(typeof(__traits(getMember, T, mem)) == immutable)*/)
			{
				bindlist ~= "\tbindFunc(" ~ mem ~ ", \"" ~ mem ~ "\", " ~ dthrow ~ ");\n";
			}
		}
		bindlist ~= "}";
		return bindlist;
	}

	enum DylibBuildLoadSymbols = _buildLoadSymbols!(T, required)();
}