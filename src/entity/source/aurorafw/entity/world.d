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

module aurorafw.entity.world;

import aurorafw.entity.entity;
import aurorafw.entity.entitymanager;
import aurorafw.entity.icomponent;
import aurorafw.entity.componentmanager;
import aurorafw.entity.systemmanager;
import aurorafw.entity.system;

import aurorafw.unit.assertion;


final class World
{
	public EntityManager entity;
	public ComponentManager component;
	public SystemManager system;


	@safe pure
	public this()
	{
		component = new ComponentManager();
		entity = new EntityManager(this, component);
		system = new SystemManager(entity);
	}


	@safe pure
	public void update()
	{
		system.update;
	}


	@safe pure
	public void update(S : System)()
	{
		system.update!S;
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
		public this() { super(UpdatePolicy.Manual); }

		override public void update() { this.updatePolicy = UpdatePolicy.Automatic; }
	}


	private class unittest_FooComponent : IComponent
	{
		int a;
	}

	private class unittest_FooBarSystem : System
	{
		override public void update()
		{
			Entity[] arr = this.manager.entity.getAllWith!(unittest_FooComponent);

			foreach(Entity e; arr)
			{
				unittest_FooComponent fc = e.get!unittest_FooComponent;
				fc.a = 5;
			}
		}
	}
}

@safe pure
@("World: System update")
unittest
{
	World world = new World();

	unittest_FooSystem fooSys = new unittest_FooSystem();
	unittest_BarSystem barSys = new unittest_BarSystem();
	world.system.create(fooSys);
	world.system.create(barSys);

	world.update(); // Only updates systems with Automatic Update Policy

	assertEquals(fooSys.updatePolicy, fooSys.UpdatePolicy.Manual); // Got updated
	assertEquals(barSys.updatePolicy, barSys.UpdatePolicy.Manual); // Didn't get updated

	world.system.update!unittest_BarSystem; // Every system can be updated manualy

	assertEquals(barSys.updatePolicy, barSys.UpdatePolicy.Automatic); // Got updated
}

@safe pure
@("World: Main loop")
unittest
{
	World world = new World();

	world.system.create(new unittest_FooBarSystem);
	Entity e = world.entity.create();
	e.add!unittest_FooComponent;

	world.update();

	assertEquals(5, e.get!unittest_FooComponent.a); // Component variable modified in the update method
}