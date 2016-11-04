#pragma once

#include "..\Vehicles\include\drawable.h"
#include "..\Vehicles\include\maths.h"
#include "..\Vehicles\include\utils.h"
using namespace simulation;

class DrawVehicle : public Drawable {
public:
	DrawVehicle()
		: Drawable(Transform(), 0.f) { }

	DrawVehicle(const Transform& transform, const vec4& colour = 0.f)
		: Drawable(transform, colour) { }

	void init();
	void update(const vec2& cursor_pos);
	void draw();
	void destroy();
};