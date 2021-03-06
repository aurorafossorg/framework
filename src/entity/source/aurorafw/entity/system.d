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

module aurorafw.entity.system;

import aurorafw.entity.systemmanager;

version (unittest) import aurorafw.unit.assertion;

abstract class System
{
	/**
	 * Update Policy
	 *
	 * Changes the way world handles system updates
	 *     Automatic: it's called everytime on the word loop update
	 *     Manual: the user decides when he wants the system to be updated
	 */
	enum UpdatePolicy
	{
		Automatic,
		Manual
	}

	@safe pure
	public this(UpdatePolicy updatePolicy = UpdatePolicy.Automatic)
	{
		this.updatePolicy = updatePolicy;
	}

	/**
	 * Manager
	 *
	 * Returns the Entity Manager
	 *
	 * Examples:
	 * --------------------
	 * auto entityManager = this.manager;
	 * --------------------
	 */
	@safe pure
	public SystemManager manager()
	{
		return _manager;
	}

	/**
	 * Manager
	 *
	 * Sets the Entity Manager for the current system
	 * This function is used internaly only
	 *
	 * Examples:
	 * --------------------
	 * System foo = new System();
	 * foo.manager = anEntityManager;
	 * --------------------
	 */
	@safe pure
	package SystemManager manager(SystemManager manager)
	{
		return _manager = manager;
	}

	/**
	 * Update
	 *
	 * Use this method to update each system
	 *
	 * Examples:
	 * --------------------
	 * final class FooSystem : System
	 * {
	 *    override public void update() { *everything you want to update* }
	 * }
	 * --------------------
	 */
	public abstract void update();

	public UpdatePolicy updatePolicy;
	private SystemManager _manager;
}
