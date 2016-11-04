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
	vec4 points[4] = {
		{-0.5f, -0.5f, 0.f, 0.f},
		{-0.5f,  0.5f, 0.f, 1.f},
		{0.5f,  0.5f, 1.f, 1.f},
		{0.5f, -0.5f, 1.f, 0.f},
	};

	glLineWidth(2.f);

	shader.use();

	glBindVertexArray(gl_array_object);
	glBindBuffer(GL_ARRAY_BUFFER, gl_buffer_object);

	mat4 s, t, m;

	Transform Left_Wheel_Transform = Transform{
		vec2{192.f, 192.f},
		vec2{96.f, 192.f},
		0.f
	};

	Transform Right_Wheel_Transform = Transform{
		vec2{576.f, 192.f},
		vec2{96.f, 192.f},
		0.f
	};

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), &points);
	s = scale({transform.size, 0.f});
	t = transpose(translate({transform.position, 0.f}));
	m = mult(s, t);
	shader.set_uniform("model", m);
	shader.set_uniform("uniform_colour", vec3{0.77f, 0.77f, 0.77f});
	shader.set_uniform("is_wheel", false);
	shader.set_uniform("time", utils::elapsed_time());
	glDrawArrays(GL_LINE_LOOP, 0, 4);

	// swap last 2 vertices for wheels
	vec4 tmp = points[2];
	points[2] = points[3];
	points[3] = tmp;
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), &points);

	s = scale(vec3{Left_Wheel_Transform.size, 0.f});
	t = transpose(translate(vec3{Left_Wheel_Transform.position, 0.f}));
	m = mult(s, t);
	shader.set_uniform("model", m);
	shader.set_uniform("uniform_colour", vec3{0.57f, 0.57f, 0.57f});
	shader.set_uniform("is_wheel", true);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	s = scale(vec3{Right_Wheel_Transform.size, 0.f});
	t = transpose(translate(vec3{Right_Wheel_Transform.position, 0.f}));
	m = mult(s, t);
	shader.set_uniform("model", m);
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
