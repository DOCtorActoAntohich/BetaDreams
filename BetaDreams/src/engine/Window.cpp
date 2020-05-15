// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "engine/Window.h"

#include "Helper.h"

using namespace beta::engine;


Window::InitializationException::InitializationException(std::string message)
	: BetaException(message) {}



Window::Window() {
	m_window = m_glfw.createWindow(this->getWidth(), this->getHeight(), this->getTitle(), true);

	// Initialize GLEW.
	glewExperimental = GL_TRUE;
	auto result = glewInit();
	if (result != GLEW_OK) {
		throw InitializationException(Helper::getGlewError(result));
	}

	this->setFillColor(utility::Color::cornflowerBlue());

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}




Window::~Window() {
	if (m_window != nullptr) {
		glfwDestroyWindow(m_window);
	}
}




int32_t Window::getWidth() const noexcept {
	return 800;
}


int32_t Window::getHeight() const noexcept {
	return 600;
}


std::string Window::getTitle() const noexcept {
	return "Beta Dreams";
}



bool Window::shouldClose() const noexcept {
	return glfwWindowShouldClose(m_window);
}



void Window::setFillColor(const utility::Color& color) noexcept {
	auto [r, g, b, a] = color.glComponents();
	glClearColor(r, g, b, a);
}



void Window::clear() const noexcept {
	glClear(GL_COLOR_BUFFER_BIT);
}



void Window::swapBuffers() {
	glfwSwapBuffers(m_window);
}



void Window::close() {
	glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}





GLFWwindow* Window::getWindow() const noexcept {
	return m_window;
}





bool Window::GlfwState::isInitialized = false;
bool Window::GlfwState::isWindowCreated = false;

Window::GlfwState::GlfwState() {
	if (GlfwState::isInitialized) {
		throw InitializationException("GLFW is already initialized");
	}

	int32_t initialized = glfwInit();
	if (initialized == GLFW_FALSE) {
		throw InitializationException(Helper::getGlfwError());
	}

	GlfwState::isInitialized = true;
}

Window::GlfwState::~GlfwState() {
	if (GlfwState::isInitialized) {
		GlfwState::isInitialized = false;
		glfwTerminate();
	}
}


GLFWwindow* Window::GlfwState::createWindow(uint32_t width, uint32_t height,
											const std::string& title,
											bool isResizable) {
	if (GlfwState::isWindowCreated) {
		throw InitializationException("Window is already created");
	}

	glfwWindowHint(GLFW_RESIZABLE, isResizable);
	GLFWwindow* window = glfwCreateWindow(
		width, height, title.c_str(), nullptr, nullptr
	);
	if (window == nullptr) {
		throw InitializationException(Helper::getGlfwError());
	}

	GlfwState::isWindowCreated = true;

	glViewport(0, 0, width, height);
	glfwMakeContextCurrent(window);

	return window;
}