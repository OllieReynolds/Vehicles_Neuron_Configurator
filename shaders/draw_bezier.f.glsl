#version 450

out vec4 colour;

uniform vec3 uniform_colour;

void main() {
	colour = vec4(uniform_colour, 1.0);
}