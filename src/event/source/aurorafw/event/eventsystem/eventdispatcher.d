/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2020 Aurora Free Open Source Software.
Copyright (C) 2020 João Lourenço <com (dot) gmail (at) jlourenco5691, backward>

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

module aurorafw.event.eventsystem.eventdispatcher;

import aurorafw.event.eventsystem.event : Event;


/** Dispatch an Event to a function
 *
 * Use this class whenever you want to redirect a specific event to a function. \
 */
@safe
public class EventDispatcher
{
public:
	this(Event event)
	{
		this.event = event;
	}


	/** Dispatch an event
	 *
	 * If the `event` variable in EventDispatcher is the same type as T calls func.
	 *
	 * Params:
	 *     T = *Event* to compare to **event**
	 *     func = callback function
	 *
	 * Examples:
	 * --------------------
	 * void onEvent(in Event e)
	 * {
	 *     Eventdispatcher ed = new EventDispatcher(e);
	 *     ed.dispatch!MyEvent(delegate void(MyEvent event) { event.toString().writeln; });
	 * }
	 * --------------------
	 * --------------------
	 * void onEvent(in Event e)
	 * {
	 *     Eventdispatcher ed = new EventDispatcher(e);
	 *     ed.dispatch!MyEvent((MyEvent event) { event.toString().writeln; });
	 * }
	 * --------------------
	 * --------------------
	 * auto func = (MyEvent event) { event.toString.writeln; };
	 * void onEvent(in Event e)
	 * {
	 *     Eventdispatcher ed = new EventDispatcher(e);
	 *     ed.dispatch!MyEvent(func);
	 * }
	 * --------------------
	 * --------------------
	 * void onMyEvent(MyEvent event) { event.toString.writeln; }
	 * void onEvent(in Event e)
	 * {
	 *     import std.functional : toDelegate;
	 *     Eventdispatcher ed = new EventDispatcher(e);
	 *     ed.dispatch!MyEvent(toDelegate(&onMyEvent));
	 * }
	 * --------------------
	 */
	@system
	void dispatch(T : Event)(in void delegate(T) func)
		in(func.ptr !is null || func.funcptr !is null)
	{
		if (event.isEventTypeOf(T.staticEventType))
			func(cast(T) event);
	}

private:
	Event event;
}


private version(unittest)
{
	import aurorafw.unit;
	import aurorafw.event.eventsystem.event : EventType, basicEventType;

	@EventType("FooEvent")
	class FooEvent : Event
	{
		mixin basicEventType!FooEvent;
	}
}


@safe
@("EventDispatcher: ctor")
unittest
{
	FooEvent event = new FooEvent();
	EventDispatcher ed = new EventDispatcher(event);
	assertSame(ed.event, event);
}


@system
@("EventDispatcher: dispatch")
unittest
{
	FooEvent event = new FooEvent();
	FooEvent event2 = new FooEvent();
	EventDispatcher ed = new EventDispatcher(event);

	ed.dispatch!FooEvent(delegate void(in FooEvent _event)
	{
		assertSame(_event, event);
		assertNotSame(_event, event2);
	});

	ed.dispatch!FooEvent((in FooEvent _event) {
		assertSame(_event, event);
		assertNotSame(_event, event2);
	});

	auto func = (in FooEvent _event) {
		assertSame(_event, event);
		assertNotSame(_event, event2);
	};

	ed.dispatch!FooEvent(func);
}
