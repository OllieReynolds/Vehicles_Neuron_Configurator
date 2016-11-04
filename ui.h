#pragma once

#include <vector>

#include "text.h"

struct String_Instance {
	std::string msg;
	vec2 position;
};

class UI {
public:
	UI()
	: text(24, "data/NotoMono-Regular.ttf", {1.f, 1.f, 1.f, 1.f}) 
	{
		
	}

	void init();
	void update(std::vector<String_Instance> ui_elements);
	void draw();
	void destroy();

private:
	Text text;
	std::vector<String_Instance> string_descriptors;
};