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
#include "engine/InputHandler.h"
#include "engine/VAO.h"
#include "engine/Camera.h"

#include "graphics/Texture.h"
#include "graphics/ShaderProgram.h"

#include "world/Chunk.h"
#include "world/World.h"

using namespace beta;

App::App()
{	}


void App::run() {
	using engine::Window;
	using engine::InputHandler;

	Window::setFillColor(Color::cornflowerBlue());
	InputHandler::pollEvents();
	auto camera = std::make_unique<engine::Camera>(glm::vec3(8, 8, 8), glm::radians(70.0f));

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

	while (!Window::shouldClose()) {
		double_t currentTime = glfwGetTime();
		dTime = currentTime - lastTime;
		lastTime = currentTime;

		fps = static_cast<uint32_t>(1 / dTime);

		if (InputHandler::isKeyJustPressed(GLFW_KEY_TAB)) {
			InputHandler::toggleCursor();
		}

		if (InputHandler::isKeyJustPressed(GLFW_KEY_ESCAPE)) {
			Window::close();
		}

		if (InputHandler::isKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
			speed = 8;
		}
		else {
			speed = 2;
		}

		if (InputHandler::isKeyPressed(GLFW_KEY_W)) {
			camera->moveForward(dTime * speed);
		}
		else if (InputHandler::isKeyPressed(GLFW_KEY_S)) {
			camera->moveForward(-dTime * speed);
		}
		if (InputHandler::isKeyPressed(GLFW_KEY_A)) {
			camera->moveRight(-dTime * speed);
		}
		else if (InputHandler::isKeyPressed(GLFW_KEY_D)) {
			camera->moveRight(dTime * speed);
		}
		if (InputHandler::isKeyPressed(GLFW_KEY_SPACE)) {
			camera->moveUp(dTime * speed);
		}
		else if (InputHandler::isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
			camera->moveUp(-dTime * speed);
		}

		if (InputHandler::isKeyJustPressed(GLFW_KEY_F11)) {
			Window::toggleFullscreen();
		}


		if (InputHandler::isCursorFrozen()) {
			double_t vertical = InputHandler::mouseDeltaY() / Window::height() * 2;
			double_t horizontal = InputHandler::mouseDeltaX() / Window::width() * 2;

			camera->rotate(vertical, horizontal, 0);
		}

		mainShader.uniformMatrix("projView", camera->getProjection() * camera->getView());
		mainShader.uniformMatrix("model", model);

		Window::clear();

		world.draw();

		Window::swapBuffers();

		InputHandler::pollEvents();
	}
}