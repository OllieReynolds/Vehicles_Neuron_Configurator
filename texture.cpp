#include "texture.h"

void Texture::init() {
	shader = {
		"shaders/framebuffer.v.glsl",
		"shaders/framebuffer.f.glsl"
	};

	shader.set_uniform("projection", orthographic_matrix({768.f, 768.f}, -1.f, 1.f, mat4()));

	vec4 points[4] = {
		{-1.f, -1.f, 0.f, 0.f},
		{-1.f,  1.f, 0.f, 1.f},
		{ 1.f, -1.f, 1.f, 0.f},
		{ 1.f,  1.f, 1.f, 1.f}

	};

	set_gl_buffer_data(sizeof(points), &points);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vec4), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vec4), (GLvoid*)(sizeof(float) * 2));

	glGenTextures(1, &gl_tex);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gl_tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	/*float pixels[] = {
		0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
	};
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2,2, 0, GL_RGB, GL_FLOAT, pixels);*/


	/*
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gl_tex, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	*/
}

void Texture::update(const vec2& cursor_pos) {
}

void Texture::draw() {
	shader.use();

	glBindVertexArray(gl_array_object);
	glBindBuffer(GL_ARRAY_BUFFER, gl_buffer_object);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gl_tex);
	
	shader.set_uniform("model", gen_model_matrix());
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(0);

	shader.release();
}

void Texture::destroy() {
	glDeleteBuffers(1, &gl_buffer_object);
	glDeleteVertexArrays(1, &gl_array_object);
	shader.destroy();
	glDeleteTextures(1, &gl_tex);
	
	
	/*glDeleteFramebuffers(1, &framebuffer);*/
}
//
//void FrameBuffer::use() {
//	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//}
//
//void FrameBuffer::release() {
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}