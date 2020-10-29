/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2019-2020 Aurora Free Open Source Software.
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

module aurorafw.entity.entitymanager;

import aurorafw.entity.entity;
import aurorafw.entity.icomponent;
import aurorafw.entity.componentmanager;
import aurorafw.entity.world;

version (unittest) import aurorafw.unit.assertion;

import std.range;
import std.exception;

class EntityManagerHandlingException : Exception
{
	mixin basicExceptionCtors;
}

final class EntityManager
{
	/**
	 * Create an entity
	 *
	 * Creates a new entity with an unique id
	 *
	 * Examples:
	 * --------------------
	 * world.entity.create();
	 * Entity e = world.entity.create();
	 * --------------------
	 */
	@safe pure
	public Entity create()
	{
		Entity e = new Entity(this, !this.delEntities.empty ? popDeletedId : nextId++);
		this.mEntities[e.id] = e;

		return e;
	}

	/**
	 * Pop deleted id
	 *
	 * Reuses an id which belonged to another entity before
	 * If there's not an id available in this, it returns null
	 *
	 * This function is only used inernaly for the creation of entities
	 */
	@safe pure
	private size_t popDeletedId()
	{
		size_t eid = this.delEntities.front;
		this.delEntities = this.delEntities.length > 1 ? this.delEntities[1 .. $] : null;

		return eid;
	}

	/**
	 * Exists
	 *
	 * Returns whether an entity exists in the scope
	 *
	 * Examples:
	 * --------------------
	 * world.manager.create();
	 * world.entity.exists(0); // true
	 * --------------------
	 */
	@safe pure
	public bool exists(in size_t eid) const
	{
		return (eid in this.mEntities) !is null;
	}

	/**
	 * Get an entity
	 *
	 * Returns the entity which contains the id passed
	 * If there are none, it returns null
	 *
	 * Examples:
	 * --------------------
	 * Entity e = world.entity.get(16);
	 * --------------------
	 */
	@safe pure
	public Entity get(in size_t eid)
	{
		Entity* p;
		return ((p = eid in this.mEntities) !is null) ? *p : null;
	}

	/**
	 * Get the first entity in the scope with a component
	 *
	 * Returns the first entity with the component passed
	 * If there's none, it returns null
	 *
	 * Examples:
	 * --------------------
	 * Entity e = world.entity.getFirstWith!Foo;
	 * --------------------
	 */
	@safe pure
	public Entity getFirstWith(C : IComponent)()
	{
		foreach (Entity e; this.mEntities)
			if (e.contains!C)
				return e;

		return null;
	}

	/**
	 * Get the first entity in the scope which contains a group of components
	 *
	 * Returns the first entity with the components passed
	 *
	 * Examples:
	 * --------------------
	 * Entity e = world.entity.getFirstWith!(Component1, Component2, Component3, ...);
	 * --------------------
	 */
	@safe pure
	public Entity getFirstWith(T...)()
	{
		foreach (Entity e; this.mEntities)
			if (e.containsAll!T)
				return e;

		return null;
	}

	/**
	 * Get every entity in the scope which contains a component
	 *
	 * Returns an array of type Entity with every entity which contains the component passed
	 *
	 * Examples:
	 * --------------------
	 * Entity[] arr = world.entity.getAllWith!Foo;
	 * --------------------
	 */
	@safe pure
	public Entity[] getAllWith(T : IComponent)()
	{
		Entity[] ret;
		foreach (Entity e; this.mEntities)
			if (e.contains!T)
				ret ~= e;

		return ret;
	}

	/**
	 * Get every entity in the scope which contains a group of components
	 *
	 * Returns an array of type Entity with every entity which contains the components passed
	 *
	 * Examples:
	 * --------------------
	 * Entity[] arr = world.entity.getAllWith!(Component1, Component2, Component3, ...);
	 * --------------------
	 */
	@safe pure
	public Entity[] getAllWith(T...)()
	{
		Entity[] ret;
		foreach (Entity e; this.mEntities)
			if (e.containsAll!T)
				ret ~= e;

		return ret;
	}

	/**
	 * Get all the deleted ids
	 *
	 * Returns an array with all the deleted ids currently in the scope
	 *
	 * Examples:
	 * --------------------
	 * auto[] arr = world.entity.getDeletedIds();
	 * --------------------
	 */
	@safe pure
	public size_t[] getDeletedIds() const
	{
		return this.delEntities.dup;
	}

	/**
	 * Detach
	 *
	 * Removes an entity from the world's scope if it exists
	 *
	 * Examples:
	 * --------------------
	 * world.entity.detach(e);
	 * --------------------
	 */
	@safe pure
	public void detach(Entity e)
	{
		Entity* p;
		p = e.id in this.mEntities;

		if (p !is null && e is this.mEntities[e.id])
		{
			this.mEntities.remove(e.id);
			this.delEntities ~= e.id;
		}
		else
			throw new EntityManagerHandlingException(
					"Cannot detach entity. Entity doesn't exist in the world's scope."
			);
	}

	/*
	 * Clear
	 *
	 * Removes every entity from the world's scope
	 */
	@safe pure
	public void clear()
	{
		foreach (key, value; this.mEntities)
		{
			this.delEntities ~= key;
			this.mEntities.remove(key);
		}
	}

	private size_t nextId = 0;
	private Entity[size_t] mEntities;
	private size_t[] delEntities;
}

///
@safe pure
@("Entity Manager: Entity id counter")
unittest
{
	EntityManager manager = new EntityManager();

	Entity e1 = manager.create();
	Entity e2 = manager.create();

	assertTrue(manager.exists(0));

	assertEquals(0, e1.id); // Entity id begins in 0
	assertEquals(1, e2.id);

	e1.detach(); // Entity id is removed from the world's scope

	assertEquals(0, manager.getDeletedIds.front);

	Entity e3 = manager.create(); // Entity gets an id which was removed previously

	assertEquals(0, e3.id);
	assertEquals(0, manager.getDeletedIds.length); // Entity id is no longer deleted

	assertThrown!EntityManagerHandlingException(manager.detach(e1)); // This entity is no longer in the world's scope
}

///
@safe pure
@("Entity Manager: Entities getAllWith and getFirstWith")
unittest
{
	final class Foo : IComponent
	{
	}

	final class Bar : IComponent
	{
	}

	final class Foobar : IComponent
	{
	}

	EntityManager manager = new EntityManager();

	Entity e1 = manager.create();
	Entity e2 = manager.create();
	Entity e3 = manager.create();

	e1.add(new Foo());
	e1.add(new Bar());

	e2.add(new Foo());
	e2.add(new Bar());

	e3.add(new Foo());

	auto arr = manager.getAllWith!(Foo, Bar);
	auto e = manager.getFirstWith!Foo;

	import std.algorithm.comparison : equal;

	assertTrue(equal!((a, b) => a is b)([e1, e2], arr));
	assertTrue(e is e1);

	assertTrue(manager.getFirstWith!Foobar is null); // There are no entities with this Component
}

///
@safe pure
@("Entity Manager: Entity getter")
unittest
{
	EntityManager manager = new EntityManager();

	Entity e = manager.create();

	assertTrue(e is manager.get(e.id));
}

///
@safe pure
@("Entity Manager: Entities clear")
unittest
{
	EntityManager manager = new EntityManager();
	Entity e = manager.create();
	manager.clear();

	assertEquals(0, manager.mEntities.length);
}
