module aurorafw.gui.api.x11.input;

import aurorafw.core.input.keys;

InputButton translateInputButtonX11(uint button)
{
	assert(0);
}

Keycode translateKeycodeX11(uint keycode)
{
	if (keycode < 0 || keycode > 255)
		return Keycode.Unknown;
	assert(0);
}

InputModifier translateInputModifierX11(uint state)
{
	assert(0);
}