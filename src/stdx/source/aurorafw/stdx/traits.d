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

This file has code parts from 'bolts' package.
Check out the project here: https://github.com/aliak00/bolts/ .
*/

/++
Extras to std.traits

This file defines extra functions to std.traits.

Authors: Luís Ferreira <luis@aurorafoss.org>
Copyright: All rights reserved, Aurora Free Open Source Software
License: GNU Lesser General Public License (Version 3, 29 June 2007)
Date: 2018-2019
+/
module aurorafw.stdx.traits;

public import std.traits;

import std.format;
import std.meta;

version(unittest) import aurorafw.unit.assertion;


/**
 * Detect version identifiers
 *
 * This is a template to check if a version
 * identifier is available.
 *
 * Examples:
 * --------------------
 * static if(isVersion!"unittest")
 * {
*      // code with version unittest ...
 * }
 * --------------------
 */
template isVersion(string ver) {
	mixin(format(q{
		version(%s) {
			enum isVersion = true;
		}
		else {
			enum isVersion = false;
		}
	}, ver));
}


///
@safe pure
@("Traits: isVersion")
unittest
{
	assertTrue(isVersion!"unittest");
	assertFalse(isVersion!"this_shouldnt_be_a_version_identifier");
}

/**
 * Match functions return type
 *
 * This template match the return type of the passed functions
 * and fail if there's more than one type (except typeof(null))
 */
template MatchReturnType(funcs...) if (allSatisfy!(isSomeFunction, funcs)) {
	alias types = NoDuplicates!(staticMap!(Unqual, staticMap!(ReturnType, funcs)));
	static assert(types.length == 1 || (types.length == 2 && is(types[1] == typeof(
			null))));

	alias MatchReturnType = types[0];
}

///
@safe pure
@("Traits: MatchReturnType")
unittest
{
	alias TL_1 = MatchReturnType!(void delegate(), void function(), void function(string foo));
	assertTrue(is(TL_1 == void));
	assertFalse(is(TL_1 == string));

	alias TL_2 = MatchReturnType!(string delegate(), string function(), string function(int foo), () => null);
	assertTrue(is(TL_2 == string));
	assertTrue(is(MatchReturnType!(()=> "atum") == string));
}

version(unittest)
{
	private interface IUnittestTestClass {}
	private class UnittestTestClass {}
	private struct UnittestTestStruct {}
}

/**
 * Checks if type is typeof(null)
 * Params:
 *   T = type or typeof a variable for null check
 */
template isNullType(alias T) {
	enum isNullType = is(typeof(T) == typeof(null));
}

///
@safe pure
@("Traits: isNullType")
unittest {
	int a;
    int *b = null;
    UnittestTestStruct c;
    void f() {}

    assertTrue(isNullType!null);

    assertFalse(isNullType!a);
    assertFalse(isNullType!b);
    assertFalse(isNullType!c);
    assertFalse(isNullType!f);
}

/**
 * Checks if type is null testable
 *
 * Params:
 *   T = type or typeof a variable
 */
template isNullTestable(alias T) {
	enum isNullTestable = __traits(compiles, {
			if (T.init is null) {
			}
		});
}

///
@safe pure
@("Traits: isNullTestable")
unittest {
	class Class1 {}
    struct Struct1 {
        void opAssign(int*) {}
    }
    assertFalse(isNullTestable!Struct1);
    assertTrue(isNullTestable!Class1);
    assertTrue(isNullTestable!(int*));

    assertFalse(isNullTestable!UnittestTestStruct);
    assertFalse(isNullTestable!int);

    class Class2 {
        @disable this();
    }
    assertTrue(isNullTestable!Class2);
}

/**
 * Checks if type is settable to null
 * Params:
 *   T = type or typeof a variable
 */
template isNullSettable(alias T) {
	enum isNullSettable = __traits(compiles, { typeof(T.init) t = T.init; t = null; });
}

///
@safe pure
@("Traits: isNullSettable")
unittest
{
	assertTrue(isNullSettable!IUnittestTestClass);
	assertTrue(isNullSettable!UnittestTestClass);
	assertTrue(isNullSettable!(int[]));
	assertTrue(isNullSettable!(int[string]));
	assertTrue(isNullSettable!(typeof(null)));
	assertTrue(isNullSettable!(int*));
	assertTrue(isNullSettable!(void function()));
	assertTrue(isNullSettable!(void delegate()));

	assertFalse(isNullSettable!int);
	assertFalse(isNullSettable!float);
	assertFalse(isNullSettable!double);
	assertFalse(isNullSettable!bool);
	assertFalse(isNullSettable!real);
	assertFalse(isNullSettable!UnittestTestStruct);

	struct Struct1 {
        void opAssign(int*) {}
    }
    assertTrue(isNullSettable!Struct1);

	struct Struct3 {
        @disable this();
        void opAssign(int*) {}
    }
    assertTrue(isNullSettable!Struct3);
}

template TypesOf(Symbols...) {
    import std.meta: AliasSeq;
    static if (Symbols.length) {
        static if (isFunction!(Symbols[0]) && is(typeof(&Symbols[0]) F)) {
            alias T = F;
        } else static if (is(typeof(Symbols[0]))) {
            alias T = typeof(Symbols[0]);
        } else {
            alias T = Symbols[0];
        }
        alias TypesOf = AliasSeq!(T, TypesOf!(Symbols[1..$]));
    } else {
        alias TypesOf = AliasSeq!();
    }
}


///
@safe pure
@("Traits: TypesOf")
unittest {
    assertTrue(is(TypesOf!("foo", 42U, 24, 123.0, float) == AliasSeq!(string, uint, int, double, float)));
	assertTrue(is(TypesOf!(null) == AliasSeq!(typeof(null))));
	assertTrue(is(TypesOf!("foobar") == AliasSeq!(string)));

	// check for static eval
	static assert(is(TypesOf!("foobar") == AliasSeq!(string)));
}


template CanImport(string moduleName) {
    enum CanImport = __traits(compiles, { mixin("import ", moduleName, ";"); });
}


///
@safe pure
@("Traits: CanImport")
unittest
{
	assertTrue(CanImport!"std.stdio");
	// check for static eval
	static assert(CanImport!"std.stdio");

	assertFalse(CanImport!"this.module.doesnt.exists.dont.create.it");
}

template ModuleContainsSymbol(string moduleName, string symbolName) {
    enum ModuleContainsSymbol = CanImport!moduleName && __traits(compiles, {
        mixin("import ", moduleName, ":", symbolName, ";");
    });
}


///
@safe pure
@("Traits: ModuleContainsSymbol")
unittest
{
	assertTrue(ModuleContainsSymbol!("std.stdio", "writeln"));
	assertFalse(ModuleContainsSymbol!("std.stdio", "thissymboldoesntactuallyexist"));

	// check for static eval
	static assert(ModuleContainsSymbol!("std.stdio", "writeln"));
}


template isOf(ab...) if (ab.length == 2) {
    alias Ts = TypesOf!ab;
    template resolve(T) {
        import std.traits: isCallable, ReturnType;
        static if (isCallable!T) {
            alias resolve = ReturnType!T;
        } else {
            alias resolve = T;
        }
    }

    enum isOf = is(resolve!(Ts[0]) == resolve!(Ts[1]));
}

///
@safe pure
@("Traits: isOf")
unittest {
    assertTrue(isOf!(int, 3));
    assertTrue(isOf!(7, 3));
    assertTrue(isOf!(3, int));
    assertFalse(isOf!(float, 3));
    assertFalse(isOf!(float, string));
    assertFalse(isOf!(string, 3));

    string foobar() { return ""; }
    assertTrue(isOf!(string, foobar));

	// check static eval
	static assert(isOf!(string, foobar));
}


template isSame(symbols...) if (symbols.length == 2) {

    private static template expectType(T) {}
    private static template expectBool(bool b) {}

    static if (__traits(compiles, expectType!(symbols[0]), expectType!(symbols[1]))) {
        enum isSame = is(symbols[0] == symbols[1]);
    } else static if (!__traits(compiles, expectType!(symbols[0]))
        && !__traits(compiles, expectType!(symbols[1]))
        && __traits(compiles, expectBool!(symbols[0] == symbols[1]))
    ) {
        static if (!__traits(compiles, &symbols[0]) || !__traits(compiles, &symbols[1]))
            enum isSame = (symbols[0] == symbols[1]);
        else
            enum isSame = __traits(isSame, symbols[0], symbols[1]);
    } else {
        enum isSame = __traits(isSame, symbols[0], symbols[1]);
    }
}


///
@safe pure
@("Traits: isSame")
unittest {
    assertTrue(isSame!(int, int));
    assertFalse(isSame!(int, short));

    enum a = 1, b = 1, c = 2, s = "a", t = "a";
    assertTrue(isSame!(1, 1));
    assertTrue(isSame!(a, 1));
    assertTrue(isSame!(a, b));
    assertFalse(isSame!(b, c));
    assertTrue(isSame!("a", "a"));
    assertTrue(isSame!(s, "a"));
    assertTrue(isSame!(s, t));
    assertFalse(isSame!(s, "g"));
    assertFalse(isSame!(1, "1"));
    assertFalse(isSame!(a, "a"));
    assertTrue(isSame!(isSame, isSame));
    assertFalse(isSame!(isSame, a));

    assertFalse(isSame!(byte, a));
    assertFalse(isSame!(short, isSame));
    assertFalse(isSame!(a, int));
    assertFalse(isSame!(long, isSame));

    static immutable X = 1, Y = 1, Z = 2;
    assertTrue(isSame!(X, X));
    assertFalse(isSame!(X, Y));
    assertFalse(isSame!(Y, Z));

    int foo();
    int bar();
    real baz(int);
    assertTrue(isSame!(foo, foo));
    assertFalse(isSame!(foo, bar));
    assertFalse(isSame!(bar, baz));
    assertTrue(isSame!(baz, baz));
    assertFalse(isSame!(foo, 0));

    int x, y;
    real z;
    assertTrue(isSame!(x, x));
    assertFalse(isSame!(x, y));
    assertFalse(isSame!(y, z));
    assertTrue(isSame!(z, z));
    assertFalse(isSame!(x, 0));
}
