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

@nogc pure @safe struct vec(T, size_t N)
{
	private static string _elements(string[4] l)
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
		static if (N <= 4)
		{
			struct
			{
				mixin(_elements(["x", "y", "z", "w"]));
			}

			struct
			{
				mixin(_elements(["r", "g", "b", "a"]));
			}

			struct
			{
				mixin(_elements(["s", "t", "p", "q"]));
			}
		}
	}
}

//TODO: Add unittesting

alias Vector2i = vec!(int, 2), ivec2 = vec!(int, 2);
alias Vector2u = vec!(uint, 2), uvec2 = vec!(uint, 2);
alias Vector2f = vec!(float, 2), vec2 = vec!(float, 2);
alias Vector2d = vec!(double, 2), dvec2 = vec!(double, 2);

alias Vector3i = vec!(int, 3), ivec3 = vec!(int, 3);
alias Vector3u = vec!(uint, 3), uvec3 = vec!(uint, 3);
alias Vector3f = vec!(float, 3), vec3 = vec!(float, 3);
alias Vector3d = vec!(double, 3), dvec3 = vec!(double, 3);

alias Vector4i = vec!(int, 4), ivec4 = vec!(int, 4);
alias Vector4u = vec!(uint, 4), uvec4 = vec!(uint, 4);
alias Vector4f = vec!(float, 4), vec4 = vec!(float, 4);
alias Vector4d = vec!(double, 4), dvec4 = vec!(double, 4);
