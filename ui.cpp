#include "ui.h"

void UI::init() {
	text.init_text();
}

void UI::update(std::vector<String_Instance> ui_elements) {
	string_descriptors = ui_elements;
}

void UI::draw() {
	for (String_Instance i : string_descriptors)
		text.draw_text(i.msg, i.position);
}

void UI::destroy() {
	text.destroy_text();
}