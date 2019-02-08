/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2018-2019 Aurora Free Open Source Software.

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
http://www.gnu.org/licenses/gpl-3.0.html.

NOTE: All products, services or anything associated to trademarks and
service marks used or referenced on this file are the property of their
respective companies/owners or its subsidiaries. Other names and brands
may be claimed as the property of others.

For more info about intellectual property visit: aurorafoss.org or
directly send an email to: contact (at) aurorafoss.org .
*/

module aurorafw.math.vector;

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

alias vec!(int, 2) Vector2i, ivec2;
alias vec!(uint, 2) Vector2u, uvec2;
alias vec!(float, 2) Vector2f, vec2;
alias vec!(double, 2) Vector2d, dvec2;

alias vec!(int, 3) Vector3i, ivec3;
alias vec!(uint, 3) Vector3u, uvec3;
alias vec!(float, 3) Vector3f, vec3;
alias vec!(double, 3) Vector3d, dvec3;

alias vec!(int, 4) Vector4i, ivec4;
alias vec!(uint, 4) Vector4u, uvec4;
alias vec!(float, 4) Vector4f, vec4;
alias vec!(double, 4) Vector4d, dvec4;
