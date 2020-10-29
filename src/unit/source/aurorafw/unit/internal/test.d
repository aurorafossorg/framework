/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2019 Anton Fediushin
Copyright (C) 2019-2020 Aurora Free Open Source Software.
Copyright (C) 2019-2020 Luís Ferreira <luis@aurorafoss.org>

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

This file was based on silly runner.
More about silly: https://gitlab.com/AntonMeep/silly
*/

module aurorafw.unit.internal.test;

package(aurorafw.unit):
version (unittest)  : import std.datetime : Duration;

struct Test
{
	struct Unit
	{
		string fullName;
		string testName;
		Location location;

		void function() testFunc;
	}

	struct Thrown
	{
		string type;
		string msg;
		string file;

		size_t line;

		immutable(string)[] info;
	}

	struct Location
	{
		string file;
		size_t line, column;
	}

	@safe pure
	public static string getName(alias test)()
	{
		string name = __traits(identifier, test);
		foreach (attribute; __traits(getAttributes, test))
		{
			if (is(typeof(attribute) : string))
			{
				name = attribute;
				break;
			}
		}

		return name;
	}

	@safe pure
	public static Location getLocation(alias test)()
	{
		enum loc = __traits(getLocation, test);

		static if (is(typeof(loc)))
			return Location(loc);
		else
			return Location.init;
	}

	Unit test;
	bool status;
	Duration duration;

	immutable(Thrown)[] thrown;
}

enum moduleHasUnittest(alias module_, alias member) =
	__traits(compiles, __traits(parent, __traits(getMember, module_, member))) &&
	__traits(isSame, __traits(parent, __traits(getMember, module_, member)), module_) &&
	__traits(compiles, __traits(getUnitTests, __traits(getMember, module_, member)));

Test[] getTestsFromModule(alias m)()
{
	Test[] tests;
	import std.traits : fullyQualifiedName, isAggregateType;

	static if (__traits(compiles, __traits(getUnitTests, m)) &&
			!(__traits(isTemplate, m) || (__traits(compiles, isAggregateType!m) && isAggregateType!m)))
	{
		alias module_ = m;
	}
	else
	{
		import std.meta : Alias;

		// For cases when module contains member of the same name
		alias module_ = Alias!(__traits(parent, m));
	}

	foreach (test; __traits(getUnitTests, module_))
		tests ~= Test(Test.Unit(fullyQualifiedName!test, Test.getName!test, Test.getLocation!test, &test));

	// Unittests in structs and classes
	foreach (member; __traits(derivedMembers, module_))
		static if (moduleHasUnittest!(module_, member))
			foreach (test; __traits(getUnitTests, __traits(getMember, module_, member)))
				tests ~= Test(Test.Unit(fullyQualifiedName!test, Test.getName!test, Test.getLocation!test, &test));
	return tests;
}

Test[] getTests()()
{
	Test[] tests;
	static if (__traits(compiles, () { static import dub_test_root; }))
	{
		static import dub_test_root;

		foreach (m; dub_test_root.allModules)
		{
			tests ~= getTestsFromModule!m;
		}
	}
	else
	{
		foreach (m; ModuleInfo)
			if (m && m.unitTest)
				tests ~= Test(Test.Unit(m.name, null, m.unitTest));
	}

	return tests;
}
