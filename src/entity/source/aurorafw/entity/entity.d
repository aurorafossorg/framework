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

module aurorafw.entity.entity;

import aurorafw.entity.icomponent;
import aurorafw.entity.ientity;
import aurorafw.entity.componentmanager;
import aurorafw.entity.entitymanager;

import aurorafw.unit.assertion;

import std.exception;
import std.traits : fullyQualifiedName;


class EntityComponentHandlingException : Exception
{
	mixin basicExceptionCtors;
}


class Entity : IEntity
{
	public immutable size_t id;
	public string name;
	public string description;
	public bool enabled;
	private IComponent[string] components;
	private EntityManager manager;


	@safe pure
	public this(EntityManager manager, size_t id)
	{
		this.id = id;
		this.manager = manager;
		this.enabled = true;
	}


	/**
	 * Add a component
	 *
	 * Every time you inittialize a new component, an unique id is generated
	 * Use this function only if you want to generate the component with values
	 *
	 * Examples:
	 * --------------------
	 * e.AddComponent(new Foo(value1, value2, ...));
	 * --------------------
	 */
	@safe pure
	public T add(T)(T t)
	{
		enum id = fullyQualifiedName!T;

		if (id in this.components)
			throw new EntityComponentHandlingException(
				"Cannot add component. Entity already contains the same type."
			);

		this.components[id] = t;
		return t;
	}


	/**
	 * Add a component
	 *
	 * Use this function only if you want to generate the component with init values
	 *
	 * Examples:
	 * --------------------
	 * e.AddComponent!Foo;
	 * --------------------
	 */
	@safe pure
	public T add(T : IComponent)()
	{
		return add(new T());
	}


	/**
	 * Remove a component
	 *
	 * It's called by passing the component's id
	 * Every time you inittialize a new component, an unique id is generated
	 * If you don't know which id you should pass, use the other variant of this function,
	 *     which is the recomended one, as it will get the correct id for you
	 *
	 * Examples:
	 * --------------------
	 * e.remove(world.component.idOf!Foo);
	 * --------------------
	 */
	@safe pure
	public void remove(in string id)
	{
		if (id in this.components)
			this.components.remove(id);

		else
			throw new EntityComponentHandlingException(
				"Cannot remove component. Entity doesn't contain the type you're trying to remove."
			);
	}


	/**
	 * Removes a component
	 *
	 * It's recomended to always use this function, as it will do the 'hard work' for you
	 *
	 * Examples:
	 * --------------------
	 * e.remove!Foo;
	 * --------------------
	 */
	@safe pure
	public void remove(C : IComponent)()
	{
		remove(fullyQualifiedName!C);
	}


	/**
	 * Get a component
	 *
	 * You pass a component type and you'll recive the same type if it exists
	 * If it doesn't, it'll return null
	 *
	 * Examples:
	 * --------------------
	 * e.get!Foo
	 *--------------------
	 */
	@safe pure
	public C get(C : IComponent)()
	{
		enum id = fullyQualifiedName!C;
		IComponent* p;
		p = id in components;

		return p !is null ? cast(C)(*p) : null;
	}


	/**
	 * Get components
	 *
	 * This will return an array of components which are contained in an entity
	 * However if you want to actualy access any of this, this method isn't recomended
	 * Use the template 'get' as it will return the type of that component
	 * Or use 'contains', 'containsAny', 'containsAll' if you want to know which components an entity is holding
	 */
	@safe pure
	public IComponent[] getAll()
	{
		import std.array : array;
		return components.byValue.array;
	}


	/**
	 * Contains a component
	 *
	 * Returns true if the entity contains the component
	 *
	 * You call this function by passing the component's id
	 * Every time you create a component, it'll generate an unique id
	 * If you don't know which id you should pass, use the other variant of this function,
	 *     which is the recomended one, as it will get the correct id for you
	 *
	 * Examples:
	 * --------------------
	 * e.contains(world.component.idOf!Foo);
	 * --------------------
	 */
	@safe pure
	public bool contains(in string id) const
	{
		return (id in components) !is null;
	}


	/**
	 * Contains a component
	 *
	 * Returns true if the entity contains the component
	 *
	 * It's recomended to always use this function, as it will do the 'hard work' for you
	 *
	 * Examples:
	 * --------------------
	 * e.contains!Foo;
	 * --------------------
	 */
	public bool contains(C : IComponent)() const
	{
		return contains(fullyQualifiedName!C);
	}


	/**
	 * Contains components
	 *
	 * Returns true if all the components exist
	 *
	 * You call this function by passing an array of the component ids
	 * Every time you create a component, it'll generate an unique id
	 * If you don't know which ids you should pass, use the other variant of this function,
	 *     which is the recomended one, as it will get the correct id for you
	 *
	 * Examples:
	 * --------------------
	 * e.containsAll([world.component.idOf!Foo, world.component.idOf!Bar]);
	 * --------------------
	 */
	@safe pure
	public bool containsAll(in string[] ids) const
	{
		foreach(id; ids)
			if (!contains(id))
				return false;

		return true;
	}


	/**
	 * Contains components
	 *
	 * Returns true if the entity contains all of the components
	 * It's recomended to always use this function, as it will do the 'hard work' for you
	 *
	 * Examples:
	 * --------------------
	 * e.containsAll!(Foo, Goo);
	 * --------------------
	 */
	@safe pure
	public bool containsAll(C...)() const
	{
		string[] ret;
		foreach(c; C)
			ret ~= fullyQualifiedName!c;

		return containsAll(ret);
	}


	/**
	 * Contains any component
	 *
	 * Returns true if the entity contains at least one of the components
	 *
	 * You call this function by passing an array of the component ids
	 * Every time you create a component, it'll generate an unique id
	 * If you don't know which ids you should pass, use the other variant of this function,
	 *     which is the recomended one, as it will get the correct id for you
	 *
	 * Examples:
	 * --------------------
	 * e.containsAny([world.component.idOf!Foo, world.component.idOf!Bar]);
	 * --------------------
	 */
	@safe pure
	public bool containsAny(in string[] ids) const
	{
		foreach(id; ids)
			if (contains(id))
				return true;

		return false;
	}


	/**
	 * Contains any component
	 *
	 * Returns true if the entity contains at least one of the components
	 * It's recomended to always use this function, as it will do the 'hard work' for you
	 *
	 * Examples:
	 * --------------------
	 * e.hasAnyComponents!(Foo, Goo);
	 * --------------------
	 */
	@safe pure
	public bool containsAny(C...)() const
	{
		string[] ret;
		foreach(c; C)
			ret ~= fullyQualifiedName!c;

		return containsAny(ret);
	}


	/**
	 * Detach
	 *
	 * Remove an entity from the world's scope
	 * Use this when you no longer need the entity
	 */
	@safe pure
	public void detach()
	{
		manager.detach(this);
	}
}

@safe pure
@("Entity: Adding and removing a component twice")
unittest
{
	final class Foo : IComponent {}

	Entity e = new Entity(null, 0);

	Foo f = new Foo();
	e.add(f);                                                // First time the component is added, no error
	assertThrown!EntityComponentHandlingException(e.add(f)); // Second time the same type is added, throws exception

	e.remove!Foo;                                                // First time the component is removed, no error
	assertThrown!EntityComponentHandlingException(e.remove!Foo); // Second time the type is being accessed, throws exception
}

@safe pure
@("Entity: Getting and contained components")
unittest
{
	final class Foo : IComponent {}
	final class Bar : IComponent {}

	Entity e = new Entity(null, 0);
	Foo foo = new Foo();
	e.add(foo); // Entity components == [foo]

	assertTrue(e.contains!Foo);
	assertTrue(e.containsAll!Foo);
	assertTrue(e.containsAny!(Foo, Bar));  // returns true, the entity contains a Foo component

	assertFalse(e.containsAll!(Foo, Bar)); // returns false, the entity doesn't contain a Bar component
	assertFalse(e.containsAny!(Bar));

	import std.range.primitives;
	auto arr = e.getAll;

	import std.traits : ReturnType;
	assertTrue(is(ReturnType!(e.get!Foo) == Foo));   // Using 'get' function returns the original type
	assertTrue(foo is e.get!Foo);
	assertTrue(e.get!Bar is null);                   // The entity doesn't contain a type Bar component, returns null
	assertEquals(1, arr.length);                     // The entity contains only 1 component
	assertTrue(is(typeof(arr.front) == IComponent));
}
