#include "draw_vehicle.h"

void DrawVehicle::init() {
	shader = {
		"shaders/draw_vehicle.v.glsl",
		"shaders/draw_vehicle.f.glsl"
	};

	shader.set_uniform("projection", orthographic_matrix({768.f, 768.f}, -1.f, 1.f, mat4()));

	vec4 points[4] = {
		{-0.5f, -0.5f, 0.f, 0.f},
		{-0.5f,  0.5f, 0.f, 1.f},
		{0.5f,  0.5f, 1.f, 1.f},
		{0.5f, -0.5f, 1.f, 0.f},

	};

	set_gl_buffer_data(sizeof(points), &points);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vec4), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vec4), (GLvoid*)(sizeof(float) * 2));
}

void DrawVehicle::update(const vec2 & cursor_pos) {
}

void DrawVehicle::draw() {
	static vec4 body_points[4] = {
		{-0.5f, -0.5f, 0.f, 0.f},
		{-0.5f,  0.5f, 0.f, 1.f},
		{ 0.5f,  0.5f, 1.f, 1.f},
		{ 0.5f, -0.5f, 1.f, 0.f},
	};

	static vec4 wheel_points[4] = {
		{-0.5f, -0.5f, 0.f, 0.f},
		{-0.5f,  0.5f, 0.f, 1.f},
		{ 0.5f, -0.5f, 1.f, 0.f},
		{ 0.5f,  0.5f, 1.f, 1.f}
	};

	glLineWidth(2.f);

	shader.use();
	shader.set_uniform("time", utils::elapsed_time());

	glBindVertexArray(gl_array_object);
	glBindBuffer(GL_ARRAY_BUFFER, gl_buffer_object);
	
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(body_points), &body_points);

	shader.set_uniform("model", gen_model_matrix(size, position));
	shader.set_uniform("uniform_colour", vec3{0.77f, 0.77f, 0.77f});
	shader.set_uniform("is_wheel", false);
	glDrawArrays(GL_LINE_LOOP, 0, 4);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(wheel_points), &wheel_points);

	shader.set_uniform("model", gen_model_matrix({96.f, 192.f}, {192.f, 192.f}));
	shader.set_uniform("uniform_colour", vec3{0.57f, 0.57f, 0.57f});
	shader.set_uniform("is_wheel", true);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	shader.set_uniform("model", gen_model_matrix({96.f, 192.f}, {576.f, 192.f}));
	shader.set_uniform("uniform_colour", vec3{0.57f, 0.57f, 0.57f});
	shader.set_uniform("is_wheel", true);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(0);
	shader.release();

	glLineWidth(1.f);
}

void DrawVehicle::destroy() {
	glDeleteBuffers(1, &gl_buffer_object);
	glDeleteVertexArrays(1, &gl_array_object);
	shader.destroy();
}
