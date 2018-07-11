#version 330 core

precision highp float;
layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

uniform mat4 prMatrix;
uniform mat4 vwMatrix = mat4(1.0);
uniform mat4 mlMatrix = mat4(1.0);

out DATA
{
	vec4 sunCoord;
	vec4 color;
} vs_out;

void main()
{
	gl_Position = prMatrix * vwMatrix * mlMatrix * position;
	vs_out.sunCoord = mlMatrix * position;
	vs_out.color = color;
}