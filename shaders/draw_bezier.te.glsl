#version 450 core

layout(isolines, equal_spacing, ccw) in;

uniform mat4 projection;

vec3 bezier(float u, vec3 p0, vec3 p1, vec3 p2, vec3 p3) {
	float B0 = (1. - u) * (1. - u) * (1. - u);
	float B1 = 3. * u * (1. - u) * (1. - u);
	float B2 = 3. * u * u * (1. - u);
	float B3 = u * u * u;

	vec3 p = B0*p0 + B1*p1 + B2*p2 + B3*p3;
	return p;
}

void main() {
	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;

	vec3 p0 = vec3(gl_in[0].gl_Position);
	vec3 p1 = vec3(gl_in[1].gl_Position);
	vec3 p2 = vec3(gl_in[2].gl_Position);
	vec3 p3 = vec3(gl_in[3].gl_Position);

	vec4 pos = vec4(bezier(u, p0, p1, p2, p3), 1.);
	gl_Position = pos;
}