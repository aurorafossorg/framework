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
import aurorafw.entity.componentmanager;
import aurorafw.entity.entitymanager;

version(unittest) import aurorafw.unit.assertion;

import std.exception;
import std.traits : fullyQualifiedName, Fields, FieldNameTuple;
import std.meta : AliasSeq;


class EntityComponentHandlingException : Exception
{
	mixin basicExceptionCtors;
}


class Entity
{
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
	 *
	 * See_Also: T add(T : IComponent)()
	 */
	@safe pure
	public T add(T : IComponent)(T t)
	{
		enum id = ComponentManager.idOf!T;

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
	 * Use this only if you want to generate the component with init values
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
	 * If you don't know which id you should pass, use the other variant of this
	 *   function, which is the recomended one, as it will get the correct id
	 *   for you
	 *
	 * Examples:
	 * --------------------
	 * e.remove(world.component.idOf!Foo);
	 * --------------------
	 *
	 * See_Also: remove(C : IComponent)()
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
	 * It's recomended to always use this function, as it will do the 'hard
	 *   work' for you
	 *
	 * Examples:
	 * --------------------
	 * e.remove!Foo;
	 * --------------------
	 */
	@safe pure
	public void remove(C : IComponent)()
	{
		remove(ComponentManager.idOf!C);
	}


	/**
	 * Modify
	 *
	 * Updates the data of a component
	 *
	 * Examples:
	 * --------------------
	 * e.moodify!Foo(ctor values...);
	 * --------------------
	 * e.add(new Foo(3));
	 * e.modify!Foo(5);
	 * --------------------
	 */
	@safe pure
	public C modify(C : IComponent)(AliasSeq!(Fields!C) args)
	{
		enum id = ComponentManager.idOf!C;
		IComponent* p;
		p = id in components;

		if(p is null)
			throw new EntityComponentHandlingException(
				"Cannot modify component. Entity doesn't contain "
				~ __traits(identifier, C) ~ "."
			);

		C c = cast(C)components[id];
		import std.conv : to;
		static foreach(i, f; [FieldNameTuple!C])
		{
			mixin("c."~f~"="~"args["~i.to!string~"];");
		}

		return c;
	}

	/**
	 * Clear
	 *
	 * Removes every component from this entity
	 *
	 * Examples:
	 * --------------------
	 * e.clear();
	 * --------------------
	 */
	@safe pure
	public void clear()
	{
		import std.algorithm.iteration : each;
		components.byKey.each!(_ => components.remove(_));
	}


	/**
	 * Get a component
	 *
	 * Returns:
	 *     Same type if it exists
	 *     Null otherwise
	 *
	 * Examples:
	 * --------------------
	 * e.get!Foo
	 *--------------------
	 */
	@safe pure
	public C get(C : IComponent)()
	{
		enum id = ComponentManager.idOf!C;
		IComponent* p;
		p = id in components;

		return p !is null ? cast(C)(*p) : null;
	}


	/**
	 * Get components
	 *
	 * Returns:
	 *     array of components which are contained in an entity
	 *     However if you want to actualy access any of this, this method isn't
	 *       recomended
	 *     Use the template 'get' as it will return the type of that component
	 *     Or use 'contains', 'containsAny', 'containsAll' if you want to know
	 *       which components an entity is holding
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
	 * You call this function by passing the component's id
	 * Every time you create a component, it'll generate an unique id
	 * If you don't know which id you should pass, use the other variant of this
	 *   function, which is the recomended one, as it will get the correct id
	 *   for you
	 *
	 * Returns:
	 *     True if the entity contains the component
	 *     False otherwise
	 *
	 * Examples:
	 * --------------------
	 * e.contains(world.component.idOf!Foo);
	 * --------------------
	 *
	 * See_Also: contains(C : IComponent)()
	 */
	@safe pure
	public bool contains(in string id) const
	{
		return (id in components) !is null;
	}


	/**
	 * Contains a component
	 *
	 * It's recomended to always use this function, as it will do the 'hard
	 *   work' for you
	 *
	 * Returns:
	 *     True if the entity contains the component
	 *     False otherwise
	 *
	 * Examples:
	 * --------------------
	 * e.contains!Foo;
	 * --------------------
	 */
	public bool contains(C : IComponent)() const
	{
		return contains(ComponentManager.idOf!C);
	}


	/**
	 * Contains components
	 *
	 * You call this function by passing an array of the component ids
	 * Every time you create a component, it'll generate an unique id
	 * If you don't know which ids you should pass, use the other variant of
	 *   this function, which is the recomended one, as it will get the correct
	 *   id for you
	 *
	 * Returns:
	 *     True if all the components exist
	 *     False otherwise
	 *
	 * Examples:
	 * --------------------
	 * e.containsAll([world.component.idOf!Foo, world.component.idOf!Bar]);
	 * --------------------
	 *
	 * See_Also: containsAll(C...)()
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
	 * It's recomended to always use this function, as it will do the 'hard
	 *   work' for you
	 *
	 * Returns:
	 *     True if the entity contains all of the components
	 *     False otherwise
	 *
	 * Examples:
	 * --------------------
	 * e.containsAll!(Foo, Goo);
	 * --------------------
	 */
	@safe pure
	public bool containsAll(C...)() const
	{
		return containsAll(ids!C);
	}


	/**
	 * Contains any component
	 *
	 * You call this function by passing an array of the component ids
	 * Every time you create a component, it'll generate an unique id
	 * If you don't know which ids you should pass, use the other variant of
	 *   this function, which is the recomended one, as it will get the correct
	 *   id for you
	 *
	 * Returns:
	 *     True if the entity contains at least one of the components
	 *     False otherwise
	 *
	 * Examples:
	 * --------------------
	 * e.containsAny([world.component.idOf!Foo, world.component.idOf!Bar]);
	 * --------------------
	 *
	 * See_Also: containsAny(C...)()
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
	 * It's recomended to always use this function, as it will do the 'hard
	 *   work' for you
	 *
	 * Returns:
	 *     True if the entity contains at least one of the components
	 *     False otherwise
	 *
	 * Examples:
	 * --------------------
	 * e.hasAnyComponents!(Foo, Goo);
	 * --------------------
	 */
	@safe pure
	public bool containsAny(C...)() const
	{
		return containsAny(ids!C);
	}


	/**
	 * Ids
	 *
	 * Used internaly only
	 * Returns: ids of every component contained by this entity
	 */
	@safe pure
	private auto ids(C...)() const
	{
		import std.meta : staticMap;
		return [staticMap!(fullyQualifiedName, C)];
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


	public immutable size_t id;
	public string name;
	public string description;
	public bool enabled;
	private IComponent[string] components;
	private EntityManager manager;
}


version(unittest)
{
	final class unittest_FooComponent : IComponent { int a; }
	final class unittest_BarComponent : IComponent { int a; }
}


///
@safe pure
@("Entity: Adding and removing a component twice")
unittest
{
	Entity e = new Entity(null, 0);

	unittest_FooComponent f = new unittest_FooComponent();
	e.add(f); // First time the component is added, no error
	assertThrown!EntityComponentHandlingException(e.add(f), "Second time the same type is added");

	e.remove!unittest_FooComponent; // First time the component is removed, no error
	assertThrown!EntityComponentHandlingException(e.remove!unittest_FooComponent,
				"Second time the type is being accessed");
}


///
@safe pure
@("Entity: Getting and contained components")
unittest
{
	Entity e = new Entity(null, 0);
	unittest_FooComponent foo = new unittest_FooComponent();
	e.add(foo); // Entity components == [foo]

	assertTrue(e.contains!unittest_FooComponent);
	assertTrue(e.containsAll!unittest_FooComponent);
	assertTrue(e.containsAny!(unittest_FooComponent, unittest_BarComponent), "Entity contains an unittets_FooComponent");

	assertFalse(e.containsAll!(unittest_FooComponent, unittest_BarComponent),
				"Entity doesn't contain an unittest_BarComponent");
	assertFalse(e.containsAny!(unittest_BarComponent));

	import std.range.primitives;
	auto arr = e.getAll;

	import std.traits : ReturnType;
	assertTrue(is(ReturnType!(e.get!unittest_FooComponent) == unittest_FooComponent), "Returns the original type");
	assertTrue(foo is e.get!unittest_FooComponent);
	assertTrue(e.get!unittest_BarComponent is null, "Entity doesn't contain a type unittest_BarComponent component");
	assertEquals(1, arr.length, "Entity should contain only 1 component");
	assertTrue(is(typeof(arr.front) == IComponent));
}


///
@safe pure
@("Entity: Entity clear")
unittest
{
	Entity e = new Entity(null, 0);

	e.add(new unittest_FooComponent());
	e.clear();

	assertEquals(0, e.getAll().length);
}


///
@safe pure
@("Entity: Modify component contents")
unittest
{
	Entity e = new Entity(null, 0);
	e.add!unittest_FooComponent;

	assertEquals(int.init, e.get!unittest_FooComponent.a);

	e.modify!unittest_FooComponent(4);

	assertEquals(4, e.get!unittest_FooComponent.a);
	assertThrown!EntityComponentHandlingException(e.modify!unittest_BarComponent(5));
}
