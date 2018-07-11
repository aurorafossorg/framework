#version 330 core

precision highp float;

layout (location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 lightPos;
uniform float size = 1.0;

in DATA
{
	vec4 sunCoord;
	vec4 color;
} fs_in;

void main()
{
	float intensity = size / length(fs_in.sunCoord.xy - lightPos);
	//color = colour * intensity;
	color = fs_in.color * intensity;
}