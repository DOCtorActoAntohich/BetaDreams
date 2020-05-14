// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "App.h"

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "exception/Exceptions.hpp"

#include "engine/Window.h"
#include "engine/Events.h"

#include "graphics/ShaderProgram.h"
#include "graphics/Texture.h"

#include "utility/Color.h"

using namespace beta;

App::App()
{	}



void App::run() {
	

	engine::Window window;
	engine::Events events(window);

	graphics::ShaderProgram mainShader("main");
	graphics::ShaderProgram negativeShader("negative");
	graphics::Texture texture("resource/texture/test.png");

	mainShader.use();
	texture.bind();
	
	GLuint VAO, VBO;
	{
		float_t vertices[] = {
			// x    y     z     u     v
		   -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		   -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,

			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		   -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat))); //-V2005
		glEnableVertexAttribArray(0);
		// https://learnopengl.com/Getting-started/Textures
		glVertexAttribPointer(
			1,									// Index of attribute list in VAO.
			2,									// Amount of consecutive data fields (i.e. how many numbers describe part of something).
			GL_FLOAT,							// Type of data, for width in bytes.
			GL_FALSE,							// Should be normalized.
			5 * sizeof(GLfloat),				// How many bytes are there between data members describing part of something.
			(GLvoid*)(3 * sizeof(GLfloat)));	// The offset from the beginning of one VBO entry.
		glEnableVertexAttribArray(1);
	
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	while (!window.shouldClose()) {
		events.pollEvents();

		if (events.isKeyJustPressed(GLFW_KEY_ESCAPE)) {
			window.close();
		}
		if (events.isKeyJustPressed(GLFW_MOUSE_BUTTON_1)) {
			mainShader.use();
		}
		else if (events.isKeyJustPressed(GLFW_MOUSE_BUTTON_2)) {
			negativeShader.use();
		}

		window.clear();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		window.swapBuffers();
	}

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}