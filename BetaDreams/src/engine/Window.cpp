// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Window.h"

#include "Helper.h"
#include "Log.h"

using namespace beta::engine;


Window::InitializationException::InitializationException(std::string message)
	: BetaException(message) {}



Window::Window() : m_glfw() {
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	m_maxWidth = mode->width;
	m_maxHeight = mode->height;

	m_width = DEFAULT_WIDTH;
	m_height = DEFAULT_HEIGHT;

	m_isFullscreen = false;

	m_window = m_glfw.createWindow(m_width, m_height, this->title(), true);
	glfwSetWindowSizeLimits(m_window, MINIMAL_WIDTH, MINIMAL_HEIGHT, m_maxWidth, m_maxHeight);
	this->centerOnScreen();
	this->setFillColor(Color::cornflowerBlue());
	Log::debug("Initialized window with size ({0}, {1}).", m_width, m_height);

	glewExperimental = GL_TRUE;
	auto result = glewInit();
	if (result != GLEW_OK) {
		throw InitializationException(Helper::getGlewError(result));
	}

	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}




Window::~Window() {
	if (m_window != nullptr) {
		glfwDestroyWindow(m_window);
		Log::debug("Window closed.");
	}
}



int32_t Window::maxWidth() const noexcept {
	return m_maxWidth;
}

int32_t Window::maxHeight() const noexcept {
	return m_maxHeight;
}

int32_t Window::width() const noexcept {
	return m_width;
}

int32_t Window::height() const noexcept {
	return m_height;
}

std::string Window::title() const noexcept {
	return "Beta Dreams";
}



bool Window::shouldClose() const noexcept {
	return glfwWindowShouldClose(m_window);
}



float_t Window::acpectRatio() const noexcept {
	return static_cast<float_t>(m_width) / m_height;
}



void Window::resize(int32_t width, int32_t height) {
	m_width = width;
	m_height = height;
	glfwSetWindowSize(m_window, width, height);
	glViewport(0, 0, m_width, m_height);
}

void Window::setPosition(int32_t x, int32_t y) {
	glfwSetWindowPos(m_window, x, y);
}

void Window::centerOnScreen() {
	int32_t xCenter = m_maxWidth / 2;
	int32_t yCenter = m_maxHeight / 2;

	int32_t xWindowHalfSize = DEFAULT_WIDTH / 2;
	int32_t yWindowHalfSize = DEFAULT_HEIGHT / 2;

	this->setPosition(xCenter - xWindowHalfSize, yCenter - yWindowHalfSize);
}



void Window::setFillColor(const Color& color) noexcept {
	auto [r, g, b, a] = color.glComponents();
	glClearColor(r, g, b, a);
}



void Window::setCursorMode(CursorMode mode) {
	glfwSetInputMode(m_window, GLFW_CURSOR, static_cast<int32_t>(mode));
}



bool Window::isFullscreen() const noexcept {
	return m_isFullscreen;
}

void Window::toggleFullscreen() noexcept {
	this->isFullscreen() ? makeWindowed() : makeFullscreen();
}

void Window::makeFullscreen() noexcept {
	this->setPosition(0, 0);
	this->resize(m_maxWidth, m_maxHeight);
	m_isFullscreen = true;
}

void Window::makeWindowed() noexcept {
	this->centerOnScreen();
	this->resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	m_isFullscreen = false;
}



void Window::clear() const noexcept {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
	Log::debug("Initialized GLFW.");
}

Window::GlfwState::~GlfwState() {
	if (GlfwState::isInitialized) {
		GlfwState::isInitialized = false;
		glfwTerminate();
		Log::debug("Terminated GLFW.");
	}
}


GLFWwindow* Window::GlfwState::createWindow(uint32_t width, uint32_t height,
											const std::string& title,
											bool isResizable) {
	if (GlfwState::isWindowCreated) {
		throw InitializationException("Window is already created");
	}

	glfwWindowHint(GLFW_RESIZABLE, isResizable);

	static constexpr uint32_t MXAA_SAMPLES = 4;
	glfwWindowHint(GLFW_SAMPLES, MXAA_SAMPLES);

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