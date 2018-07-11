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
** the GNU General Public License version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3 requirements will be
** met: https://www.gnu.org/licenses/gpl-3.0.html.
****************************************************************************/

#include <AuroraFW/Core.h>
#include <AuroraFW/Math.h>
#include <AuroraFW/CLI.h>

using namespace AuroraFW;

Application* App;

template<typename T>
void printCoord(AuroraFW::Math::vec2<T> vec)
{
	CLI::Log(CLI::Information, "It's coordinates are ", vec.toString());
}

template<typename T>
void printCoord(AuroraFW::Math::vec3<T> vec)
{
	CLI::Log(CLI::Information, "It's coordinates are ", vec.toString());
}

template<typename T>
void printCoord(AuroraFW::Math::vec4<T> vec)
{
	CLI::Log(CLI::Information, "It's coordinates are ", vec.toString());
}

template<typename T, uint m, uint n>
void printMatrix(AuroraFW::Math::mat<T, m, n> mat)
{
	for(int i = 0; i< 4; i++)
	{
		for(int j = 0; j< 4; j++)
		{
			CLI::Output << mat.matrix[i][j] << " ";
		}
	}
}

void slot_App_on_open(Application* )
{
	CLI::Log(CLI::Information, "Creating new Vector2D vec2A.");
	Math::Vector2D vec2A (1.0f, 3.0f);
	printCoord(vec2A);

	CLI::Log(CLI::Information, "Adding 3 to the vector.");
	vec2A.add(3.0f);
	printCoord(vec2A);

	CLI::Log(CLI::Information, "Substracting 1x and 2y to the vector.");
	vec2A.subtract(1.0f, 2.0f);
	printCoord(vec2A);

	CLI::Log(CLI::Information, "Normalizing vec2A");
	vec2A.normalize();
	printCoord(vec2A);

	CLI::Log(CLI::Information, "Normalizing the vector into a vec2B.");
	Math::Vector2D vec2B = vec2A.normalized();
	printCoord(vec2B);

	CLI::Log(CLI::Information, "It's magnitude is ", vec2B.magnitude());
	CLI::Log(CLI::Information, "The cross product of vec2A and vec2B is ", vec2A.dot(vec2B));

	CLI::Log(CLI::Information, "Creating a third vec2C.");
	Math::Vector2D vec2C (3.0f, -5.0f);
	printCoord(vec2C);

	CLI::Log(CLI::Information, "vec2A += vec2C");
	vec2A += vec2C;
	printCoord(vec2A);

	CLI::Log(CLI::Information, "Distance between vec2B and vec2C: ", vec2B.distanceToPoint(vec2C));

	CLI::Log(CLI::Information, "Creating new Vector3D vec3A.");
	Math::Vector3D vec3A (1.0f, 3.0f, 2.0f);
	printCoord(vec3A);

	CLI::Log(CLI::Information, "Adding 3 to the vector.");
	vec3A.add(3.0f);
	printCoord(vec3A);

	CLI::Log(CLI::Information, "Substracting 1x, 2y and 0z to the vector.");
	vec3A.subtract(1.0f, 2.0f, 0.0f);
	printCoord(vec3A);

	CLI::Log(CLI::Information, "Normalizing vec3A");
	vec3A.normalize();
	printCoord(vec3A);

	CLI::Log(CLI::Information, "Normalizing the vector into a vec3B.");
	Math::Vector3D vec3B = vec3A.normalized();
	printCoord(vec3B);

	CLI::Log(CLI::Information, "It's magnitude is ", vec3B.magnitude());
	CLI::Log(CLI::Information, "The cross product of vec3A and vec3B is ", vec3A.dot(vec3B));

	CLI::Log(CLI::Information, "Creating a third vec3C.");
	Math::Vector3D vec3C (3.0f, -5.0f, -2.0f);
	printCoord(vec3C);

	CLI::Log(CLI::Information, "vec3A += vec3C");
	vec3A += vec3C;
	printCoord(vec3A);

	CLI::Log(CLI::Information, "Distance between vec3B and vec3C: ", vec3B.distanceToPoint(vec3C));

	CLI::Log(CLI::Information, "Creating new Vector4D vec4A.");
	Math::Vector4D vec4A (1, 3, 2, 1);
	printCoord(vec4A);

	CLI::Log(CLI::Information, "Adding 3 to the vector.");
	vec4A.add(3);
	printCoord(vec4A);

	CLI::Log(CLI::Information, "Substracting 1x, 2y, 0z and 4w to the vector.");
	vec4A.subtract(1, 2, 0, 4);
	printCoord(vec4A);

	CLI::Log(CLI::Information, "Normalizing vec4A");
	vec4A.normalize();
	printCoord(vec4A);

	CLI::Log(CLI::Information, "Normalizing the vector into a vec4B.");
	Math::Vector4D vec4B = vec4A.normalized();
	printCoord(vec4B);

	CLI::Log(CLI::Information, "It's magnitude is ", vec4B.magnitude());
	CLI::Log(CLI::Information, "The cross product of vec4A and vec4B is ", vec4A.dot(vec4B));

	CLI::Log(CLI::Information, "Creating a third vec4C.");
	Math::Vector4D vec4C (3.0f, -5.0f, -2.0f, 1.0f);
	printCoord(vec4C);

	CLI::Log(CLI::Information, "vec4A += vec4C");
	vec4A += vec4C;
	printCoord(vec4A);

	CLI::Log(CLI::Information, "Distance between vec4B and vec4C: ", vec4B.distanceToPoint(vec4C));

	CLI::Log(CLI::Information, "Creating new matrix");
	AuroraFW::Math::Matrix4x4 mat;
	CLI::Log(CLI::Information, "Printing matrix values: ");
	printMatrix(mat);
	CLI::Output << CLI::EndLine;
	CLI::Log(CLI::Notice, "Output should be 0");

	CLI::Log(CLI::Information, "sizeof Matrix4x4: ", sizeof(mat));
	CLI::Log(CLI::Notice, "This should be 64");

	AuroraFW::Math::Vector4D matvec4(3.0f, -5.0f, 1.0f, 2.0f);
	AuroraFW::Math::Matrix4x4 matr;
	CLI::Log(CLI::Information, "sizeof Matrix4x4: ", sizeof(matr));
	CLI::Log(CLI::Notice, "This should be 64");

	CLI::Log(CLI::Notice, "The absolute value of -42 is ", Math::abs(-42));
}

int main(int argc, char* argv[])
{
	App = new Application(argc, argv, slot_App_on_open);
	delete App;

	return EXIT_SUCCESS;
}
