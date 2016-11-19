#pragma once

#include "..\Vehicles\include\drawable.h"
#include "..\Vehicles\include\maths.h"
#include "..\Vehicles\include\utils.h"

using namespace simulation;

class Texture : public Drawable {
public:
	Texture()
		: Drawable({0.f, 0.f, 0.f}, 0.f) { }

	Texture(const Transform& transform, const vec4& colour = 0.f)
		: Drawable(transform, colour) { }

	void init();
	void update(const vec2& cursor_pos);
	void draw();
	void destroy();

	GLuint gl_tex;
};