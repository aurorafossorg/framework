/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2018-2020 Aurora Free Open Source Software.
Copyright (C) 2018-2020 Luís Ferreira <luis@aurorafoss.org>

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
http://www.gnu.org/licenses/gpl-3.0.html.

NOTE: All products, services or anything associated to trademarks and
service marks used or referenced on this file are the property of their
respective companies/owners or its subsidiaries. Other names and brands
may be claimed as the property of others.

For more info about intellectual property visit: aurorafoss.org or
directly send an email to: contact (at) aurorafoss.org .

This file has code provided on dlang forum and on bolts package check them out
here: https://forum.dlang.org/post/gdipbdsoqdywuabnpzpe@forum.dlang.org and at
code.dlang.org or even https://github.com/aliak00/bolts/ .
*/

/++
Extras to object module

This file defines extra functions to object module.

Authors: Luís Ferreira <luis@aurorafoss.org>
Copyright: All rights reserved, Aurora Free Open Source Software
License: GNU Lesser General Public License (Version 3, 29 June 2007)
Date: 2018-2020
+/
module aurorafw.stdx.object;

import std.traits;
import std.meta;

import aurorafw.stdx.traits;

version(unittest) import aurorafw.unit.assertion;

public template match(handlers...) {
	MatchReturnType!handlers match(T)(auto ref T obj)
		if(is(T == class) || is(T == interface))
	{
		alias TL = staticMap!(Unqual,staticMap!(FunctionTypeOf, handlers));
		static assert(is(NoDuplicates!(TL) == TL));

		enum CompParams(alias H1, alias H2) = Parameters!H1.length > Parameters!H2.length;
		alias matchReturnType = typeof(return);
		alias sortedHandlers = AliasSeq!(
			staticSort!(CompParams, handlers),
			// default if everything fails
			() => matchReturnType.init);
		foreach(handler; sortedHandlers)
		{
			alias paramsHandler = Parameters!handler;
			static assert(paramsHandler.length <= 1);
			static if(paramsHandler.length == 1)
			{
				alias firstParam = Parameters!handler[0];

				// runtime verifications
				if(typeid(obj) == typeid(firstParam))
					return handler(cast(firstParam) obj);
			}
			else static if(paramsHandler.length == 0) {
				return handler();
			}
		}
	}
}

private version(unittest)
{
	// dfmt off
	@safe pure
	class UnittestFoobar {}

	@safe pure
	class UnittestFoo : UnittestFoobar {}

	@safe pure
	class UnittestBar : UnittestFoobar {}
	// dfmt on
}

public enum from = FromImpl!()();

public template _from(string moduleName = null)
{
	enum _from = FromImpl!(moduleName)();
}


private struct FromImpl(string moduleName = null) {
    template opDispatch(string symbolName) {
        static if (ModuleContainsSymbol!(moduleName, symbolName)) {
            mixin("import ", moduleName,";");
            mixin("alias opDispatch = ", symbolName, ";");
        } else {
            static if (moduleName.length == 0) {
                enum opDispatch = FromImpl!(symbolName)();
            } else {
                enum importString = moduleName ~ "." ~ symbolName;
                static assert(
                    CanImport!importString,
                    "Symbol \"" ~ symbolName ~ "\" not found in " ~ moduleName
                );
                enum opDispatch = FromImpl!importString();
            }
        }
    }
}

///
@safe pure
@("Object: from opDispatch sugar")
unittest {
	assertTrue(__traits(compiles, { _from!"std.math".abs(-1); }));
	assertTrue(__traits(compiles, { _from!().std.math.abs(-1); }));
	assertTrue(__traits(compiles, { from.std.math.abs(-1); }));
	assertTrue(__traits(compiles, { _from!"std.math".abs(-1); }));
	assertFalse(__traits(compiles, { from.std.math.thisFunctionDoesNotExist(42); }));
	assertFalse(__traits(compiles, { _from!"std.math".thisFunctionDoesNotExist(42); }));

	// check for static eval
	static assert(__traits(compiles, { _from!"std.math".abs(-1); }));
	static assert(__traits(compiles, { from.std.math.abs(-1); }));

	// test if it actually imports the right symbol
	assertEquals(1, from.std.math.abs(-1));
}

///
@system
@("Object: Type pattern matching")
unittest
{
	UnittestFoobar foo = new UnittestFoo();
	assertEquals("yes", foo.match!(
		(UnittestFoo _) => "yes", (UnittestBar _) => "bar", () => "no"
	));

	Object bar = new UnittestBar();
	assertEquals("yes", bar.match!(
		(UnittestBar _) => "yes", () => "no"
	));

	assertEquals(bar, bar.match!(
		(UnittestBar _) => _, () => null
	));

	assertEquals(null, bar.match!( (UnittestFoo _) => _ ));
}
