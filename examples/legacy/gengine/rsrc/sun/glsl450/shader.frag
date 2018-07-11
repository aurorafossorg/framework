#version 450

precision highp float;

layout (location = 0) out vec4 fragColor;
layout (location = 0) in vec3 sunCoord;

uniform blobSettings {
	vec4 color;
	vec2 lightPos;
	float size;
};

void main()
{
	float intensity = size / length(sunCoord.xy - lightPos);
	fragColor = color * intensity;
}