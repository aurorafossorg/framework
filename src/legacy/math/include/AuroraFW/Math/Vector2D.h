/*****************************************************************************
**                                     __
**                                    / _|
**   __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
**  / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
** | (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
**  \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/
**
** Copyright (C) 2018-2019 Aurora Free Open Source Software.
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

/** @file AuroraFW/Math/Vector2D.h
 * 2D Vector/Vertex Header. This contains a vec2 struct that
 * represents a vector or vertex in 2D space.
 * @since snapshot20190930
 */

#ifndef AURORAFW_MATH_VECTOR2D_H
#define AURORAFW_MATH_VECTOR2D_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/STDL/STL/IStream.h>
#include <AuroraFW/STDL/STL/OStream.h>

#include <AuroraFW/Math/Vector3D.h>
#include <AuroraFW/Math/Vector4D.h>

#include <cmath>

namespace AuroraFW {
	namespace Math {
		template<typename T> struct vec3;
		template<typename T> struct vec4;
		
		/** A struct that represents a 2D vector. A struct that store's
		 * position in 2D coordinates, allows to manipulate them and also
		 * to do vector operations.
		 * @since snapshot20190930
		 */
		template<typename T>
		struct AFW_API vec2 {
			/** Constructs a vector with zero coordinates.
			 * @see vec2(const T& )
			 * @see vec2(const T& , const T& )
			 * @since snapshot20190930
			 */
			vec2();

			/** Constructs a vector with the given coordinates.
			 * @param scalar The T value to both x and y coordinates.
			 * @see vec2()
			 * @see vec2(const T& , const T& )
			 * @since snapshot20190930
			 */
			vec2(const T& );

			/** Constructs a vector with the given coordinates.
			 * @param x The x value for the x coordinate.
			 * @param y The y value for the y coordinate.
			 * @see vec2( )
			 * @see vec2(const T& )
			 * @since snapshot20190930
			 */
			vec2(const T& , const T& );

			/** Constructs a vector using the coordinates from the given Vector3D.
			 * The z value is not used.
			 * @param v The vec3<T> to get both the x and y coordinates from.
			 * @see vec2(const vec4<T>& )
			 * @since snapshot20190930
			 */
			explicit vec2(const vec3<T>& );

			/** Construct a vector using the coordinates from the given Vector4D.
			 * The z and w values are not used.
			 * @param v The vec4<T> to get both the x and y coordinates from.
			 * @see vec2(const vec3<T>& )
			 * @since snapshot20190930
			 */
			explicit vec2(const vec4<T>& );

			/** Adds the given vector's coordinates to this vector.
			 * @param v The vector to get the coordinates from.
			 * @return This vector with the added coordinates.
			 * @see add(const T& )
			 * @see add(const T& , const T& )
			 * @since snapshot20190930
			 */
			vec2& add(const vec2<T>& );

			/** Subtracts the given vector's coordinates to this vector.
			 * @param v The vector to get the coordinates from.
			 * @return This vector with the subtracted coordinates.
			 * @see subtract(const T& )
			 * @see subtract(const T& , const T& )
			 * @since snapshot20190930
			 */
			vec2& subtract(const vec2<T>& );

			/** Multiplies the given vector's coordinates to this vector.
			 * @param v The vector to get the coordinates from.
			 * @return This vector with the multiplied coordinates.
			 * @see multiply(const T& )
			 * @see multiply(const T& , const T& )
			 * @since snapshot20190930
			 */
			vec2& multiply(const vec2<T>& );

			/** Divides the given vector's coordinates to this vector.
			 * @param v The vector to get the coordinates from.
			 * @return This vector with the divided coordinates.
			 * @see divide(const T& )
			 * @see divide(const T& , const T& )
			 * @since snapshot20190930
			 */
			vec2& divide(const vec2<T>& );

			/** Adds the given value to this vector.
			 * @param val The value for both coordinates.
			 * @return This vector with the added coordinates.
			 * @see add(const vec2& )
			 * @see add(const T& , const T& )
			 * @since snapshot20190930
			 */
			vec2& add(const T& );

			/** Subtracts the given value to this vector.
			 * @param val The value for both coordinates.
			 * @return This vector with the subtracted coordinates.
			 * @see subtract(const vec2& )
			 * @see subtract(const T&& , const T&& )
			 * @since snapshot20190930
			 */
			vec2& subtract(const T& );

			/**
			 * Multiplies the given value to this vector.
			 * @param val The value for both coordinates.
			 * @return This vector with the multiplied coordinates.
			 * @see multiply(const vec2& )
			 * @see multiply(const T& , const T& )
			 * @since snapshot20190930
			 */
			vec2& multiply(const T& );

			/** Divides the given value to this vector.
			 * @param val The value for both coordinates.
			 * @return This vector with the divided coordinates.
			 * @see divide(const vec2& )
			 * @see divide(const T& , const T& )
			 * @since snapshot20190930
			 */
			vec2& divide(const T& );

			/** Adds the given values to this vector.
			 * @param valX The value for the x coordinate.
			 * @param valY The value for the y coordinate.
			 * @return This vector with the added coordinates.
			 * @see add(const vec2& )
			 * @see add(const T& )
			 * @since snapshot20190930
			 */
			vec2& add(const T& , const T& );

			/** Subtracts the given values to this vector.
			 * @param valX The value for the x coordinate.
			 * @param valY The value for the y coordinate.
			 * @return This vector with the subtracted coordinates.
			 * @see subtract(const vec2& )
			 * @see subtract(const T& )
			 * @since snapshot20190930
			 */
			vec2& subtract(const T&, const T& );

			/** Multiplies the given values to this vector.
			 * @param valX The value for the x coordinate.
			 * @param valY The value for the y coordinate.
			 * @return This vector with the multiplied coordinates.
			 * @see multiply(const vec2& )
			 * @see multiply(const T& )
			 * @since snapshot20190930
			 */
			vec2& multiply(const T& , const T& );

			/** Divides the given values to this vector.
			 * @param valX The value for the x coordinate.
			 * @param valY The value for the y coordinate.
			 * @return This vector with the divided coordinates.
			 * @see divide(const vec2& )
			 * @see divide(const T& )
			 * @since snapshot20190930
			 */
			vec2& divide(const T& , const T& );

			/** Sets the x coordinate to the given value.
			 * @param val The value of the x coordinate.
			 * @see setY(const T& )
			 * @since snapshot20190930
			 */
			void setX(const T& );

			/** Sets the y coordinate to the given value.
			 * @param val The value of the y coordinate.
			 * @see setX(const T& )
			 * @since snapshot20190930
			 */
			void setY(const T& );

			/**
			 * Adds the right vector's coordinates to the left one.
			 * @see operator-(const vec2& )
			 * @since snapshot20190930
			 */
			vec2<T> operator+(const vec2<T>& );

			/** Subtracts the right vector's coordinates to the left one.
			 * @see operator+(const vec2& )
			 * @since snapshot20190930
			 */
			vec2<T> operator-(const vec2<T>& );

			/** Multiplies the left vector's coordinates with the right vector.
			 * @see operator/(const vec2& )
			 * @since snapshot20190930
			 */
			vec2<T> operator*(const vec2<T>& );

			/** Divides the left vector's coordinates with the right vector.
			 * @see operator*(const vec2& )
			 * @since snapshot20190930
			 */
			vec2<T> operator/(const vec2<T>& );

			/** Adds the given value to the vector.
			 * @see operator-(const T& )
			 * @since snapshot20190930
			 */
			vec2<T> operator+(const T& );

			/** Subtracts the given value to the vector.
			 * @see operator+(const T& )
			 * @since snapshot20190930
			 */
			vec2<T> operator-(const T& );

			/** Multiplies vector with the given value.
			 * @see operator/(const T& )
			 * @since snapshot20190930
			 */
			vec2<T> operator*(const T& );

			/** Divides vector with the given value.
			 * @see operator*(const T& )
			 * @since snapshot20190930
			 */
			vec2<T> operator/(const T& );

			/** Adds the given vector to this vector.
			 * @see operator-=(const vec2& )
			 * @since snapshot20190930
			 */
			vec2<T>& operator+=(const vec2<T>& );

			/** Subtracts the given vector to this vector.
			 * @see operator+=(const vec2& )
			 * @since snapshot20190930
			 */
			vec2<T>& operator-=(const vec2<T>& );

			/** Multiplies this vector by the given vector.
			 * @see operator/=(const vec2& )
			 * @since snapshot20190930
			 */
			vec2<T>& operator*=(const vec2<T>& );

			/** Divides this vector by the given vector.
			 * @see operator*=(const vec2& )
			 * @since snapshot20190930
			 */
			vec2<T>& operator/=(const vec2<T>& );

			/** Adds the given value to this vector.
			 * @see operator-=(const T& )
			 * @since snapshot20190930
			 */
			vec2<T>& operator+=(const T& );

			/** Subtracts the given value to this vector.
			 * @see operator+=(const T& )
			 * @since snapshot20190930
			 */
			vec2<T>& operator-=(const T& );

			/** Multiplies this vector by the given value.
			 * @see operator/=(const T& )
			 * @since snapshot20190930
			 */
			vec2<T>& operator*=(const T& );

			/** Divides this vector by the given value.
			 * @see operator*=(const T& )
			 * @since snapshot20190930
			 */
			vec2<T>& operator/=(const T& );

			/** Compares this vector's coordinates with the given one
			 * and returns <code>true</code> if both coordinates are exactly equal.
			 * @see operator!=()
			 * @since snapshot20190930
			 */
			bool operator==(const vec2<T>& ) const;

			/** Compares this vector's coordinates with the given one
			 * and returns <code>true</code> if any of the coordinates are different.
			 * @see operator==()
			 * @since snapshot20190930
			 */
			bool operator!=(const vec2<T>& ) const;

			/** Compares this vector's coordinates with the given one
			 * and returns <code>true</code> if all the coordinates from this vector
			 * are lower than the coordinates from the given one.
			 * @see operator>()
			 * @since snapshot20190930
			 */
			bool operator<(const vec2<T>& ) const;

			/** Compares this vector's coordinates with the given one
			 * and returns <code>true</code> if all the coordinates from this vector
			 * are lower or equal than the coordinates from the
			 * given one.
			 * @see operator>=()
			 * @since snapshot20190930
			 */
			bool operator<=(const vec2<T>& ) const;

			/** Compares this vector's coordinates with the given one
			 * and returns <code>true</code> if all the coordinates from this vector
			 * are bigger than the coordinates from the given one
			 * @see operator<()
			 * @since snapshot20190930
			 */
			bool operator>(const vec2<T>& ) const;

			/** Compares this vector's coordinates with the given one
			 * and returns <code>true</code> if all the coordinates from this vector
			 * are bigger or equal than the coordinates from the
			 * given one
			 * @see operator<=()
			 * @since snapshot20190930
			 */
			bool operator>=(const vec2<T>& ) const;

			/** The exact same thing as length().
			 * @return The magnitude/length of this vector.
			 * @see length()
			 * @since snapshot20190930
			 */
			T magnitude() const;

			/** Returns the length of this vector.
			 * @return The magnitude/length of this vector.
			 * @see magnitude()
			 * @since snapshot20190930
			 */
			T length() const;

			/** Return true if any coordinate of this vector is null.
			 * @return <code>true</code> if any coordinate is NAN. <code>false</code> otherwhise.
			 * @since snapshot20190930
			 */
			bool isNull() const;

			/** Normalizes this vector. (It retains the angle of the
			 * vector but reduces it's length to 1)
			 * @see normalized()
			 * @since snapshot20190930
			 */
			void normalize();

			/** Returns a new normalized vector from this one. (It
			 * retains the angle of this vector but the length
			 * of the returned vector is 1)
			 * @return Normalized vector with the angle of this one.
			 * @see normalize()
			 * @since snapshot20190930
			 */
			vec2<T> normalized() const;

			/** Returns the value of the dot product between this
			 * vector and the given one.
			 * @param other The vector to dot product with this one.
			 * @return The dot product of the two vectors.
			 * @since snapshot20190930
			 */
			T dot(const vec2<T>& ) const;

			/** Returns the distance from this vector to a point, whose
			 * coordinates are on the given vector.
			 * @param other The vector representing the point's coordinates.
			 * @return Distance between this vector and the point.
			 * @see distanceToLine()
			 * @since snapshot20190930
			 */
			T distanceToPoint(const vec2<T>& ) const;

			/** Returns the smallest distance from this vector to a line,
			 * which is defined by a point and angle, provided by the
			 * two given vectors.
			 * @param point A vector representing the point's coordinates.
			 * @param direction A vector representing the direction of the line.
			 * @return The smallest distance between this vector and the line.
			 * @see distanceToPoint()
			 * @since snapshot20190930
			 */
			T distanceToLine(const vec2<T>& , const vec2<T>& ) const;

			/** Returns the vector as a string.
			 * @since snapshot20190930
			 */
			std::string toString() const;

			/** Returns the vector as a stream.
			 * @since snapshot20190930
			 */
			template<typename t>
			friend std::ostream& operator<<(std::ostream& , const vec2<t>& );

			/** The vector's x coordinate.
			 * @see y
			 * @since snapshot20190930
			 */
			T x;

			/** The vector's y coordinate.
			 * @see x
			 * @since snapshot20190930
			 */
			T y;
		};

		typedef vec2<float> Vector2D;

		// Inline definitions
		template<typename T>
		inline T vec2<T>::magnitude() const
		{
			return length();
		}

		template<typename T>
		inline bool vec2<T>::isNull() const
		{
			return std::isnan(x) || std::isnan(y);
		}

		// Template implementation
		// Constructors
		template<typename T>
		vec2<T>::vec2()
			: x(0.0f), y(0.0f)
		{}

		template<typename T>
		vec2<T>::vec2(const T& scalar)
			: x(scalar), y(scalar)
		{}

		template<typename T>
		vec2<T>::vec2(const T& x, const T& y)
			: x(x), y(y)
		{}

		template<typename T>
		vec2<T>::vec2(const vec3<T>& v)
			: x(v.x), y(v.y)
		{}

		template<typename T>
		vec2<T>::vec2(const vec4<T>& v)
			: x(v.x), y(v.y)
		{}

		// Operations
		// Using an existing vec2
		template<typename T>
		vec2<T>& vec2<T>::add(const vec2<T>& v)
		{
			x += v.x;
			y += v.y;

			return *this;
		}

		template<typename T>
		vec2<T>& vec2<T>::subtract(const vec2<T>& v)
		{
			x -= v.x;
			y -= v.y;

			return *this;
		}

		template<typename T>
		vec2<T>& vec2<T>::multiply(const vec2<T>& v)
		{
			x *= v.x;
			y *= v.y;

			return *this;
		}

		template<typename T>
		vec2<T>& vec2<T>::divide(const vec2<T>& v)
		{
			x /= v.x;
			y /= v.y;

			return *this;
		}

		// Using a value (scalar)
		template<typename T>
		vec2<T>& vec2<T>::add(const T& val)
		{
			x += val;
			y += val;

			return *this;
		}

		template<typename T>
		vec2<T>& vec2<T>::subtract(const T& val)
		{
			x -= val;
			y -= val;

			return *this;
		}

		template<typename T>
		vec2<T>& vec2<T>::multiply(const T& val)
		{
			x *= val;
			y *= val;

			return *this;
		}

		template<typename T>
		vec2<T>& vec2<T>::divide(const T& val)
		{
			x /= val;
			y /= val;

			return *this;
		}

		// Using an x and y value
		template<typename T>
		vec2<T>& vec2<T>::add(const T& valX, const T& valY)
		{
			x += valX;
			y += valY;

			return *this;
		}

		template<typename T>
		vec2<T>& vec2<T>::subtract(const T& valX, const T& valY)
		{
			x -= valX;
			y -= valY;

			return *this;
		}

		template<typename T>
		vec2<T>& vec2<T>::multiply(const T& valX, const T& valY)
		{
			x *= valX;
			y *= valY;

			return *this;
		}

		template<typename T>
		vec2<T>& vec2<T>::divide(const T& valX, const T& valY)
		{
			x /= valX;
			y /= valY;

			return *this;
		}

		template<typename T>
		void vec2<T>::setX(const T& val) {
			x = val;
		}

		template<typename T>
		void vec2<T>::setY(const T& val) {
			y = val;
		}

		// Operators
		template<typename T>
		vec2<T> vec2<T>::operator+(const vec2<T>& right)
		{
			return add(right);
		}

		template<typename T>
		vec2<T> vec2<T>::operator-(const vec2<T>& right)
		{
			return subtract(right);
		}

		template<typename T>
		vec2<T> vec2<T>::operator*(const vec2<T>& right)
		{
			return multiply(right);
		}

		template<typename T>
		vec2<T> vec2<T>::operator/(const vec2<T>& right)
		{
			return divide(right);
		}

		template<typename T>
		vec2<T> vec2<T>::operator+(const T& value)
		{
			return vec2<T>(x + value, y + value);
		}

		template<typename T>
		vec2<T> vec2<T>::operator-(const T& value)
		{
			return vec2<T>(x - value, y - value);
		}

		template<typename T>
		vec2<T> vec2<T>::operator*(const T& value)
		{
			return vec2<T>(x * value, y * value);
		}

		template<typename T>
		vec2<T> vec2<T>::operator/(const T& value)
		{
			return vec2<T>(x / value, y / value);
		}

		template<typename T>
		vec2<T>& vec2<T>::operator+=(const vec2<T>& other)
		{
			return add(other);
		}

		template<typename T>
		vec2<T>& vec2<T>::operator-=(const vec2<T>& other)
		{
			return subtract(other);
		}

		template<typename T>
		vec2<T>& vec2<T>::operator*=(const vec2<T>& other)
		{
			return multiply(other);
		}

		template<typename T>
		vec2<T>& vec2<T>::operator/=(const vec2<T>& other)
		{
			return divide(other);
		}

		template<typename T>
		vec2<T>& vec2<T>::operator+=(const T& value)
		{
			return add(value);
		}

		template<typename T>
		vec2<T>& vec2<T>::operator-=(const T& value)
		{
			return subtract(value);
		}

		template<typename T>
		vec2<T>& vec2<T>::operator*=(const T& value)
		{
			return multiply(value);
		}

		template<typename T>
		vec2<T>& vec2<T>::operator/=(const T& value)
		{
			return divide(value);
		}

		template<typename T>
		bool vec2<T>::operator==(const vec2<T>& other) const
		{
			return x == other.x && y == other.y;
		}

		template<typename T>
		bool vec2<T>::operator!=(const vec2<T>& other) const
		{
			return !(*this == other);
		}

		template<typename T>
		bool vec2<T>::operator<(const vec2<T>& other) const
		{
			return x < other.x && y < other.y;
		}

		template<typename T>
		bool vec2<T>::operator<=(const vec2<T>& other) const
		{
			return x <= other.x && y <= other.y;
		}

		template<typename T>
		bool vec2<T>::operator>(const vec2<T>& other) const
		{
			return x > other.x && y > other.y;
		}

		template<typename T>
		bool vec2<T>::operator>=(const vec2<T>& other) const
		{
			return x >= other.x && y >= other.y;
		}

		// Vector operations
		template<typename T>
		T vec2<T>::length() const
		{
			return sqrt(x * x + y * y);
		}

		template<typename T>
		void vec2<T>::normalize()
		{
			T length = magnitude();
			this->x /= length;
			this->y /= length;
		}

		template<typename T>
		vec2<T> vec2<T>::normalized() const
		{
			T length = magnitude();
			return vec2<T>(x / length, y / length);
		}

		template<typename T>
		T vec2<T>::dot(const vec2<T>& other) const
		{
			return x * other.x + y * other.y;
		}

		template<typename T>
		T vec2<T>::distanceToPoint(const vec2<T>& other) const
		{
			T a = x - other.x;
			T b = y - other.y;
			return sqrt(a * a + b * b);
		}

		template<typename T>
		T vec2<T>::distanceToLine(const vec2<T>& point, const vec2<T>& direction) const
		{
			// TODO: Find the formula to get the distance
		}

		template<typename T>
		std::string vec2<T>::toString() const
		{
			return "vec2<T>: (" + std::to_string(x) + ", " + std::to_string(y) + ")";
		}

		template<typename T>
		std::ostream& operator<<(std::ostream& stream, const vec2<T>& vector)
		{
			stream << vector.toString();
			return stream;
		}
	}
}

#endif // AURORAFW_MATH_VECTOR2D_H
