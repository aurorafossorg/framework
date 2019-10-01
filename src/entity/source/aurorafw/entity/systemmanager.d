/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2019 Aurora Free Open Source Software.
Copyright (C) 2019 João Lourenço <joao@aurorafoss.org>

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
*/

module aurorafw.entity.systemmanager;

import aurorafw.entity.system;
import aurorafw.entity.entitymanager;

import aurorafw.unit.assertion;

import std.traits : fullyQualifiedName;
import std.exception;


final class SystemHandlingException : Exception
{
	mixin basicExceptionCtors;
}


class SystemManager
{
	public EntityManager entity;
	private System[string] systems;


	@safe pure
	public this(EntityManager entity)
	{
		this.entity = entity;
	}


	@safe pure
	public void create(S : System)(S s)
	{
		if (!(fullyQualifiedName!S in systems))
		{
			s._manager = this;
			systems[fullyQualifiedName!S] = s;
		}
		else
			throw new SystemHandlingException(
				"Cannot add system. " ~ __traits(identifier, S) ~ " is already created!"
			);
	}


	@safe pure
	public S get(S : System)()
	{
		immutable string name = fullyQualifiedName!S;
		if (name in systems)
			return cast(S)(systems[name]);

		else
			return null;
	}


	@safe pure
	public void update()
	{
		foreach(System s; this.systems)
			if (s.updatePolicy == s.UpdatePolicy.Automatic)
				s.update();
	}


	@safe pure
	public void update(S : System)()
	{
		this.systems[fullyQualifiedName!S].update();
	}
}


version(unittest)
{
	private class unittest_FooSystem : System
	{
		override public void update() { this.updatePolicy = UpdatePolicy.Manual; }
	}

	private class unittest_BarSystem : System
	{
		@safe pure
		public this () { super(UpdatePolicy.Manual); }

		override public void update() { this.updatePolicy = UpdatePolicy.Automatic; }
	}
}

@safe pure
@("System Manager: System creation")
unittest
{
	SystemManager system = new SystemManager(null);

	system.create(new unittest_FooSystem());

	import std.traits : ReturnType;
	assertTrue(is(ReturnType!(system.get!unittest_FooSystem) == unittest_FooSystem));

	assertThrown!SystemHandlingException(system.create(new unittest_FooSystem())); // System created twice
}

@safe pure
@("System Manager: Accessing system properties")
unittest
{
	SystemManager system = new SystemManager(null);

	system.create(new unittest_FooSystem());

	import std.traits : ReturnType;
	assertTrue((system.get!(unittest_FooSystem)).manager is system);
	assertTrue(is(ReturnType!(system.get!unittest_FooSystem) == unittest_FooSystem));
	assertTrue(system.get!(unittest_BarSystem) is null); // System wasn't created
}

@safe pure
@("System Manager: System update")
unittest
{
	SystemManager system = new SystemManager(null);

	unittest_FooSystem fooSys = new unittest_FooSystem();
	unittest_BarSystem barSys = new unittest_BarSystem();
	system.create(fooSys);
	system.create(barSys);

	assertEquals(fooSys.updatePolicy, fooSys.UpdatePolicy.Automatic);
	assertEquals(barSys.updatePolicy, barSys.UpdatePolicy.Manual);

	system.update(); // Only updates systems with Automatic Update Policy

	assertEquals(fooSys.updatePolicy, fooSys.UpdatePolicy.Manual); // Got updated
	assertEquals(barSys.updatePolicy, barSys.UpdatePolicy.Manual); // Didn't get updated

	system.update!unittest_BarSystem; // Systems can be updated manualy

	assertEquals(barSys.updatePolicy, barSys.UpdatePolicy.Automatic); // Got updated
}
