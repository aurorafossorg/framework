module aurorafw.math.matrix;

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

/** @file aurorafw/math/matrix.d
 * Variable Matrix file. This contains a variable matrix struct that
 * represents a grid with size of M * N.
 * @author Luís Ferreira <contact@lsferreira.net>
 * @since snapshot20180509
 */

/** A struct that represents a variable matrix. A struct that store's
 * N*M array, allows to manipulate it.
 * @since snapshot20190930
 */
@nogc pure @safe struct mat(T, size_t M, size_t N) {
	this(T num)
	in {
		static assert(M == N, "invalid diagonal matrix");
	}
	body {
		foreach(size_t i; 0..M)
			matrix[i * M + i] = num;
	}

	this(immutable ref mat!(T, M, N) mat)
	{
		this = mat;
	}

	this(T[M*N] arr)
	{
		matrix[] = arr;
	}

	this(T[] arr)
	in {
		assert(arr.length == M * N, "array doesn't have the same size");
	}
	body {
		matrix = arr;
	}

	pragma(inline) static mat!(T, M, N) zero()
	{
		mat!(T, M, N) ret;
		ret.matrix[0..N*M] = 0;
		return ret;
	}

	pragma(inline) static mat!(T, M, N) identity()
	{
		mat!(T, M, N) ret;
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

	bool opEquals(mat!(T, M, N) mat) const
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

alias mat!(float, 2, 2) Matrix2x2f, Matrix2f;
alias mat!(float, 3, 3) Matrix3x3f, Matrix3f;
alias mat!(float, 4, 4) Matrix4x4f, Matrix4f;
alias mat!(double, 2, 2) Matrix2x2d, Matrix2d;
alias mat!(double, 3, 3) Matrix3x3d, Matrix3d;
alias mat!(double, 4, 4) Matrix4x4d, Matrix4d;

alias Matrix2x2f mat2;
alias Matrix3x3f mat3;
alias Matrix4x4f mat4;