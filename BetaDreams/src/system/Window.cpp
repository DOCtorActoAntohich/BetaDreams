#include "system/Window.h"

#include "exception/Exceptions.h"
#include "Helper.h"

using namespace beta;


Window::Window() {
	if (!glfwInit()) {
		throw InitializationException(Helper::getGlfwError());
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	m_window = glfwCreateWindow(
		this->getWidth(), this->getHeight(),
		this->getTitle().c_str(), nullptr, nullptr
	);

	if (m_window == nullptr) {
		throw InitializationException(Helper::getGlfwError());
		glfwTerminate();
	}
	
	glViewport(0, 0, this->getWidth(), this->getHeight());
	glfwMakeContextCurrent(m_window);

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




int32_t Window::getWidth() const {
	return 800;
}


int32_t Window::getHeight() const {
	return 600;
}


std::string Window::getTitle() const {
	return "Beta Dreams";
}





bool Window::shouldClose() {
	return glfwWindowShouldClose(m_window);
}



void Window::swapBuffers() {
	glfwSwapBuffers(m_window);
}




