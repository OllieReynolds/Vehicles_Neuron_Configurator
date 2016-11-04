#include "draw_bezier.h"


void DrawBezier::init() {
	shader = {
		"shaders/draw_bezier.v.glsl",
		"shaders/draw_bezier.tc.glsl",
		"shaders/draw_bezier.te.glsl",
		"shaders/draw_bezier.f.glsl"
	};

	shader.set_uniform("projection", orthographic_matrix({768.f, 768.f}, -1.f, 1.f, mat4()));

	vec2 points[4] = {
		{-0.2f,  0.75f},
		{-0.1f,  0.0f},
		{-0.1f, -0.7f},
		{-0.5f, -0.5f}
	};
	
	set_gl_buffer_data(sizeof(points), &points);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

}

void DrawBezier::update(const vec2 & cursor_pos) {
	switch (wire_config) {
	case 0:
		lwheel = left_weight;
		rwheel = right_weight;
		break;

	case 1:
		lwheel = right_weight;
		rwheel = left_weight;
		break;

	case 2:
		lwheel = left_weight + right_weight;
		rwheel = 0.f;
		break;

	case 3:
		lwheel = 0.f;
		rwheel = left_weight + right_weight;
		break;
	}
}

void DrawBezier::draw() {	
	static vec2 bezier_points[4][2][4] = {
		{ // Layout 0
			{
				{-0.2f,  0.75f},
				{-0.1f,  0.0f},
				{-0.1f, -0.7f},
				{-0.5f, -0.5f}
			},

			{
				{0.2f,  0.75f},
				{0.1f,  0.0f},
				{0.1f, -0.7f},
				{0.5f, -0.5f}
			}
		},

		{ // Layout 1
			{
				{-0.2f,  0.75f},
				{-0.1f,  0.0f},
				{-0.1f, -0.7f},
				{0.5f, -0.5f}
			},

			{
				{0.2f,  0.75f},
				{0.1f,  0.0f},
				{0.1f, -0.7f},
				{-0.5f, -0.5f}
			}
		},

		{ // Layout 2
			{
				{-0.2f,  0.75f},
				{-0.1f,  0.0f},
				{-0.1f, -0.7f},
				{-0.5f, -0.5f}
			},

			{
				{0.2f,  0.75f},
				{0.1f,  0.0f},
				{0.1f, -0.7f},
				{-0.5f, -0.5f}
			}
		},

		{ // Layout 3
			{
				{-0.2f,  0.75f},
				{-0.1f,  0.0f},
				{-0.1f, -0.7f},
				{0.5f, -0.5f}
			},

			{
				{0.2f,  0.75f},
				{0.1f,  0.0f},
				{0.1f, -0.7f},
				{0.5f, -0.5f}
			}
		}
	};

	glLineWidth(8.f);

	shader.use();
	shader.set_uniform("projection", orthographic_matrix({768.f, 768.f}, -1.f, 1.f, mat4()));
	shader.set_uniform("uniform_colour", vec3{1.f, 0.f, 0.f});

	glBindVertexArray(gl_array_object);
	glBindBuffer(GL_ARRAY_BUFFER, gl_buffer_object);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bezier_points[wire_config][0]), &bezier_points[wire_config][0]);
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	glDrawArrays(GL_PATCHES, 0, 4);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bezier_points[wire_config][1]), &bezier_points[wire_config][1]);
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	glDrawArrays(GL_PATCHES, 0, 4);

	glBindVertexArray(0);
	shader.release();

	glLineWidth(1.f);
}

void DrawBezier::destroy() {
	glDeleteBuffers(1, &gl_buffer_object);
	glDeleteVertexArrays(1, &gl_array_object);

	shader.destroy();
}