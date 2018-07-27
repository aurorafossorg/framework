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

/** @file AuroraFW/Math/Vector3D.h
 * 3D Vector/Vertex header. This contains a Vector3d struct that
 * represents a vector or vertex in 3D space.
 * @since snapshot20170930
 */
#ifndef AURORAFW_MATH_VECTOR3D_H
#define AURORAFW_MATH_VECTOR3D_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/STDL/STL/OStream.h>

#include <AuroraFW/Math/Vector2D.h>
#include <AuroraFW/Math/Vector4D.h>

#include <cmath>

namespace AuroraFW {
	namespace Math {
		template<typename T> struct vec2;
		template<typename T> struct vec4;
		template<typename T> struct mat4;

		/**
		 * A struct that represents a 3D vector. A struct that store's
		 * position in 3D coordinates, allows to manipulate them and also
		 * to do vector operations.
		 * @since snapshot20170930
		 */
		template<typename T>
		struct AFW_API vec3 {
			/** Constructs a vector with zero coordinates.
			 * @see vec3(const T& )
			 * @see vec3(const T& , const T& )
			 * @see vec3(const T& , const T& , const T& )
			 * @since snapshot20170930
			 */
			vec3();

			/** Constructs a vector with the given coordinates.
			 * @param scalar The T value to the x, y and z coordinates.
			 * @see vec3()
			 * @see vec3(const T& , const T& )
			 * @see vec3(const T& , const T& , const T& )
			 * @since snapshot20170930
			 */
			vec3(const T& );

			/** Constructs a vector with the given coordinates.
			 * The z value will be defined to 0.
			 * @param x The x value for the x coordinate.
			 * @param y The y value for the y coordinate.
			 * @see vec3( )
			 * @see vec3(const T& )
			 * @see vec3(const T& , const T& , const T& )
			 * @since snapshot20170930
			 */
			vec3(const T& , const T& );

			/** Constructs a vector with the given coordinates.
			 * @param x The x value for the x coordinate.
			 * @param y The y value for the y coordinate.
			 * @param x The z value for the z coordinate.
			 * @see vec3( )
			 * @see vec3(const T& )
			 * @see vec3(const T& , const T& )
			 * @since snapshot20170930
			 */
			vec3(const T& , const T& , const T& );

			/** Constructs a vector using the coordinates from the given vec2<T>.
			 * The z value will be defined as 0.
			 * @param v The vec2<T> to get both the x and y coordinates from.
			 * @see vec3(const vec4<T>& )
			 * @since snapshot20170930
			 */
			vec3(const vec2<T>& );

			/** Constructs a vector using the coordinates from the given vec3<T>.
			 * The z value will be defined as 0.
			 * @param v The vec2<T> to get both the x and y coordinates from.
			 * @see vec3(const vec4<T>& )
			 * @since snapshot20170930
			 */
			vec3(const vec3<T> &);

			/** Construct a vector using the coordinates from the given vec4<T>.
			 * The w value is not used.
			 * @param v The vec4<T> to get the x, y and z coordinates from.
			 * @see vec3(const vec2<T>& )
			 * @since snapshot20170930
			 */
			vec3(const vec4<T>& );

			/** Adds the given vector's coordinates to this vector.
			 * @param v The vector to get the coordinates from.
			 * @return This vector with the added coordinates.
			 * @see add(const T& )
			 * @see add(const T& , const T& , const T& )
			 * @since snapshot20170930
			 */
			vec3<T>& add(const vec3<T>& );

			/** Subtracts the given vector's coordinates to this vector.
			 * @param v The vector to get the coordinates from.
			 * @return This vector with the subtracted coordinates.
			 * @see subtract(const T& )
			 * @see subtract(const T& , const T& , const T& )
			 * @since snapshot20170930
			 */
			vec3<T>& subtract(const vec3<T>& );

			/** Multiplies the given vector's coordinates to this vector.
			 * @param v The vector to get the coordinates from.
			 * @return This vector with the multiplied coordinates.
			 * @see multiply(const T& )
			 * @see multiply(const T& , const T& , const T& )
			 * @since snapshot20170930
			 */
			vec3<T>& multiply(const vec3<T>& );

			/** Divides the given vector's coordinates to this vector.
			 * @param v The vector to get the coordinates from.
			 * @return This vector with the divided coordinates.
			 * @see divide(const T& )
			 * @see divide(const T& , const T& , const T& )
			 * @since snapshot20170930
			 */
			vec3<T>& divide(const vec3<T>& );

			/** Adds the given value to this vector.
			 * @param val The value for all three coordinates.
			 * @return This vector with the added coordinates.
			 * @see add(const vec3<T>& )
			 * @see add(const T& , const T& , const T& )
			 * @since snapshot20170930
			 */
			vec3<T>& add(const T& );

			/** Subtracts the given value to this vector.
			 * @param val The value for all three coordinates.
			 * @return This vector with the subtracted coordinates.
			 * @see subtract(const vec3<T>& )
			 * @see subtract(const T& , const T& , const T& )
			 * @since snapshot20170930
			 */
			vec3<T>& subtract(const T& );

			/** Multiplies the given value to this vector.
			 * @param val The value for all three coordinates.
			 * @return This vector with the multiplied coordinates.
			 * @see multiply(const vec3<T>& )
			 * @see multiply(const T& , const T& , const T& )
			 * @since snapshot20170930
			 */
			vec3<T>& multiply(const T& );

			vec3<T> multiply(const mat4<T> &) const;

			/** Divides the given value to this vector.
			 * @param val The value for all three coordinates.
			 * @return This vector with the divided coordinates.
			 * @see divide(const vec3<T>& )
			 * @see divide(const T& , const T& , const T& )
			 * @since snapshot20170930
			 */
			vec3<T>& divide(const T& );

			/** Adds the given values to this vector.
			 * @param valX The value for the x coordinate.
			 * @param valY The value for the y coordinate.
			 * @param valZ The value for the z coordinate.
			 * @return This vector with the added coordinates.
			 * @see add(const vec3<T>& )
			 * @see add(const T& )
			 * @since snapshot20170930
			 */
			vec3<T>& add(const T& , const T& , const T& );

			/** Subtracts the given values to this vector.
			 * @param valX The value for the x coordinate.
			 * @param valY The value for the y coordinate.
			 * @param valZ The value for the z coordinate.
			 * @return This vector with the subtracted coordinates.
			 * @see subtract(const vec3<T>& )
			 * @see subtract(const T& )
			 * @since snapshot20170930
			 */
			vec3<T>& subtract(const T& , const T& , const T& );

			/** Multiplies the given values to this vector.
			 * @param valX The value for the x coordinate.
			 * @param valY The value for the y coordinate.
			 * @param valZ The value for the z coordinate.
			 * @return This vector with the multiplied coordinates.
			 * @see multiply(const vec3<T>& )
			 * @see multiply(const T& )
			 * @since snapshot20170930
			 */
			vec3<T>& multiply(const T& , const T& , const T& );

			/** Divides the given values to this vector.
			 * @param valX The value for the x coordinate.
			 * @param valY The value for the y coordinate.
			 * @param valZ The value for the z coordinate.
			 * @return This vector with the divided coordinates.
			 * @see divide(const vec3<T>& )
			 * @see divide(const T& )
			 * @since snapshot20170930
			 */
			vec3<T>& divide(const T& , const T& , const T& );

			/** Sets the x coordinate to the given value.
			 * @param val The value of the x coordinate.
			 * @see setY(const T& )
			 * @see setZ(const T& )
			 * @since snapshot20170930
			 */
			void setX(const T& );

			/** Sets the y coordinate to the given value.
			 * @param val The value of the y coordinate.
			 * @see setX(const T& )
			 * @see setZ(const T& )
			 * @since snapshot20170930
			 */
			void setY(const T& );

			/** Sets the z coordinate to the given value.
			 * @param val The value of the z coordinate.
			 * @see setX(const T& )
			 * @see setY(const T& )
			 * @since snapshot20170930
			 */
			void setZ(const T& );

			/** Gets the x coordinate.
			 * @see getY()
			 * @see getZ()
			 * @since snapshot20171003
			 */
			T getX() const;

			/** Gets the y coordinate.
			 * @see getX()
			 * @see getZ()
			 * @since snapshot20171003
			 */
			T getY() const;

			/** Gets the z coordinate.
			 * @see getX()
			 * @see getY()
			 * @since snapshot20171003
			 */
			T getZ() const;

			/** Adds the right vector's coordinates to the left one.
			 * @see operator-(const vec3<T>& )
			 * @since snapshot20170930
			 */
			vec3<T> operator+(const vec3<T>& );

			/** Subtracts the right vector's coordinates to the left one.
			 * @see operator+(const vec3<T>& )
			 * @since snapshot20170930
			 */
			vec3<T> operator-(const vec3<T>& );

			/** Multiplies the left vector's coordinates with the right vector.
			 * @see operator/(const vec3<T>& )
			 * @since snapshot20170930
			 */
			vec3<T> operator*(const vec3<T>& );

			/** Divides the left vector's coordinates with the right vector.
			 * @see operator*(const vec3<T>& )
			 * @since snapshot20170930
			 */
			vec3<T> operator/(const vec3<T>& );

			/** Adds the given value to the vector.
			 * @see operator-(const T& )
			 * @since snapshot20170930
			 */
			vec3<T> operator+(const T& );

			/** Subtracts the given value to the vector.
			 * @see operator+(const T& )
			 */
			vec3<T> operator-(const T& );

			/** Multiplies vector with the given value.
			 * @see operator/(const T& )
			 * @since snapshot20170930
			 */
			vec3<T> operator*(const T& );

			/** Divides vector with the given value.
			 * @see operator*(const T& )
			 * @since snapshot20170930
			 */
			vec3<T> operator/(const T& );

			/** Adds the given vector to this vector.
			 * @see operator-=(const vec3<T>& )
			 * @since snapshot20170930
			 */
			vec3<T>& operator+=(const vec3<T>& );

			/** Subtracts the given vector to this vector.
			 * @see operator+=(const vec3<T>& )
			 * @since snapshot20170930
			 */
			vec3<T>& operator-=(const vec3<T>& );

			/** Multiplies this vector by the given vector.
			 * @see operator/=(const vec3<T>& )
			 * @since snapshot20170930
			 */
			vec3<T>& operator*=(const vec3<T>& );

			/** Divides this vector by the given vector.
			 * @see operator*=(const vec3<T>& )
			 * @since snapshot20170930
			 */
			vec3<T>& operator/=(const vec3<T>& );

			/** Adds the given value to this vector.
			 * @see operator-=(const T& )
			 * @since snapshot20170930
			 */
			vec3<T>& operator+=(const T& );

			/** Subtracts the given value to this vector.
			 * @see operator+=(const T& )
			 * @since snapshot20170930
			 */
			vec3<T>& operator-=(const T& );

			/** Multiplies this vector by the given value.
			 * @see operator/=(const T& )
			 * @since snapshot20170930
			 */
			vec3<T>& operator*=(const T& );

			/** Divides this vector by the given value.
			 * @see operator*=(const T& )
			 * @since snapshot20170930
			 */
			vec3<T>& operator/=(const T& );

			/**
			 * Compares this vector's coordinates with the given one
			 * and returns <code>true</code> if all three coordinates are exactly equal.
			 * @see operator!=()
			 * @since snapshot20170930
			 */
			bool operator==(const vec3<T>& ) const;

			/**
			 * Compares this vector's coordinates with the given one
			 * and returns <code>true</code> if any of the coordinates are different.
			 * @see operator==()
			 * @since snapshot20170930
			 */
			bool operator!=(const vec3<T>& ) const;

			/**
			 * Compares this vector's coordinates with the given one
			 * and returns <code>true</code> if all the coordinates from this vector
			 * are lower than the coordinates from the given one.
			 * @see operator>()
			 * @since snapshot20170930
			 */
			bool operator<(const vec3<T>& ) const;

			/**
			 * Compares this vector's coordinates with the given one
			 * and returns <code>true</code> if all the coordinates from this vector
			 * are lower or equal than the coordinates from the
			 * given one.
			 * @see operator>=()
			 * @since snapshot20170930
			 */
			bool operator<=(const vec3<T>& ) const;

			/**
			 * Compares this vector's coordinates with the given one
			 * and return <code>true</code> if all the coordinates from this vector
			 * are bigger than the coordinates from the given one
			 * @see operator<()
			 * @since snapshot20170930
			 */
			bool operator>(const vec3<T>& ) const;

			/**
			 * Compares this vector's coordinates with the given one
			 * and return <code>true</code> if all the coordinates from this vector
			 * are bigger or equal than the coordinates from the
			 * given one
			 * @see operator<=()
			 * @since snapshot20170930
			 */
			bool operator>=(const vec3<T>& ) const;

			/**
			 * The exact same thing as length().
			 * @return The magnitude/length of this vector.
			 * @see length()
			 * @since snapshot20170930
			 */
			T magnitude() const;

			/**
			 * Returns the length of this vector.
			 * @return The magnitude/length of this vector.
			 * @see magnitude()
			 * @since snapshot20170930
			 */
			T length() const;

			/**
			 * Return true if any coordinate of this vector is null.
			 * @return <code>true</code> if any coordinate is NAN. <code>false</code> otherwhise.
			 * @since snapshot20170930
			 */
			bool isNull() const;

			/**
			 * Normalizes this vector. (It retains the angle of the
			 * vector but reduces it's length to 1)
			 * @see normalized()
			 * @since snapshot20170930
			 */
			void normalize();

			/**
			 * Returns a new normalized vector from this one. (It
			 * retains the angle of this vector but the length
			 * of the returned vector is 1)
			 * @return Normalized vector with the angle of this one.
			 * @see normalize()
			 * @since snapshot20170930
			 */
			vec3<T> normalized() const;

			/**
			 * Returns the value of the dot product between this
			 * vector and the given one.
			 * @param other The vector to dot product with this one.
			 * @return The dot product of the two vectors.
			 * @since snapshot20170930
			 */
			T dot(const vec3<T>& ) const;

			/**
			 * Returns the distance from this vector to a point, whose
			 * coordinates are on the given vector.
			 * @param other The vector representing the point's coordinates.
			 * @return Distance between this vector and the point.
			 * @see distanceToLine()
			 * @since snapshot20170930
			 */
			T distanceToPoint(const vec3<T>& ) const;

			/**
			 * Returns the smallest distance from this vector to a line,
			 * which is defined by a point and angle, provided by the
			 * two given vectors.
			 * @param point A vector representing the point's coordinates.
			 * @param direction A vector representing the direction of the line.
			 * @return The smallest distance between this vector and the line.
			 * @see distanceToPoint()
			 * @since snapshot20170930
			 */
			T distanceToLine(const vec3<T>&, const vec3<T>& ) const;

			/**
			 * Returns the vector as a string.
			 * @since snapshot20170930
			 */
			std::string toString() const;

			/**
			 * Returns the vector as a stream.
			 * @since snapshot20170930
			 */
			template<typename t>
			friend std::ostream& operator<<(std::ostream& , const vec3<T>& );

			/**
			 * The vector's x coordinate.
			 * @see y
			 * @see z
			 * @since snapshot20170930
			 */
			T x;

			/**
			 * The vector's y coordinate.
			 * @see x
			 * @see z
			 * @since snapshot20170930
			 */
			T y;

			/**
			 * The vector's z coordinate.
			 * @see x
			 * @see y
			 * @since snapshot20170930
			 */
			T z;
		};

		typedef vec3<float> Vector3D;

		// Inline definitions
		template<typename T>
		inline T vec3<T>::magnitude() const
		{
			return length();
		}

		template<typename T>
		inline bool vec3<T>::isNull() const
		{
			return std::isnan(x) || std::isnan(y) || std::isnan(z);
		}

		template<typename T>
		inline void vec3<T>::setX(const T& val)
		{
			x = val;
		}

		template<typename T>
		inline void vec3<T>::setY(const T& val)
		{
			y = val;
		}

		template<typename T>
		inline void vec3<T>::setZ(const T& val)
		{
			z = val;
		}

		template<typename T>
		inline T vec3<T>::getX() const
		{
			return x;
		}

		template<typename T>
		inline T vec3<T>::getY() const
		{
			return y;
		}

		template<typename T>
		inline T vec3<T>::getZ() const
		{
			return z;
		}

		// Inline Operators
		template<typename T>
		inline vec3<T> vec3<T>::operator+(const vec3<T>& obj)
		{
			return add(obj);
		}

		template<typename T>
		inline vec3<T> vec3<T>::operator-(const vec3<T>& obj)
		{
			return subtract(obj);
		}

		template<typename T>
		inline vec3<T> vec3<T>::operator*(const vec3<T>& obj)
		{
			return multiply(obj);
		}

		template<typename T>
		inline vec3<T> vec3<T>::operator/(const vec3<T>& obj)
		{
			return divide(obj);
		}

		template<typename T>
		inline vec3<T>& vec3<T>::operator+=(const vec3<T>& obj)
		{
			return add(obj);
		}

		template<typename T>
		inline vec3<T>& vec3<T>::operator-=(const vec3<T>& obj)
		{
			return subtract(obj);
		}

		template<typename T>
		inline vec3<T>& vec3<T>::operator*=(const vec3<T>& obj)
		{
			return multiply(obj);
		}

		template<typename T>
		inline vec3<T>& vec3<T>::operator/=(const vec3<T>& obj)
		{
			return divide(obj);
		}

		template<typename T>
		inline vec3<T>& vec3<T>::operator+=(const T& obj)
		{
			return add(obj);
		}

		template<typename T>
		inline vec3<T>& vec3<T>::operator-=(const T& val)
		{
			return subtract(val);
		}

		template<typename T>
		inline vec3<T>& vec3<T>::operator*=(const T& val)
		{
			return multiply(val);
		}

		template<typename T>
		inline vec3<T>& vec3<T>::operator/=(const T& val)
		{
			return divide(val);
		}

		// Template implementation
		// Constructors
		template<typename T>
		vec3<T>::vec3()
		: x(0), y(0), z(0)
		{}

		template<typename T>
		vec3<T>::vec3(const T& scalar)
			: x(scalar), y(scalar), z(scalar)
		{}

		template<typename T>
		vec3<T>::vec3(const T& x, const T& y)
			: x(x), y(y), z(0.0f)
		{}

		template<typename T>
		vec3<T>::vec3(const T& x, const T& y, const T& z)
			: x(x), y(y), z(z)
		{}

		template<typename T>
		vec3<T>::vec3(const vec2<T>& v)
			: x(v.x), y(v.y), z(0)
		{}

		template<typename T>
		vec3<T>::vec3(const vec3<T>& v)
			: x(v.x), y(v.y), z(v.z)
		{}

		template<typename T>
		vec3<T>::vec3(const vec4<T>& v)
			: x(v.x), y(v.y), z(v.z)
		{}

		// Operations
		// Using an existing vec3<T>
		template<typename T>
		vec3<T>& vec3<T>::add(const vec3<T>& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;

			return *this;
		}

		template<typename T>
		vec3<T>& vec3<T>::subtract(const vec3<T>& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;

			return *this;
		}

		template<typename T>
		vec3<T>& vec3<T>::multiply(const vec3<T>& v)
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;

			return *this;
		}

		template<typename T>
		vec3<T> vec3<T>::multiply(const mat4<T>& mat) const
		{
			return vec3(
				mat.r[0].x * x + mat.r[0].y * y + mat.r[0].z * z + mat.r[0].w,
				mat.r[1].x * x + mat.r[1].y * y + mat.r[1].z * z + mat.r[1].w,
				mat.r[2].x * x + mat.r[2].y * y + mat.r[2].z * z + mat.r[2].w
				);
		}

		template<typename T>
		vec3<T>& vec3<T>::divide(const vec3<T>& v)
		{
			x /= v.x;
			y /= v.y;
			z /= v.z;

			return *this;
		}

		// Using a value (scalar)
		template<typename T>
		vec3<T>& vec3<T>::add(const T& val)
		{
			x += val;
			y += val;
			z += val;

			return *this;
		}

		template<typename T>
		vec3<T>& vec3<T>::subtract(const T& val)
		{
			x -= val;
			y -= val;
			z -= val;

			return *this;
		}

		template<typename T>
		vec3<T>& vec3<T>::multiply(const T& val)
		{
			x *= val;
			y *= val;
			z *= val;

			return *this;
		}

		template<typename T>
		vec3<T>& vec3<T>::divide(const T& val)
		{
			x /= val;
			y /= val;
			z /= val;

			return *this;
		}

		// Using an x, y and z value
		template<typename T>
		vec3<T>& vec3<T>::add(const T& valX, const T& valY, const T& valZ)
		{
			x += valX;
			y += valY;
			z += valZ;

			return *this;
		}

		template<typename T>
		vec3<T>& vec3<T>::subtract(const T& valX, const T& valY, const T& valZ)
		{
			x -= valX;
			y -= valY;
			z -= valZ;

			return *this;
		}

		template<typename T>
		vec3<T>& vec3<T>::multiply(const T& valX, const T& valY, const T& valZ)
		{
			x *= valX;
			y *= valY;
			z *= valZ;

			return *this;
		}

		template<typename T>
		vec3<T>& vec3<T>::divide(const T& valX, const T& valY, const T& valZ)
		{
			x /= valX;
			y /= valY;
			z /= valZ;

			return *this;
		}

		//Operators
		template<typename T>
		vec3<T> vec3<T>::operator+(const T& value)
		{
			return vec3<T>(x + value, y + value, z + value);
		}

		template<typename T>
		vec3<T> vec3<T>::operator-(const T& value)
		{
			return vec3<T>(x - value, y - value, z - value);
		}

		template<typename T>
		vec3<T> vec3<T>::operator*(const T& value)
		{
			return vec3<T>(x * value, y * value, z * value);
		}

		template<typename T>
		vec3<T> vec3<T>::operator/(const T& value)
		{
			return vec3<T>(x / value, y / value, z / value);
		}

		template<typename T>
		bool vec3<T>::operator==(const vec3<T>& other) const
		{
			return x == other.x && y == other.y && z == other.z;
		}

		template<typename T>
		bool vec3<T>::operator!=(const vec3<T>& other) const
		{
			return !(*this == other);
		}

		template<typename T>
		bool vec3<T>::operator<(const vec3<T>& other) const
		{
			return x < other.x && y < other.y && z < other.z;
		}

		template<typename T>
		bool vec3<T>::operator<=(const vec3<T>& other) const
		{
			return x <= other.x && y <= other.y && z <= other.z;
		}

		template<typename T>
		bool vec3<T>::operator>(const vec3<T>& other) const
		{
			return x > other.x && y > other.y && z > other.z;
		}

		template<typename T>
		bool vec3<T>::operator>=(const vec3<T>& other) const
		{
			return x >= other.x && y >= other.y && z >= other.z;
		}

		// Vector operations
		template<typename T>
		T vec3<T>::length() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		template<typename T>
		void vec3<T>::normalize()
		{
			T length = magnitude();
			this->x /= length;
			this->y /= length;
			this->z /= length;
		}

		template<typename T>
		vec3<T> vec3<T>::normalized() const
		{
			T length = magnitude();
			return vec3<T>(x / length, y / length, z / length);
		}

		template<typename T>
		T vec3<T>::dot(const vec3<T>& other) const
		{
			return x * other.x + y * other.y + z * other.z;
		}

		template<typename T>
		T vec3<T>::distanceToPoint(const vec3<T>& other) const
		{
			T a = x - other.x;
			T b = y - other.y;
			T c = z - other.z;
			return sqrt(a * a + b * b + c * c);
		}

		template<typename T>
		T vec3<T>::distanceToLine(const vec3<T>& point, const vec3<T>& direction) const
		{
			// TODO: Find the formula to get the distance
		}

		template<typename T>
		std::string vec3<T>::toString() const
		{
			return "vec3: (" + std::to_string(x) + ", " + std::to_string(y) + ")";
		}

		template <typename T>
		std::ostream& operator<<(std::ostream& stream, const vec3<T>& vector)
		{
			stream << vector.toString();
			return stream;
		}
	}
}

#include <AuroraFW/Math/Matrix.h>

#endif // AURORAFW_MATH_VECTOR3D_H
