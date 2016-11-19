#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "freetype265MT.lib")

#include <iostream>
#include <sstream>

#include <glew.h>
#include <glfw3.h>

#include "draw_bezier.h"
#include "draw_vehicle.h"
#include "texture.h"
#include "ui.h"

namespace {
	struct Instance {
		DrawBezier db;
		DrawVehicle dv;
		Texture tex;
		UI ui;

		GLuint frame_buffer;

		void init() {
			db.init();
			dv.init();
			ui.init();

			tex.init();
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 768, 768, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
			glGenFramebuffers(1, &frame_buffer);
			glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex.gl_tex, 0);
		}

		void update() {
			db.update(0.f);
			dv.update(0.f);

			std::vector<String_Instance> ui_elements;
			switch (db.wire_config) {
			case 0: ui_elements.push_back(String_Instance{"LL         RR",{384.f, 700.f}}); break;
			case 1: ui_elements.push_back(String_Instance{"LR         RL",{384.f, 700.f}}); break;
			case 2: ui_elements.push_back(String_Instance{"LL         RL",{384.f, 700.f}}); break;
			case 3: ui_elements.push_back(String_Instance{"LR         RR",{384.f, 700.f}});	break;
			}

			ui_elements.push_back(String_Instance{" Left weight: " + utils::friendly_float(db.left_weight) + "        Left wheel: " + utils::friendly_float(db.lwheel),{384.f, 30.f}});
			ui_elements.push_back(String_Instance{"Right weight: " + utils::friendly_float(db.right_weight) + "       Right wheel: " + utils::friendly_float(db.rwheel),{384.f, 6.f}});
			
			ui.update(ui_elements);
		}

		void draw() {
			glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer); glClearColor(0.f, 0.f, 0.f, 1.f); glClear(GL_COLOR_BUFFER_BIT);
			db.draw();
			dv.draw();
			ui.draw();
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			tex.draw();
		}

		void destroy() {
			db.destroy();
			dv.destroy();
			ui.destroy();
			tex.destroy();
		}
	};

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (action == GLFW_PRESS) {
			Instance* i = reinterpret_cast<Instance*>(glfwGetWindowUserPointer(window));

			switch (key) {
			case GLFW_KEY_LEFT:
				if (--i->db.wire_config < 0)
					i->db.wire_config = 3;
				break;

			case GLFW_KEY_RIGHT:
				i->db.wire_config = abs((i->db.wire_config + 1) % 4);
				break;
			}
		}
	}
}

int main() {
	// GLFW init
	if (!glfwInit()) {
		std::cout << "GLFW failed to initialise" << std::endl;
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(768, 768, "Vehicles", NULL, NULL);

	// GLFW window
	if (!window) {
		glfwTerminate();
		std::cout << "GFLW failed to create window" << std::endl;
		return 1;
	} 

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
		
	// GLEW init
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		std::cout << "Glew failed to initialise" << std::endl;
		return 1;
	}

	{ // Display config
		std::stringstream ss;
		ss << "Device Vendor: " << glGetString(GL_VENDOR) << std::endl;
		ss << "Device Renderer: " << glGetString(GL_RENDERER) << std::endl;
		ss << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
		ss << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
		std::cout << ss.str() << std::endl;
	}

	glEnable(GL_BLEND);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	

	Instance i = {
		DrawBezier(Transform{}, 0.f),
		DrawVehicle(Transform{384.f, {256.f, 512.f}, 0.f}, vec4{0.461757f, 0.554109f, 0.692636f, 1.f}),
		Texture(Transform{384.f, {192.f, 192.f}, 0.f}, 0.f),
		UI()
	};

	i.init();
	
	glfwSetWindowUserPointer(window, &i);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		i.update();
		i.draw();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	i.destroy();

	glfwTerminate();

	return 0;
}