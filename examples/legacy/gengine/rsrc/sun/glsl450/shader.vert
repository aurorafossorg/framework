#version 450

precision highp float;
layout (location = 0) in vec4 position;

uniform blobSettings {
	mat4 prMatrix;
	mat4 vwMatrix;
	mat4 mlMatrix;
};

layout (location = 0) out vec4 sunCoord;

void main()
{
	gl_Position = prMatrix * vwMatrix * mlMatrix * position;
	sunCoord = mlMatrix * position;
}