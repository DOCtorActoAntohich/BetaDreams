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

#include "graphics/Texture.h"
#include "graphics/ShaderProgram.h"
#include "graphics/VAO.h"
#include "graphics/Camera.h"

#include "world/Chunk.h"
#include "world/World.h"

using namespace beta;

App::App()
{	}


void App::run() {
	engine::Window window;
	engine::Events events(window);
	auto camera = graphics::Camera::create(window, glm::vec3(8, 8, 8), glm::radians(70.0f));

	graphics::ShaderProgram mainShader("main");

	graphics::Texture texture("resource/texture/grid.png");
	mainShader.use();
	texture.bind();

	glm::mat4 model(1.0f);
	
	world::World world;
	world.addEmptyChunk(glm::vec3(0.5, 0.5, 0.5));
	world.addEmptyChunk(glm::vec3(1.5, 0.5, 0.5));
	world.renderAll();

	float_t speed = 2;

	double_t lastTime = glfwGetTime();
	double_t dTime = 0.0f;

	uint32_t fps = 0;

	while (!window.shouldClose()) {
		double_t currentTime = glfwGetTime();
		dTime = currentTime - lastTime;
		lastTime = currentTime;

		fps = static_cast<uint32_t>(1 / dTime);

		if (events.isKeyJustPressed(GLFW_KEY_TAB)) {
			events.toggleCursor();
		}

		if (events.isKeyJustPressed(GLFW_KEY_ESCAPE)) {
			window.close();
		}

		if (events.isKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
			speed = 8;
		}
		else {
			speed = 2;
		}

		if (events.isKeyPressed(GLFW_KEY_W)) {
			camera->moveForward(dTime * speed);
		}
		else if (events.isKeyPressed(GLFW_KEY_S)) {
			camera->moveForward(-dTime * speed);
		}
		if (events.isKeyPressed(GLFW_KEY_A)) {
			camera->moveRight(-dTime * speed);
		}
		else if (events.isKeyPressed(GLFW_KEY_D)) {
			camera->moveRight(dTime * speed);
		}
		if (events.isKeyPressed(GLFW_KEY_SPACE)) {
			camera->moveUp(dTime * speed);
		}
		else if (events.isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
			camera->moveUp(-dTime * speed);
		}

		if (events.isKeyJustPressed(GLFW_KEY_F11)) {
			window.toggleFullscreen();
		}


		if (events.isCursorFrozen()) {
			double_t vertical = events.mouseDeltaY() / window.height() * 2;
			double_t horizontal = events.mouseDeltaX() / window.width() * 2;

			camera->rotate(vertical, horizontal, 0);
		}

		mainShader.uniformMatrix("projView", camera->getProjection() * camera->getView());
		mainShader.uniformMatrix("model", model);

		window.clear();

		world.draw();

		window.swapBuffers();

		events.pollEvents();
	}
}