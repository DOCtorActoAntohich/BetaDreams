// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Window.h"

#include "Helper.h"
#include "Log.h"

using namespace beta::engine;


#pragma region C Wrapper

inline void my_glfw_initialize() {
	if (glfwInit() == GLFW_FALSE) {
		throw std::runtime_error(beta::Helper::getGlfwError());
	}
	beta::Log::debug("Initialized GLFW.");
}


inline void my_glfw_terminate() {
	glfwTerminate();
	beta::Log::debug("Terminated GLFW.");
}


inline void my_glew_initialize() {
	glewExperimental = GL_TRUE;
	auto result = glewInit();
	if (result != GLEW_OK) {
		throw std::runtime_error(beta::Helper::getGlewError(result));
	}
}


inline std::pair<int32_t, int32_t> get_screen_resolution() {
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	return { mode->width, mode->height };
}


inline GLFWwindow* create_window(const int32_t width, const int32_t height, const std::string& title) {
	glfwWindowHint(GLFW_RESIZABLE, true);

	static constexpr uint32_t MXAA_SAMPLES = 4;
	glfwWindowHint(GLFW_SAMPLES, MXAA_SAMPLES);

	GLFWwindow* window = glfwCreateWindow(
		width, height, title.c_str(), nullptr, nullptr
	);
	if (window == nullptr) {
		throw std::runtime_error(beta::Helper::getGlfwError());
	}

	glViewport(0, 0, width, height);
	glfwMakeContextCurrent(window);

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

	return window;
}

#pragma /* C Wrapper. */ endregion



Window::Window()
	: m_width(DEFAULT_WIDTH), m_height(DEFAULT_HEIGHT)
	, m_title("Beta Dreams"), m_isFullscreen(false)
	, m_window(nullptr)
{
	my_glfw_initialize();

	std::tie(m_maxWidth, m_maxHeight) = get_screen_resolution();

	m_window = create_window(m_width, m_height, m_title);
	glfwSetWindowSizeLimits(m_window, MINIMAL_WIDTH, MINIMAL_HEIGHT, m_maxWidth, m_maxHeight);
	this->centerOnScreen();
	Log::debug("Initialized window with size ({0}, {1}).", m_width, m_height);

	my_glew_initialize();
}

Window::~Window() {
	glfwDestroyWindow(m_window);
	my_glfw_terminate();
}


Window& Window::instance() {
	static Window instance;
	return instance;
}



int32_t Window::maxWidth() {
	return instance().m_maxWidth;
}

int32_t Window::maxHeight() {
	return instance().m_maxHeight;
}


int32_t Window::width() {
	return instance().m_width;
}

int32_t Window::height() {
	return instance().m_height;
}

const std::string& Window::title() {
	return instance().m_title;
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(instance().m_window);
}

float_t Window::aspectRatio() {
	return static_cast<float_t>(instance().m_width) / instance().m_height;
}



void Window::setCursorMode(CursorMode mode) {
	glfwSetInputMode(instance().m_window, GLFW_CURSOR, static_cast<int32_t>(mode));
}



bool Window::isFullscreen() {
	return instance().m_isFullscreen;
}

void Window::toggleFullscreen() {
	Window::isFullscreen() ? Window::makeWindowed() : Window::makeFullscreen();
}

void Window::makeFullscreen() {
	instance().m_makeFullscreen_impl();
}

void Window::makeWindowed() {
	instance().m_makeWindowed_impl();
}



void Window::setFillColor(const Color& color) {
	instance();
	auto [r, g, b, a] = color.glComponents();
	glClearColor(r, g, b, a);
}

void Window::clear() {
	instance();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swapBuffers() {
	glfwSwapBuffers(instance().m_window);
}



void Window::close() {
	glfwSetWindowShouldClose(instance().m_window, GLFW_TRUE);
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



void Window::m_makeFullscreen_impl() {
	this->setPosition(0, 0);
	this->resize(m_maxWidth, m_maxHeight);
	m_isFullscreen = true;
}

void Window::m_makeWindowed_impl() {
	this->centerOnScreen();
	this->resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	m_isFullscreen = false;
}


GLFWwindow* Window::getWindowPtr() {
	return instance().m_window;
}
