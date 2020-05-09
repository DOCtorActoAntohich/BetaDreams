#version 410 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_textureCoordinate;

out vec4 a_color;
out vec2 a_textureCoordinate;

void main() {
	a_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	a_textureCoordinate = v_textureCoordinate;
	gl_Position = vec4(v_position, 1.0);
}