#include "engine/Window.h"

#include "exception/Exceptions.h"
#include "Helper.h"

using namespace beta::engine;


Window::Window() {
	// Initialize GLFW.
	if (!glfwInit()) {
		throw InitializationException(Helper::getGlfwError());
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	m_window = glfwCreateWindow(
		this->getWidth(), this->getHeight(),
		this->getTitle().c_str(), nullptr, nullptr
	);

	if (m_window == nullptr) {
		glfwTerminate();
		throw InitializationException(Helper::getGlfwError());
	}
	
	glViewport(0, 0, this->getWidth(), this->getHeight());
	glfwMakeContextCurrent(m_window);

	// Initialize GLEW.
	glewExperimental = GL_TRUE;
	auto result = glewInit();
	if (result != GLEW_OK) {
		throw InitializationException(Helper::getGlewError(result));
	}
}




Window::~Window() {
	if (m_window != nullptr) {
		glfwDestroyWindow(m_window);
	}

	glfwTerminate();
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



void Window::swapBuffers() {
	glfwSwapBuffers(m_window);
}



void Window::close() {
	glfwSetWindowShouldClose(m_window, true);
}





GLFWwindow* Window::getWindow() const noexcept {
	return m_window;
}