#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "engine/Window.h"
#include "engine/Events.h"
#include "graphics/Shader.h"

float_t vertices[] = {
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f
};


int main(int argc, char** argv) {
	beta::engine::Window window;
	beta::engine::Events events(window);

	beta::graphics::Shader* shader = beta::graphics::Shader::load("resource/shader/main.glslv", "resource/shader/main.glslf");
	if (shader == nullptr) {
		std::cerr << "Failed to load shaders. Shutting down." << std::endl;
		return 1;
	}


	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	glClearColor(0.39f, 0.58f, 0.93f, 0.0f);

	while (!window.shouldClose()) {
		events.pollEvents();

		if (events.isKeyJustPressed(GLFW_KEY_ESCAPE)) {
			window.close();
		}

		glClear(GL_COLOR_BUFFER_BIT);
		shader->use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		window.swapBuffers();
	}

	delete shader;


	return 0;
}
