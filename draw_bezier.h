#pragma once

#include "..\Vehicles\include\drawable.h"
#include "..\Vehicles\include\maths.h"
#include "text.h"
#include "..\Vehicles\include\utils.h"

using namespace simulation;

class DrawBezier : public Drawable {
public:

	DrawBezier()
		: Drawable(Transform(), 0.f), wire_config(0), left_weight(.5f), right_weight(-.5f), lwheel(.5f), rwheel(-.5f)
	{
	}

	DrawBezier(const Transform& transform, const vec4& colour = 0.f)
		: Drawable(transform, colour), wire_config(0), left_weight(.5f), right_weight(-.5f), lwheel(.5f), rwheel(-.5f)
	{
	}

	void init();
	void update(const vec2& cursor_pos);
	void draw();
	void destroy();

	int wire_config;

	float left_weight;
	float right_weight;
	float lwheel;
	float rwheel;
};