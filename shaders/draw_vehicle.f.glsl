#version 450

in vec2 uv;
out vec4 colour;

uniform vec3 uniform_colour;
uniform float time;
uniform float speed_coefficient;
uniform bool is_wheel;

void main() {
	vec4 coord = gl_FragCoord;

	if (is_wheel) {
		if (mod(coord.y + (time * -64.), 32.) > 8.)
			colour = vec4(uniform_colour, 1.0);
		else
			colour = vec4(0.f, 0.f, 0.f, 1.f);
	}
	else {
		colour = vec4(uniform_colour, 1.0);
	}
}