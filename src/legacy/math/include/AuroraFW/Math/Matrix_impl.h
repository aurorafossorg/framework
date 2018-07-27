/*****************************************************************************
**                                    / _|
**   __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
**  / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
** | (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
**  \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/
**
** Copyright (C) 2018 Aurora Free Open Source Software.
**
** This file is part of the Aurora Free Open Source Software. This
** organization promote free and open source software that you can
** redistribute and/or modify under the terms of the GNU Lesser General
** Public License Version 3 as published by the Free Software Foundation or
** (at your option) any later version approved by the Aurora Free Open Source
** Software Organization. The license is available in the package root path
** as 'LICENSE' file. Please review the following information to ensure the
** GNU Lesser General Public License version 3 requirements will be met:
** https://www.gnu.org/licenses/lgpl.html .
**
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3 or later as published by the Free Software
** Foundation. Please review the following information to ensure the GNU
** General Public License requirements will be met:
** http://www.gnu.org/licenses/gpl-3.0.html.
**
** NOTE: All products, services or anything associated to trademarks and
** service marks used or referenced on this file are the property of their
** respective companies/owners or its subsidiaries. Other names and brands
** may be claimed as the property of others.
**
** For more info about intellectual property visit: aurorafoss.org or
** directly send an email to: contact (at) aurorafoss.org .
*****************************************************************************/

#ifndef AURORAFW_MATH_MATRIX_H
	#error "Should define Matrix.h first!"
#endif

#ifndef AURORAFW_MATH_MATRIX_IMPL_H
#define AURORAFW_MATH_MATRIX_IMPL_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

namespace AuroraFW {
	namespace Math {
		template<typename T, uint m, uint n>
		mat<T, m, n>::mat()
		{
			memset(matrix, 0, m * n * sizeof(T));
		}

		template<typename T, uint m, uint n>
		mat<T, m, n>::mat(const mat<T, m, n> &mat)
		{
			for(int i = 0; i< m; i++)
			{
				for(int j = 0; j< n; j++)
				{
					matrix[i][j] = mat.matrix[i][j];
				}
			}
		}

		template<typename T, uint m, uint n>
		constexpr mat<T, m, n>::mat(T diagonal)
		{
			static_assert(m == n, "invalid diagonal matrix");
			memset(matrix, 0, m * n * sizeof(T));
			matrix[0][0] = diagonal;
			matrix[1][1] = diagonal;
			matrix[2][2] = diagonal;
			matrix[3][3] = diagonal;
		}

		template<typename T, uint m, uint n>
		mat<T, m, n>::mat(T* mat)
		{
			memcpy(m, mat, 4 * 4 * sizeof(T));
		}

		template<typename T, uint m, uint n>
		mat<T, m, n> mat<T, m, n>::identity()
		{
			return mat(static_cast<T>(1));
		}

		template<typename T, uint m, uint n>
		mat<T, m, n>& mat<T, m, n>::multiply(const mat<T, m, n>& mat)
		{
			T data[4][4];
			for (int row = 0; row < 4; row++)
			{
				for (int col = 0; col < 4; col++)
				{
					T sum = static_cast<T>(0);
					for (int e = 0; e < 4; e++)
					{
						sum += matrix[e][row] * mat.matrix[col][e];
					}
					data[col][row] = sum;
				}
			}
			memcpy(m, data, 4 * 4 * sizeof(float));
			return *this;
		}

		template<typename T, uint m, uint n>
		vec3<T> mat<T, m, n>::multiply(const vec3<T>& vec) const
		{
			return vec.multiply(*this);
		}

		template<typename T, uint m, uint n>
		vec4<T> mat<T, m, n>::multiply(const vec4<T>& vec) const
		{
			return vec.multiply(*this);
		}

		template<typename T, uint m, uint n>
		mat<T, m, n> mat<T, m, n>::operator*(const mat<T, m, n> &mat)
		{
			return multiply(mat);
		}

		template<typename T, uint m, uint n>
		mat<T, m, n>& mat<T, m, n>::operator*=(const mat<T, m, n> &mat)
		{
			return multiply(mat);
		}

		template<typename T, uint m, uint n>
		vec3<T> mat<T, m, n>::operator*(const vec3<T> &vec)
		{
			return multiply(vec);
		}

		template<typename T, uint m, uint n>
		vec4<T> mat<T, m, n>::operator*(const vec4<T> &vec)
		{
			return multiply(vec);
		}

		template<typename T, uint m, uint n>
		mat<T, m, n> mat<T, m, n>::orthographic(T left, T right, T bottom, T top, T near_, T far_)
		{
			mat<T, m, n> ret(1.0f);

			ret.matrix[0][0] = 2.0f / (right - left);
			ret.matrix[1][1] = 2.0f / (top - bottom);
			ret.matrix[2][2] = 2.0f / (near_ - far_);
			ret.matrix[3][0] = (left + right) / (left - right);
			ret.matrix[3][1] = (bottom + top) / (bottom - top);
			ret.matrix[3][2] = (far_ + near_) / (far_ - near_);

			return ret;
		}

		template<typename T, uint m, uint n>
		mat<T, m, n> mat<T, m, n>::translate(const vec3<T>& vec)
		{
			mat<T, m, n> ret(1.0f);

			ret.matrix[3][0] = vec.x;
			ret.matrix[3][1] = vec.y;
			ret.matrix[3][2] = vec.z;

			return ret;
		}
	}
}

#endif // AURORAFW_MATH_MATRIX_IMPL_H
