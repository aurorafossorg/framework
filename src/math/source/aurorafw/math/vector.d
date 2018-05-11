module aurorafw.math.vector;

/****************************************************************************
** ┌─┐┬ ┬┬─┐┌─┐┬─┐┌─┐  ┌─┐┬─┐┌─┐┌┬┐┌─┐┬ ┬┌─┐┬─┐┬┌─
** ├─┤│ │├┬┘│ │├┬┘├─┤  ├┤ ├┬┘├─┤│││├┤ ││││ │├┬┘├┴┐
** ┴ ┴└─┘┴└─└─┘┴└─┴ ┴  └  ┴└─┴ ┴┴ ┴└─┘└┴┘└─┘┴└─┴ ┴
** A Powerful General Purpose Framework
** More information in: https://aurora-fw.github.io/
**
** Copyright (C) 2018 Aurora Framework, All rights reserved.
**
** This file is part of the Aurora Framework. This framework is free
** software; you can redistribute it and/or modify it under the terms of
** the GNU Lesser General Public License version 3 as published by the
** Free Software Foundation and appearing in the file LICENSE included in
** the packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************/

@nogc pure @safe struct vec(T, size_t N) {
	private static enum string _elements(string[4] l)
	{
		string ret;
		foreach (size_t i; 0 .. N)
		{
			ret ~= "T " ~ l[i] ~ "; ";
		}
		return ret;
	}

	union
	{
		T[N] vec;
		static if (N < 5)
		{
			struct { mixin(_elements(["x", "y", "z", "w"])); }
			struct { mixin(_elements(["r", "g", "b", "a"])); }
			struct { mixin(_elements(["s", "t", "p", "q"])); }
		}
	}
}

alias vec!(int, 2) Vector2i;
alias vec!(uint, 2) Vector2u;
alias vec!(float, 2) Vector2f;
alias vec!(double, 2) Vector2d;

alias vec!(int, 3) Vector3i;
alias vec!(uint, 3) Vector3u;
alias vec!(float, 3) Vector3f;
alias vec!(double, 3) Vector3d;

alias vec!(int, 4) Vector4i;
alias vec!(uint, 4) Vector4u;
alias vec!(float, 4) Vector4f;
alias vec!(double, 4) Vector4d;

alias Vector2i ivec2;
alias Vector2u uvec2;
alias Vector2f vec2;
alias Vector2d dvec2;

alias Vector3i ivec3;
alias Vector3u uvec3;
alias Vector3f vec3;
alias Vector3d dvec3;

alias Vector4i ivec4;
alias Vector4u uvec4;
alias Vector4f vec4;
alias Vector4d dvec4;