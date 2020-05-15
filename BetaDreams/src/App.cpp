// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "App.h"

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "engine/Window.h"
#include "engine/Events.h"

#include "graphics/ShaderProgram.h"
#include "graphics/Texture.h"
#include "graphics/VAO.h"

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

	graphics::VAO textureData;
	textureData.attach(
		{ { -1.0f, -1.0f, 0.0f,
		     1.0f, -1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f,

			 1.0f, -1.0f, 0.0f,
			 1.0f,  1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f
		},
		3 }
	).attach(
		{ {	0.0f, 0.0f,
			1.0f, 0.0f,
			0.0f, 1.0f,

			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f
		},
		2 }
	);


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

		textureData.draw();

		window.swapBuffers();
	}
}