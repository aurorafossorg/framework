/*
									__
								   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2018 Ali Akhtarzada
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

This file has code parts from 'optional' package which is distributed
under MIT License.
Check out the project here: https://github.com/aliak00/optional/
*/

/++
Extras to std.typecons

This file defines extra functions to std.typecons.

Authors: Luís Ferreira <luis@aurorafoss.org>
Copyright: All rights reserved, Aurora Free Open Source Software
License: GNU Lesser General Public License (Version 3, 29 June 2007)
Date: 2018-2020
+/
module aurorafw.stdx.typecons;

public import std.typecons;

import std.range;
import std.format : singleSpec, FormatSpec, formatValue;

import aurorafw.stdx.object;
import aurorafw.stdx.traits;

version (unittest) import aurorafw.unit.assertion;

/**
 * Pattern matching for Nullable and Optional types
 *
 * Example:
 * ---
 * Optional!int foo = 7;
 *
 * foo.match!(
 *     (int value) => true,
 *     () => false
 * ); // true
 * ---
 */
public template match(handlers...) if (handlers.length <= 2 && handlers.length >= 1)
{
	MatchReturnType!handlers match(T)(auto ref T t)
			if (__traits(isSame, TemplateOf!T, Nullable) || __traits(isSame, TemplateOf!T, Optional))
	{
		static if (is(typeof(handlers[0](t.get))))
		{
			alias someHandler = handlers[0];
			alias noHandler = handlers[1];
		}
		else
		{
			alias someHandler = handlers[1];
			alias noHandler = handlers[0];
		}

		static if (__traits(isSame, TemplateOf!T, Nullable))
		{
			// Nullable type
			if (t.isNull)
				return noHandler();
			else
				return someHandler(t.get());
		}
		else
		{
			// Optional type
			if (!t.defined)
				return noHandler();
			else
				return someHandler(t.get());
		}

	}
}

///
@safe pure
@("Optional: pattern matching")
unittest
{
	immutable Optional!int foo = 7;
	immutable Optional!int bar;

	// dfmt off
	assertTrue(foo.match!(
		(int value) => true, () => false
	));

	assertFalse(bar.match!(
		(int value) => true, () => false
	));
	// dfmt on
}

///
@safe pure
@("Nullable: pattern matching")
unittest
{
	immutable Nullable!int foo = 7;
	immutable Nullable!int bar;

	// dfmt off
	assertTrue(foo.match!(
		(int value) => true, () => false
	));

	assertFalse(bar.match!(
		(int value) => true, () => false
	));
	// dfmt on
}

template isOptional(T)
{
	import std.traits : isInstanceOf;

	enum isOptional = isInstanceOf!(Optional, T);
}

/**
 * Defines an optional type
 *
 * Optional values are values that can be or not defined.
 *
 * Examples:
 * ---
 * Optional!int foo; // undefined
 * foo = 7; // now its defined to 7
 *
 * // can also be undefined again
 * foo.popFront();
 * ---
 */
struct Optional(T)
{

	private static string autoReturn(string expression)()
	{
		return `
			auto ref expr() {
				return `
			~ expression ~ `;
			}`
			~ q{
			alias R = typeof(expr());
			static if (!is(R == void))
				return empty ? none!R : some!R(expr());
			else {
				if (!empty) {
					expr();
				}
			}
		};
	}

	private enum isNullInvalid = is(T == class) || is(T == interface)
		|| isSomeFunction!T || isPointer!T
		|| is(T == typeof(null));

	private enum definedIfNotNull = q{
		static if (isNullInvalid)
			this._defined = this.value.payload !is null;
		else
			this._defined = true;
	};

	private union DontCallDestructorT
	{
		T payload;
	}

	private DontCallDestructorT value = DontCallDestructorT.init;
	private bool _defined = false;

	/**
	 * Constructs an optional type with a defined given value
	 *
	 * Params:
	 *   value = given value
	 */
	this(T value)
	{
		import std.traits : isCopyable;

		static if (!isCopyable!T)
		{
			import std.functional : forward;

			this.value.payload = forward!value;
		}
		else
		{
			this.value.payload = value;
		}

		mixin(definedIfNotNull);
	}

	/**
	 * Constructs an optional type with a non defined value
	 * Params:
	 *   None = None type, empty data
	 */
	this(const None)
	{
		this.value = DontCallDestructorT.init;
	}

	static if (is(T == struct) && hasElaborateDestructor!T)
	{
		/**
		 * Distructs the optional object
		 */
		~this()
		{
			if (this._defined)
			{
				destroy(value.payload);
			}
		}
	}

	/**
	 * Check if the optional type is empty
	 *
	 * Returns: true if the value is not defined, false otherwise
	 *
	 * See_Also: defined()
	 */
	@property bool empty() const
	{
		return !this.defined;
	}

	/**
	 * Check if the optional type is defined
	 *
	 * Returns: true if the value is defined, false otherwise
	 *
	 * See_Also: empty()
	 */
	@property bool defined() const
	{
		return this._defined;
	}

	/**
	 * Attemp to get the defined value
	 *
	 * Returns: if defined, the defined value, assert otherwise
	 */
	@property ref inout(T) front() inout
	{
		assert(defined, "Attempting to get an undefined optional.");
		return this.value.payload;
	}

	/// ditto
	@property ref inout(T) get() inout
	{
		return front;
	}

	/**
	 * Gets the optional value or fallback if no value defined
	 *
	 * Params:
	 *   fallback = fallback value if not defined
	 *
	 * Returns: if defined, the value, fallback value otherwise
	 */
	@property inout(T) getOr()(inout(T) fallback) inout
	{
		return defined ? value.payload : fallback;
	}

	/// ditto
	@property auto getOr(U)(inout(U) fallback) inout
	{
		return defined ? value.payload : fallback;
	}

	/**
	 * Mark this optional as undefined
	 */
	void popFront()
	{
		this._defined = false;
	}

	/**
	 * Compares this optional with an empty None value
	 *
	 * This will basically tells whether the optional is empty or not.
	 *
	 * Params:
	 *   None = None type, empty data
	 * Returns: true if there's a defined value, false otherwise
	 */
	bool opEquals(const None) const
	{
		return this.empty;
	}

	/**
	 * Compares this optional with another optional for equality
	 *
	 * Params:
	 *   rhs = right-hand side optional value
	 *
	 * Returns: true if equal, false otherwise
	 */
	bool opEquals(U : T)(const auto ref Optional!U rhs) const
	{
		if ((this.empty || rhs.empty))
			return this.empty == rhs.empty;

		static if (is(U == class))
		{
			return this.value.payload is rhs.value.payload;
		}
		else
		{
			return this.value.payload == rhs.value.payload;
		}
	}

	/**
	 * Compares this optional with a nullable for equality
	 *
	 * Params:
	 *   rhs = right-hand side nullable value
	 *
	 * Returns: true if equal, false otherwise
	 */
	bool opEquals(U : T)(auto ref Nullable!U rhs) const
	{
		return (this.empty || rhs.isNull)
			? this.empty == rhs.isNull : this.value.payload == rhs.get;
	}

	/**
	 * Compares this optional with a value for equality
	 *
	 * Params:
	 *   rhs = right-hand side value
	 *
	 * Returns: true if equal, false otherwise
	 */
	bool opEquals(U : T)(const auto ref U rhs) const
	{
		static if (is(U == class) && is(T == class))
		{
			return defined && this.value.payload is rhs;
		}
		else
		{
			return defined && this.value.payload == rhs;
		}
	}

	/**
	 * Compare this optional with an input range for equality
	 *
	 * Params:
	 *   rhs = right-hand side value
	 *
	 * Returns: true if equal, false otherwise
	 */
	bool opEquals(R)(auto ref R rhs) const
	if (isInputRange!R)
	{
		if (this.empty && rhs.empty)
			return true;
		if (this.empty || rhs.empty)
			return false;

		return this.front == rhs.front;
	}

	/**
	 * Assign this optional to a none
	 *
	 * Params:
	 *   None = None type, empty data
	 */
	auto ref opAssign()(const None) if (isMutable!T)
	{
		if (!empty)
		{
			static if (isNullInvalid)
			{
				this.value.payload = null;
			}
			else
			{
				destroy(this.value.payload);
			}
			this._defined = false;
		}
		return this;
	}

	/**
	 * Assign this optional to a value
	 *
	 * Params:
	 *   lhs = left-hand value
	 */
	auto ref opAssign(U : T)(auto ref U lhs) if (isMutable!T && isAssignable!(T, U))
	{
		import std.algorithm.mutation : moveEmplace, move;

		auto copy = DontCallDestructorT(lhs);

		if (empty)
		{
			// trusted since payload is known to be T.init here.
			() @trusted { moveEmplace(copy.payload, value.payload); }();
		}
		else
		{
			move(copy.payload, value.payload);
		}

		mixin(definedIfNotNull);
		return this;
	}

	/**
	 * Assign this optional to another optional
	 *
	 * Params:
	 *   lhs = left-hand optional value
	 */
	auto ref opAssign(U : T)(auto ref Optional!U lhs) if (isMutable!T && isAssignable!(T, U))
	{
		static if (__traits(isRef, lhs) || !isMutable!U)
		{
			this.value.payload = lhs.value.payload;
		}
		else
		{
			import std.algorithm : move;

			this.value.payload = move(lhs.value.payload);
		}

		this._defined = lhs._defined;
		return this;
	}

	/**
	 * Unary operator with auto return type
	 */
	auto opUnary(string op, this This)()
	{
		mixin(autoReturn!(op ~ "front"));
	}

	/**
	 * Binary operator with auto return types
	 *
	 * Params:
	 *   rhs = right-hand value
	 */
	auto opBinary(string op, U:
			T, this This)(auto ref U rhs)
	{
		mixin(autoReturn!("front" ~ op ~ "rhs"));
	}

	/**
	 * Binary operator with auto return types
	 *
	 * Params:
	 *   lhs = left-hand value
	 */
	auto opBinaryRight(string op, U:
			T, this This)(auto ref U lhs)
	{
		mixin(autoReturn!("lhs" ~ op ~ "front"));
	}

	/**
	 * Call operator with auto return types
	 *
	 * Params:
	 *   args = passed arguments
	 */
	auto opCall(Args...)(Args args) if (from.std.traits.isCallable!T)
	{
		mixin(autoReturn!(q{this._value(args)}));
	}

	/**
	 * Op Assign operator with auto return types
	 * Params:
	 *   rhs = right-hand value
	 */
	auto opOpAssign(string op, U:
			T, this This)(auto ref U rhs)
	{
		mixin(autoReturn!("front" ~ op ~ "= rhs"));
	}

	static if (isArray!T)
	{

		/**
		 * Index operator with auto return types
		 *
		 * Params:
		 *   index = given index of the array
		 */
		auto opIndex(this This)(size_t index)
		{
			enum call = "front[index]";
			import std.range : ElementType;

			if (empty || index >= front.length || index < 0)
			{
				return none!(mixin("typeof(" ~ call ~ ")"));
			}
			mixin(autoReturn!(call));
		}

		/**
		 * Index operator with auto return types
		 */
		auto opIndex(this This)()
		{
			mixin(autoReturn!("front[]"));
		}

		/**
		 * Slice operator with auto return types
		 *
		 * Params:
		 *   begin = begin index of the array slice
		 *   end = end index of the array slice
		 */
		auto opSlice(this This)(size_t begin, size_t end)
		{
			enum call = "front[begin .. end]";
			import std.range : ElementType;

			if (empty || begin > end || end > front.length)
			{
				return none!(mixin("typeof(" ~ call ~ ")"));
			}
			mixin(autoReturn!(call));
		}

		/**
		 * Dollar operator representing the length of the array
		 */
		auto opDollar() const
		{
			return empty ? 0 : front.length;
		}
	}

	/**
	 * Calculates the hash value of the value inside this optional
	 *
	 * Returns: hash of the optional value
	 */
	size_t toHash() const @safe nothrow
	{
		static if (__traits(compiles, .hashOf(value.payload)))
			return defined ? .hashOf(value.payload) : 0;
		else
			return defined ? typeid(T).getHash(&value.payload) : 0;
	}

	/**
	  * Convert the optional to a human readable string.
	  */
	string toString()() const
	{
		import std.conv : to;

		if (empty)
		{
			return "Optional(None)";
		}
		static if (__traits(compiles, { value.payload.toString; }))
		{
			return "Some(" ~ value.payload.toString ~ ")";
		}
		else
		{
			return "Some(" ~ to!string(value.payload) ~ ")";
		}
	}

}

/**
 * A type with nothing inside used by Optional
 *
 * This type is useful to represent empty data from an
 * optional type, instead of doing payload allocation.
 */
@safe pure nothrow @nogc
public struct None
{
	/**
	 * Converts type None to string
	 *
	 * Returns: None string identifier
	 */
	@safe pure nothrow @nogc
	public string toString() const
	{
		return __traits(identifier, None);
	}
}

/**
 * Represents a non defined optional type
 */
@safe pure
public auto none(T)()
{
	return Optional!T();
}

/**
 * Represents a None type
 */
@safe pure
public None none()
{
	immutable none = None();
	return none;
}

/**
 * Creates an optional type with a defined given value
 *
 * Params:
 *   value = a given value
 */
public auto some(T)(auto ref T value)
{
	import std.traits : isCopyable;

	static if (!isCopyable!T)
	{
		import std.functional : forward;

		return optional!T(forward!value);
	}
	else
	{
		return optional!T(value);
	}
}

/// ditto
public auto optional(T)(auto ref T value)
{
	import std.traits : isCopyable;

	static if (!isCopyable!T)
	{
		import std.functional : forward;

		return Optional!T(forward!value);
	}
	else
	{
		return Optional!T(value);
	}
}

/**
 * Creates an optional type with a none
 * Params:
 *   none = None type, empty data
 */
public auto some(T)(const None none)
{
	return optional!T(none);
}

/// ditto
public auto optional(T)(const None none)
{
	return Optional!T(none);
}

/**
 * Creates an empty optional type
 */
public auto optional(T)()
{
	return Optional!T();
}

///
@system pure
@("Optional: front & popFront")
unittest
{
	auto a = some(7);
	auto b = none!int;

	assertEquals(7, a.front);
	assertTrue(a.defined);
	a.popFront();
	assertFalse(a.defined);

	expectThrows!AssertError(a.front);
	expectThrows!AssertError(b.front);
}

///
@safe pure
@("Optional: definition")
unittest
{
	assertTrue(some(5).defined);
	assertTrue(Optional!int(5).defined);

	struct foobar
	{
		@disable this(this);

		int z;
	}

	assertTrue(some(foobar()).defined);
	assertTrue(some(none!int).defined);

	assertFalse(some!int(none).defined);
	assertFalse(some(null).defined);

	assertFalse(none!int.defined);
	assertFalse(Optional!int().defined);
	assertFalse(Optional!(int[])().defined);
}

/**
 * Converts a input range into an optional type
 *
 * Params:
 *   range = given input range
 */
auto toOptional(R)(auto ref R range) if (isInputRange!R || is(R == void[]))
{
	static if (is(R == void[]))
	{
		return none;
	}
	else
	{
		assert(range.empty || range.walkLength == 1);
		if (range.empty)
		{
			return none!(ElementType!R);
		}
		else
		{
			return some(range.front);
		}
	}
}

/**
 * Converts a nullable type to an optional type
 *
 * Params:
 *   nullable = given Nullable!T
 */
auto toOptional(T)(auto inout ref Nullable!T nullable)
{
	if (nullable.isNull)
	{
		return inout Optional!T();
	}
	else
	{
		return inout Optional!T(nullable.get);
	}
}

///
@safe pure
@("Optional: toOptional")
unittest
{
	assertEquals(some(7), toOptional([7]));
	assertEquals(none, toOptional([]));
	assertEquals(none, toOptional([null]));
	assertEquals(none, toOptional((int[]).init));

	assertEquals(some(7), toOptional(Nullable!(int)(7)));
	assertEquals(none, toOptional(Nullable!(typeof(null))(null)));
	assertEquals(none, toOptional(Nullable!(int)()));
}

///
@safe pure
@("Optional: assign operator")
unittest
{
	Optional!int foo;
	Optional!int bar;
	assertEquals(none, foo);
	foo = none;
	assertEquals(none, foo);
	foo = bar;
	assertEquals(none, bar);
	assertEquals(bar, foo);
	foo = 7;
	assertEquals(7, foo);
	// assign again to move instead of moveEmplace
	foo = 3;
	assertEquals(3, foo);
	foo = some(7);
	assertEquals(7, foo);
	// assign again to none invalidation defined value
	foo = none;
	assertEquals(none, foo);

}

///
@safe pure
@("Optional: arrays")
unittest
{
	auto arr = some([1, 2, 3, 45]);
	assertEquals(2, arr[1]);
	assertEquals([1, 2, 3, 45], arr[]);
	assertEquals([1, 2, 3, 45], arr[0 .. $]);
	auto jk = none!(int[]);
	assertEquals(none!int, jk[213]);
	assertEquals(none!(int[]), jk[]);
	assertEquals(none!(int[]), jk[0 .. $]);
}

///
@safe pure
@("Optional: toHash")
unittest
{
	Optional!int foo;
	assertEquals(0, foo.toHash);
	foo = 7;
	assertTrue(foo.toHash > 0);
	assertEquals(.hashOf(7), foo.toHash);
}

///
@safe
@("Optional: inpure toHash")
unittest
{
	Optional!Object bar;
	assertEquals(0, bar.toHash);
	auto obj = new Object();
	bar = obj;
	assertTrue(bar.toHash > 0);
	assertEquals(.hashOf(obj), bar.toHash);
}

///
@system
@("Optional: inpure and unsafe toHash")
unittest
{
	auto obj = new Object();
	Optional!Object bar = obj;
	assertEquals(typeid(Object).getHash(&obj), bar.toHash);
}

///
@safe pure
@("Optional: opEquals")
unittest
{
	assertEquals(7, some(7));
	assertEquals(none!int, none!int);
	assertEquals(none, none!int);
	assertEquals(none, none);
	assertEquals(none!int, some(none!int));
	assertEquals(none, some(none));

	// compare with nullable
	assertEquals(nullable(7), optional(7));
	assertEquals(Nullable!(int).init, none!int);

	// range opEquals
	assertEquals([7], some(7));
	int[] a = [];
	assertEquals(a, none!int);
}

///
@safe pure
@("Optional: class opEquals")
unittest
{
	@safe pure class C
	{
		int c;

		// assertEquals needs @safe and pure
		// toString method in case of fail
		@safe pure
		override string toString() const
		{
			import std.conv : to;

			return c.to!string;
		}
	}

	C c = new C();
	assertEquals(c, optional(c));
	assertEquals(optional(c), optional(c));
	// cover toString method
	assertEquals("0", optional(c).front.toString);
}

///
@safe pure
@("Optional: toString")
unittest
{
	assertEquals("Some(1)", some(1).toString);
	assertEquals("None", none.toString);
	assertEquals("Optional(None)", none!int.toString);
}

/**
 * Converts an optional type to a nullable type
 *
 * Params:
 *   opt = optional
 */
auto toNullable(T)(auto ref Optional!T opt)
{
	return (opt.empty)
		? Nullable!T() : opt.front.nullable;
}

///
@safe pure
@("Optional: toNullable")
unittest
{
	assertEquals(nullable(7), some(7).toNullable);
	assertEquals(Nullable!(int).init, none!int.toNullable);
}

///
@safe pure
@("Optional: getOr")
unittest
{
	auto a = some(3);
	auto b = none!int;

	assertEquals(3, a.getOr(7));
	assertEquals(8, b.getOr(8));
}

/**
 * Gets the value inside of a nullable type or fallback to a given value
 *
 * Params:
 *   n = nullable type
 *   t = fallback value
 *
 * Returns: value inside nullable if defined, fallback otherwise
 */
T getOr(T)(Nullable!T n, T t)
{
	return n.isNull ? t : n.get();
}

///
@safe pure
@("Nullable: getOr")
unittest
{
	auto a = nullable(3);
	auto b = Nullable!(int).init;

	assertEquals(3, a.getOr(7));
	assertEquals(8, b.getOr(8));
}

///
@safe pure
@("Optional: autoReturn")
unittest
{
	auto foobar = () => "thestring";
	// type independent
	immutable string expr1 = Optional!(string).autoReturn!("foobar()");
	immutable string expr2 = Optional!(typeof(null)).autoReturn!("foobar()");

	import std.string : splitLines, strip, startsWith;
	import std.algorithm.iteration : map, filter, joiner;

	auto minify = (string t) => t.splitLines
		.map!(strip)
		.filter!(l => !l.empty)
		.filter!(l => !l.startsWith("//"))
		.joiner;

	auto minifiedExpr = minify(q{
		auto ref expr() {
				return foobar();
			}
			alias R = typeof(expr());
			static if (!is(R == void))
				return empty ? none!R : some!R(expr());
			else {
				if (!empty) {
					expr();
				}
			}
	});

	// just to make sure you dont make mistakes on minify
	assertFalse(minifiedExpr.array.empty);
	assertFalse(minify(expr1).array.empty);
	assertFalse(minify(expr2).array.empty);

	assertEquals(minifiedExpr.array, minify(expr1).array);
	assertEquals(minifiedExpr.array, minify(expr2).array);
}

struct OptionalChain(T)
{
	import std.traits : hasMember;

	private static string autoReturn(string expression)()
	{
		return `
			auto ref expr() {
				return `
			~ expression ~ `;
			}
			`
			~ q{
			auto ref val() {
				// If the dispatched result is an Optional itself, we flatten it out so that client code
				// does not have to do a.oc.member.oc.otherMember
				static if (isOptional!(typeof(expr()))) {
					return expr().front;
				} else {
					return expr();
				}
			}
			alias R = typeof(val());
			static if (is(R == void)) {
				if (!value.empty) {
					val();
				}
			} else {
				if (value.empty) {
					return OptionalChain!R(none!R());
				}
				static if (isOptional!(typeof(expr()))) {
					// If the dispatched result is an optional, check if the expression is empty before
					// calling val() because val() calls .front which would assert if empty.
					if (expr().empty) {
						return OptionalChain!R(none!R());
					}
				}
				return OptionalChain!R(some(val()));
			}
		};
	}

	public Optional!T value;
	alias value this;

	this(Optional!T value)
	{
		this.value = value;
	}

	this(T value)
	{
		this.value = value;
	}

	public string toString()
	{
		return value.toString;
	}

	public template opDispatch(string name) if (hasMember!(T, name))
	{
		static if (is(typeof(__traits(getMember, T, name)) == function))
		{
			auto opDispatch(Args...)(auto ref Args args)
			{
				mixin(autoReturn!("value.front." ~ name ~ "(args)"));
			}
		}
		else static if (is(typeof(mixin("value.front." ~ name))))
		{
			// non-function field
			auto opDispatch(Args...)(auto ref Args args)
			{
				static if (Args.length == 0)
				{
					mixin(autoReturn!("value.front." ~ name));
				}
				else static if (Args.length == 1)
				{
					mixin(autoReturn!("value.front." ~ name ~ " = args[0]"));
				}
				else
				{
					static assert(
							0,
							"Dispatched " ~ T.stringof ~ "." ~ name ~ " was resolved to non-function field that has more than one argument",
					);
				}
			}
		}
		else
		{
			// member template
			template opDispatch(Ts...)
			{
				enum targs = Ts.length ? "!Ts" : "";
				auto opDispatch(Args...)(auto ref Args args)
				{
					mixin(autoReturn!("value.front." ~ name ~ targs ~ "(args)"));
				}
			}
		}
	}
}

auto oc(T)(auto ref T value) if (isNullTestable!T && !isInstanceOf!(Nullable, T))
{
	return OptionalChain!T(value);
}

auto oc(T)(auto ref Optional!T value)
{
	return OptionalChain!T(value);
}

auto oc(T)(auto ref Nullable!T value)
{
	return OptionalChain!T(value.isNull ? none!T : some(value.get));
}

@safe pure
@("OptionalChain: Optional")
unittest
{
	@safe pure class C
	{
		int fun()
		{
			return 3;
		}
	}

	Optional!C a = null;
	assertEquals(none!int, oc(a).fun);

	a = new C();
	assertEquals(3, oc(a).fun);
	assertEquals(some(3), oc(a).fun);
}

@safe pure
@("OptionalChain: Nullable")
unittest
{
	@safe pure class C
	{
		int fun()
		{
			return 3;
		}
	}

	Nullable!C a;
	assertEquals(none!int, oc(a).fun);

	a = new C();
	assertEquals(3, oc(a).fun);
	assertEquals(some(3), oc(a).fun);
}

@safe pure
@("OptionalChain: null testable values")
unittest
{
	// not null testable values (basic types and structs)
	assertFalse(__traits(compiles, oc(7)));

	// nullable c
	@safe pure
	class C
	{
		int c = 3;
		alias c this;

		// need this to not be ambigous
		@safe pure
		override string toString() const
		{
			import std.conv : to;

			return c.to!string;
		}
	}

	C c = null;
	assertTrue(none!C == oc(c).value);
	assertEquals(none!int, oc(c).c);

	c = new C();

	assertEquals(c, oc(c).value);
	assertEquals(3, oc(c).c);
	// just to cover toString
	assertEquals("Some(3)", oc(c).toString);
}

///
@safe pure
@("OptionalChain: autoReturn")
unittest
{
	// type independent
	immutable string expr1 = OptionalChain!(string).autoReturn!("value.front");
	immutable string expr2 = OptionalChain!(typeof(null)).autoReturn!("value.front");

	import std.string : splitLines, strip, startsWith;
	import std.algorithm.iteration : map, filter, joiner;

	auto minify = (string t) => t.splitLines
		.map!(strip)
		.filter!(l => !l.empty)
		.filter!(l => !l.startsWith("//"))
		.joiner;

	auto minifiedExpr = minify(q{
			auto ref expr() {
				return value.front;
			}

			auto ref val() {
				static if (isOptional!(typeof(expr()))) {
					return expr().front;
				} else {
					return expr();
				}
			}
			alias R = typeof(val());
			static if (is(R == void)) {
				if (!value.empty) {
					val();
				}
			} else {
				if (value.empty) {
					return OptionalChain!R(none!R());
				}
				static if (isOptional!(typeof(expr()))) {
					if (expr().empty) {
						return OptionalChain!R(none!R());
					}
				}
				return OptionalChain!R(some(val()));
			}
	});

	// just to make sure you dont make mistakes on minify
	assertFalse(minifiedExpr.array.empty);
	assertFalse(minify(expr1).array.empty);
	assertFalse(minify(expr2).array.empty);

	assertEquals(minifiedExpr.array, minify(expr1).array);
	assertEquals(minifiedExpr.array, minify(expr2).array);
}
