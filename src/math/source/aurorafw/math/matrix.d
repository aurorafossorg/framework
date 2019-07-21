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

module aurorafw.math.matrix;

/** @file aurorafw/math/matrix.d
 * Variable Matrix file. This contains a variable matrix struct that
 * represents a grid with size of M * N.
 * @author Luís Ferreira <contact@lsferreira.net>
 * @since snapshot20180509
 */

/** A struct that represents a variable matrix. A struct that store's
 * N*M array, allows to manipulate it.
 * @since snapshot20180930
 */
@nogc pure @safe struct Matrix(T, size_t M, size_t N) {
	this(T initNumber)
	in {
		static assert(M == N, "invalid diagonal matrix");
	}
	body {
		foreach(i; 0 .. M)
			matrix[i * M + i] = initNumber;
	}

	this(immutable ref Matrix!(T, M, N) mat)
	{
		this.matrix = mat.matrix.dup;
	}

	this(T[M*N] matrix)
	{
		this.matrix = matrix;
	}

	this(T[] matrix)
	in {
		assert(matrix.length == M * N, "array doesn't have the same size");
	}
	body {
		this.matrix = matrix;
	}

	pragma(inline) static Matrix!(T, M, N) zero()
	{
		Matrix!(T, M, N) ret;
		return ret;
	}

	pragma(inline) static Matrix!(T, M, N) identity()
	{
		Matrix!(T, M, N) ret;
		ret.setIdentity();
		return ret;
	}

	void setIdentity() @property
	{
		foreach(size_t x; 0 .. M)
			foreach(size_t y; 0 .. N)
				if (y == x)
					matrix[x * M + y] = 1;
				else
					matrix[x * M + y] = 0;
	}

	Matrix!(T, M, N) opBinary(string op)(T val)
	{
		Matrix!(T, M, N) ret;
		foreach(i; 0 .. M)
			foreach(j; 0 .. N)
				mixin("ret.matrix[i * M + j] = this.matrix[i * M + j] "~op~" val;");
		return ret;
	}

	Matrix!(T, M, N) opBinary(string op)(Matrix!(T, M, N) val) if(op == "+" || op == "-")
	{
		Matrix!(T, M, N) ret;
		foreach(i; 0 .. M)
			foreach(j; 0 .. N)
				mixin("ret[i,j] = this[i,j]"~op~"val[i,j];");

		return ret;
	}

	Matrix!(T, M, N) opBinary(string op : "*")(Matrix!(T, M, N) val)
	{
		Matrix!(T, M, N) res;

		foreach (i; 0 .. M)
			foreach (j; 0 .. N)
			{
				T sumProduct = 0;
				foreach (k; 0 .. N)
					sumProduct += this[i, k] * val[k, j];
				res[i, j] = sumProduct;
			}

		return res;
	}

	bool opEquals(Matrix!(T, M, N) mat) const
	{
		return matrix == mat.matrix;
	}

	T opIndex(in size_t m, in size_t n) const
	in
	{
		assert (n < N && m < M, "index out of bounds");
	}
	body
	{
		return matrix[m * M + n];
	}

	T opIndex(in size_t i) const
	in
	{
		assert (i < N * M, "index out of bounds");
	}
	body
	{
		return matrix[i];
	}

	T opIndexAssign(in T val, in size_t m, in size_t n)
	in
	{
		assert (n < N && m < M, "index out of bounds");
	}
	body
	{
		return (matrix[m * M + n] = val);
	}

	T[] opSliceAssign(in T val, in size_t i1, in size_t i2)
	in
	{
		assert (i1 < N * M && i2 < N * M, "index out of bounds");
	}
	body
	{
		return (matrix[i1..i2] = val);
	}

	T[] opSliceAssign(in T val)
	{
		return (matrix[] = val);
	}

	T[M*N] matrix;
}

alias Matrix!(float, 2, 2) Matrix2x2f, Matrix2f, mat2;
alias Matrix!(float, 3, 3) Matrix3x3f, Matrix3f, mat3;
alias Matrix!(float, 4, 4) Matrix4x4f, Matrix4f, mat4;
alias Matrix!(double, 2, 2) Matrix2x2d, Matrix2d;
alias Matrix!(double, 3, 3) Matrix3x3d, Matrix3d;
alias Matrix!(double, 4, 4) Matrix4x4d, Matrix4d;

@("Matrix: Identity")
unittest {
	Matrix!(int, 3, 3) mat = Matrix!(int, 3, 3).identity;
	int[3*3] matIdentity =
		[1, 0, 0,
		 0, 1, 0,
		 0, 0, 1];

	assert(matIdentity == mat.matrix);
}


@("Matrix: Add operation")
unittest {
	Matrix!(int, 3, 3) mat = Matrix!(int, 3, 3).identity;
	int[3 * 3] matIdentity =
		[2, 1, 1,
		 1, 2, 1,
		 1, 1, 2];

	assert(matIdentity == (mat + 1).matrix);
}

@("Matrix: Subtract operation")
unittest {
	Matrix!(int, 3, 3) mat = Matrix!(int, 3, 3).identity;
	int[3 * 3] matIdentity =
		[0, -1, -1,
		 -1, 0, -1,
		 -1, -1, 0];

	assert(matIdentity == (mat - 1).matrix);
}
