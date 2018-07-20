/****************************************************************************
** ┌─┐┬ ┬┬─┐┌─┐┬─┐┌─┐  ┌─┐┬─┐┌─┐┌┬┐┌─┐┬ ┬┌─┐┬─┐┬┌─
** ├─┤│ │├┬┘│ │├┬┘├─┤  ├┤ ├┬┘├─┤│││├┤ ││││ │├┬┘├┴┐
** ┴ ┴└─┘┴└─└─┘┴└─┴ ┴  └  ┴└─┴ ┴┴ ┴└─┘└┴┘└─┘┴└─┴ ┴
** A Powerful General Purpose Framework
** More information in: https://aurora-fw.github.io/
**
** Copyright (C) 2017 Aurora Framework, All rights reserved.
**
** This file is part of the Aurora Framework. This framework is free
** software; you can redistribute it and/or modify it under the terms of
** the GNU Lesser General Public License version 3 as published by the
** Free Software Foundation and appearing in the file LICENSE included in
** the packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************/

#ifndef AURORAFW_MATH_MATRIX_H
#define AURORAFW_MATH_MATRIX_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/STDL/STL/OStream.h>
#include <AuroraFW/STDL/LibC/String.h>
#include <AuroraFW/Math/Vector3D.h>
#include <AuroraFW/Math/Vector4D.h>

namespace AuroraFW {
	namespace Math {
		template<typename T, uint m, uint n>
		struct AFW_API mat
		{
			mat();
			constexpr mat(T );
			mat(const mat<T, m, n> &);
			mat(T* );

			mat &multiply(const mat<T, m, n> &);
			vec3<T> multiply(const vec3<T> &) const;
			vec4<T> multiply(const vec4<T> &) const;

			mat<T, m, n> operator*(const mat<T, m, n> &);
			mat<T, m, n>& operator*=(const mat<T, m, n> &);
			vec3<T> operator*(const vec3<T> &) const;
			vec3<T> operator*(const vec3<T> &);
			vec3<T> operator*(const vec4<T> &) const;
			vec4<T> operator*(const vec4<T> &);

			mat<T, m, n> &invert();

			vec4<T> getColumn(uint_t) const;
			vec3<T> getPos() const;

			void setColumn(uint_t, const vec4<T> &);
			void setPos(const vec3<T> &);

			//Static methods
			static mat<T, m, n> identity();

			static mat<T, m, n> orthographic(T , T , T , T , T , T );
			static mat<T, m, n> perspective(T , T , T , T );
			static mat<T, m, n> lookAt(const vec3<T> &, const vec3<T> &, const vec3<T> &);

			static mat<T, m, n> translate(const vec3<T> &);
			static mat<T, m, n> rotation(T, const vec3<T> &);
			static mat<T, m, n> scale(const vec3<T> &);
			static mat<T, m, n> invert(const mat4<T> &);
			static mat<T, m, n> transpose(const mat4<T> &);

			std::string toString() const;

			template<typename t>
			friend std::ostream& operator<<(std::ostream& , const vec3<T>& );

			T matrix[m][n];
		};
		typedef mat<float, 4, 4> Matrix4x4;
		typedef mat<float, 4, 3> Matrix4x3;
		typedef mat<float, 4, 2> Matrix4x2;

		typedef mat<float, 3, 4> Matrix3x4;
		typedef mat<float, 3, 3> Matrix3x3;
		typedef mat<float, 3, 2> Matrix3x2;

		typedef mat<float, 2, 4> Matrix2x4;
		typedef mat<float, 2, 3> Matrix2x3;
		typedef mat<float, 2, 2> Matrix2x2;
	}
}

#include <AuroraFW/Math/Matrix_impl.h>

#endif // AURORAFW_MATH_MATRIX_H
