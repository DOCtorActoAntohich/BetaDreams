#version 410 core

layout (location = 0) in vec3 objectPosition;
layout (location = 1) in vec2 in_textureCoordinate;

out vec4 rgbMultipliers;
out vec2 textureCoordinate;

uniform mat4 projView;
uniform mat4 model;

void main() {
	rgbMultipliers = vec4(1, 1, 1, 1);
	textureCoordinate = in_textureCoordinate;
	gl_Position = projView * model * vec4(objectPosition, 1.0);
}