# Event: EventSystem

An easy way to use events, written in D.

## Examples

### This is the simplest event you can make
```d
module simpleevent;
import deventsystem.event;

@EventType("SimpleEvent")
class SimpleEvent : Event
{
	mixin basicEventType!SimpleEvent;
}
```
By using the `basicEventType` mixin it auto implements the abstract methods defined in the parent class `Event` and creates a new static function with the event type you defined in `@EventType`
```d
@safe abstract class Event
{
public:
	@safe pure
	abstract @property string eventType() const;

	// ...
}
```
The above code generates something like this
```d
module simpleevent;
import deventsystem.event;

@EventType("SimpleEvent")
class SimpleEvent : Event
{
public:
	@safe pure
	static @property string staticEventType()
	{
		return "SimpleEvent";
	}

	@safe pure
	override @property string eventType() const
	{
		return staticEventType;
	}
}
```
To use an event you must create a callback and the connect it to a default function or not depending on which behaviour you're looking for
```d
module app;
import simpleevent;
import deventsystem.event;

class Foo
{
	// use this to generate everything you need for your event
	mixin genCallback!(Foo, SimpleEvent) onSimple;

	// you MUST create an **onEvent** function
	protect void onEvent(Event event)
	{
		import deventsystem.eventdispacher : EventDispacher;

		// create an event dispacher to guide your event to the right function
		EventDispacher ed = new EventDispacher(event);

		// dispach your event to the default dispacher of the given event
		ed.dispach!SimpleEvent(&onSimple.dispach);
	}


	// you can or not create a function to emit your event
	public void simple()
	{
		// add some logic you might want

		// emit the event
		onSimple.emit;

		// DISCLAIMER: the function above is only generated if your event has
		//   public empty constructor which is true in this case

		/**
		 * you can however pass in an event whether or not you have the said
		 *    constructor above
		 *
		 * Examples:
		 * --------------------
		 * SimpleEvent event = new SimpleEvent();
		 * onSimple.emit(event);
		 * --------------------
		 */
	}
}

public bool onFooSimple(Foo foo, SimpleEvent event)
{
	// logic here
	// return true or false to stop or not propagating the event respectively
	return true;
}

public void main()
{
	Foo foo = new Foo();

	foo.onSimple.connect((Foo foo, SimpleEvent event) {
		// logic here
		// return true or false to stop or not propagating the event respectively
		return true;
	});

	// same as
	import std.functional : toDelegate;
	foo.onSimple.connect(toDelegate(&onFooSimple));

	// calls onFooSimple
	foo.simple();
}
```

### A more realistic example
Lets imagine an use case where you have mouse events
```d
module mouseevent;
import deventsystem.event;

@EventType("MouseEvent")
class MouseEvent : Event
{
	mixin basicEventType!MouseEvent;

	protected this() {}
}

@EventType("MouseButtonEvent")
class MouseButtonEvent : MouseEvent
{
	mixin basicEventType!MouseEvent;

	protected this(uint keyval)
	{
		this.keyval = keyval;
	}

	const uint keyval;
}

@EventType("MouseButtonPressedEvent")
class MouseButtonPressedEvent : MouseButtonEvent
{
	mixin basicEventType!MouseButtonPressedEvent;

	public this(uint keyval)
	{
		super(keyval);
	}
}

@EventType("MouseButtonReleasedEvent")
class MouseButtonReleasedEvent : MouseButtonEvent
{
	mixin basicEventType!MouseButtonReleasedEvent;

	public this(uint keyval)
	{
		super(keyval);
	}
}
```
Lets imagine you have program with windows which capture mouse events and now
you want to add functionality to that
```d
module window
import mouseevent;
import deventsystem.event;
import std.typecons : scoped;

class Window
{
	mixin genCallback!(Window, MouseButtonPressedEvent) onMouseButtonPressed;

	// you can create a callback with some of the variables in an Event!
	// be aware the variable's name MUST BE equal to the names in the event
	// class
	mixin genCallback!(Window, MouseButtonReleasedEvent, int, "keyval") onMouseButtonReleased;

public:
	this()
	{
		// you can add some default behaviour
		onMouseButtonPressed.connect((Window, MouseButtonPressedEvent event) {
			// logic here
			return true;
		});

		onMouseButtonReleased.connect((Window, int keyval) {
			// logic here
			return true;
		});
	}

	void mouseButtonPress(uint keyval)
	{
		// some logic ...
		// emit the signal
		onMouseButtonPressed.emit(scoped!MouseButtonPressedEvent(keyval));
	}

	void mouseButtonRelease()
	{
		// some logic ...
		// emit the signal
		onMouseButtonReleased.emit(keyval);
	}

protected:
	void onEvent(Event event)
	{
		import deventsystem.eventdispacher : EventDispacher;
		auto ed = scoped!EventDispacher(event);

		ed.dispach!MouseButtonPressedEvent(&onMouseButtonPressed.dispach);
		ed.dispach!MouseButtonReleasedEvent(&onMouseButtonReleased.dispach);
	}
}
```
