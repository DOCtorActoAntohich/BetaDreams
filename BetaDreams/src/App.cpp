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
#include "graphics/Camera.h"

using namespace beta;

App::App()
{	}



void App::run() {
	engine::Window window;
	engine::Events events(window);
	graphics::Camera camera(window, glm::vec3(0, 0, 1), glm::radians(70.f));

	graphics::ShaderProgram mainShader("main");
	graphics::ShaderProgram negativeShader("negative");
	graphics::Texture texture("resource/texture/test.png");

	mainShader.use();
	texture.bind();

	glm::mat4 model(1.0f);

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


	float_t speed = 2;

	double_t lastTime = glfwGetTime();
	double_t dTime = 0.0f;

	while (!window.shouldClose()) {
		double_t currentTime = glfwGetTime();
		dTime = currentTime - lastTime;
		lastTime = currentTime;


		if (events.isKeyJustPressed(GLFW_KEY_TAB)) {
			events.toggleCursor();
		}

		if (events.isKeyJustPressed(GLFW_KEY_ESCAPE)) {
			window.close();
		}

		if (events.isKeyJustPressed(GLFW_MOUSE_BUTTON_1)) {
			mainShader.use();
		}
		else if (events.isKeyJustPressed(GLFW_MOUSE_BUTTON_2)) {
			negativeShader.use();
		}

		if (events.isKeyPressed(GLFW_KEY_W)) {
			camera.moveForward(dTime * speed);
		}
		else if (events.isKeyPressed(GLFW_KEY_S)) {
			camera.moveForward(-dTime * speed);
		}
		if (events.isKeyPressed(GLFW_KEY_A)) {
			camera.moveRight(-dTime * speed);
		}
		else if (events.isKeyPressed(GLFW_KEY_D)) {
			camera.moveRight(dTime * speed);
		}
		if (events.isKeyPressed(GLFW_KEY_SPACE)) {
			camera.moveUp(dTime * speed);
		}
		else if (events.isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
			camera.moveUp(-dTime * speed);
		}

		if (events.isCursorFrozen()) {
			double_t vertical = events.mouseDeltaY() / window.height() * 2;
			double_t horizontal = events.mouseDeltaX() / window.width() * 2;

			camera.rotate(vertical, horizontal, 0);
		}

		mainShader.uniformMatrix("projView", camera.getProjection() * camera.getView());
		negativeShader.uniformMatrix("projView", camera.getProjection() * camera.getView());

		mainShader.uniformMatrix("model", model);
		negativeShader.uniformMatrix("model", model);

		window.clear();

		textureData.draw();

		window.swapBuffers();

		events.pollEvents();
	}
}