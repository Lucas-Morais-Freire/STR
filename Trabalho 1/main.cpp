#include <iostream>
#include <random>
#include <sys/time.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <engine.hpp>
#include <shader.hpp>
#include <circle.hpp>

int generate_random_num(int lower, int upper);

int main() {
	engine eng(1280, 720);
	glfwSetWindowPos(eng(),300,100);
	glfwSwapInterval(1);
	std::cout << glGetString(GL_VERSION) << '\n';

	shaderProg mainShader{
		{"shaders/circle.vert", GL_VERTEX_SHADER},
		{"shaders/circle.frag", GL_FRAGMENT_SHADER}
	};
	mainShader.use();

	glm::mat4 projmat = glm::ortho(-640.f, 640.f, -360.f, 360.f, 0.f, 1.0f);
	GLint projmat_loc = glGetUniformLocation(mainShader(), "projmat");
	glUniformMatrix4fv(projmat_loc, 1, GL_FALSE, glm::value_ptr(projmat));

	const GLfloat colors[4][3] = {
		{1.f, 0.f, 0.f},
		{0.f, 1.f, 0.f},
		{0.f, 0.f, 1.f},
		{1.f, 1.f, 0.f},
	};

	GLfloat center[2] = {
		generate_random_num(-640, 640),
		generate_random_num(-320, 320)
	};
	unsigned char color_index = generate_random_num(0, 3);
	circle* circ = new circle(center, 50.f, colors[color_index]);

	timeval start, finish;
	gettimeofday(&start, nullptr);
	auto render = [&]() {
		glClear(GL_COLOR_BUFFER_BIT);

		gettimeofday(&finish, nullptr);

		if ((finish.tv_sec - start.tv_sec)*1000.f + (finish.tv_usec - start.tv_usec)/1000.f >= 2000.f) {
			center[0] = generate_random_num(-640, 640); center[1] = generate_random_num(-320, 320);
			unsigned char color_index = generate_random_num(0, 3);
			delete circ;
			circ = new circle(center, 50.f, colors[color_index]);

			start.tv_sec = finish.tv_sec;
			start.tv_usec = finish.tv_usec;
		}

		circ->draw(mainShader);
	};

	auto keyHold = [&](const std::list<int>& pressedKeys) {

	};

	auto keyPress = [&](int key) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			eng.setWindowShouldClose(true);
			break;
		}
	};

	auto mousePos = [&](double xpos, double ypos) {

	};

	eng.setRenderFunc(render);
	eng.setKeyHoldFunc(keyHold);
	eng.setKeyPressFunc(keyPress);
	eng.setMousePosFunc(mousePos);

	eng.mainLoop();

	delete circ;
	return 0;
}

int generate_random_num(int lower, int upper) {
	static std::mt19937 gen(time(nullptr));
	return gen() % (upper - lower + 1) + lower;
}