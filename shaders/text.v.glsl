#version 450

layout(location = 0) in vec4 position;

out vec2 tex_coord;

uniform mat4 projection;

void main() {
	//gl_Position = vec4(1.0);
	gl_Position = projection * vec4(position.xy, 0.0, 1.0);
	tex_coord = vec2(position.zw);
};