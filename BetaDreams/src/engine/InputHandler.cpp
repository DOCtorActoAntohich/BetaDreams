// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "InputHandler.h"

#include <algorithm>

#include "Log.h"

using namespace beta::engine;


InputHandler::InputHandler()
	: m_currentFrame(0)
	, m_isCursorLocked(false), m_isCursorStarted(false)
	, m_xMousePos(0), m_yMousePos(0)
	, m_xMouseDelta(0), m_yMouseDelta(0)
{
	KeyState initialKeyState = { m_currentFrame, false };
	m_keyboardKeysState.fill(initialKeyState);
	m_mouseButtonsState.fill(initialKeyState);

	GLFWwindow* sourceWindow = Window::getWindowPtr();
	glfwSetWindowUserPointer(sourceWindow, this);

	glfwSetKeyCallback(sourceWindow, InputHandler::keyboardCallback);
	glfwSetMouseButtonCallback(sourceWindow, InputHandler::mouseCallback);
	glfwSetCursorPosCallback(sourceWindow, InputHandler::cursorPositionCallback);
	glfwSetWindowSizeCallback(sourceWindow, InputHandler::windowResizeCallback);

	Log::debug("Initialized Input Handler.");
}


InputHandler& InputHandler::instance() {
	static InputHandler inputHandler;
	return inputHandler;
}



void InputHandler::pollEvents() {
	instance().m_pollEvents_impl();
}

void InputHandler::m_pollEvents_impl() {
	// To avoid overflow.
	constexpr uint32_t MAX_FRAMES = 2000000000u;
	if (m_currentFrame > MAX_FRAMES) {
		this->m_subExtraFrames();
	}

	++m_currentFrame;

	m_xMouseDelta = m_yMouseDelta = 0;

	glfwPollEvents();
}

void InputHandler::m_subExtraFrames() {
	static auto frame_to_zero = [](KeyState& state) {
		state.frame = 0;
	};

	m_currentFrame = 0;
	std::for_each(m_keyboardKeysState.begin(), m_keyboardKeysState.end(), frame_to_zero);
	std::for_each(m_mouseButtonsState.begin(), m_mouseButtonsState.end(), frame_to_zero);
}




bool InputHandler::isKeyPressed(int32_t code) {
	if (code < 0 || code >= KEYBOARD_KEYS) {
		return false;
	}
	return instance().m_keyboardKeysState[code].isPressed;
}

bool InputHandler::isKeyJustPressed(int32_t code) {
	return isKeyPressed(code) && instance().m_keyboardKeysState[code].frame == instance().m_currentFrame;
}



bool InputHandler::isButtonPressed(int32_t code) {
	if (code < 0 || code >= MOUSE_BUTTONS) {
		return false;
	}
	return instance().m_mouseButtonsState[code].isPressed;
}

bool InputHandler::isButtonJustPressed(int32_t code) {
	return isButtonPressed(code) && instance().m_mouseButtonsState[code].frame == instance().m_currentFrame;
}




double_t InputHandler::mouseDeltaX() {
	return instance().m_xMouseDelta;
}

double_t InputHandler::mouseDeltaY() {
	return instance().m_yMouseDelta;
}



void InputHandler::freezeCursor() {
	instance().m_isCursorLocked = true;
	Window::setCursorMode(CursorMode::DISABLED);
}

void InputHandler::unfreezeCursor() {
	instance().m_isCursorLocked = false;
	Window::setCursorMode(CursorMode::NORMAL);
}

void InputHandler::toggleCursor() {
	if (InputHandler::isCursorFrozen()) {
		InputHandler::unfreezeCursor();
	}
	else {
		InputHandler::freezeCursor();
	}
}

bool InputHandler::isCursorFrozen() {
	return instance().m_isCursorLocked;
}



void InputHandler::updateKeyboardKeyState(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
	if (action == GLFW_REPEAT) {
		return;
	}

	m_keyboardKeysState[key].isPressed = action == GLFW_PRESS;
	m_keyboardKeysState[key].frame = m_currentFrame;
}


void InputHandler::updateMouseButtonState(int32_t button, int32_t action, int32_t mode) {
	if (action == GLFW_REPEAT) {
		return;
	}

	m_mouseButtonsState[button].isPressed = action == GLFW_PRESS;
	m_mouseButtonsState[button].frame = m_currentFrame;
}


void InputHandler::updateCursorPosition(double_t xpos, double_t ypos) {
	if (m_isCursorStarted) {
		m_xMouseDelta = xpos - m_xMousePos;
		m_yMouseDelta = ypos - m_yMousePos;
	}
	else {
		m_isCursorStarted = true;
	}
	m_xMousePos = xpos;
	m_yMousePos = ypos;
}


void InputHandler::resizeWindow(int32_t width, int32_t height) {
	Window::instance().resize(width, height);
}





inline void InputHandler::keyboardCallback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mode) {
	auto instance = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	instance->updateKeyboardKeyState(key, scancode, action, mode);
}


inline void InputHandler::mouseCallback(GLFWwindow* window, int32_t button, int32_t action, int32_t mode) {
	auto instance = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	instance->updateMouseButtonState(button, action, mode);
}


inline void InputHandler::cursorPositionCallback(GLFWwindow* window, double_t xpos, double_t ypos) {
	auto instance = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	instance->updateCursorPosition(xpos, ypos);
}

inline void InputHandler::windowResizeCallback(GLFWwindow* window, int32_t width, int32_t height) {
	auto instance = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	instance->resizeWindow(width, height);
}
