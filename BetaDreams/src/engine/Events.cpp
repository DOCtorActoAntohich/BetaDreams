#include "engine/Events.h"

#include <algorithm>

using namespace beta::engine;



Events::Events(const Window& window) {
	m_currentFrame = 0;

	KeyState initialKeyState = { m_currentFrame, false };
	m_keyboardKeysState.fill(initialKeyState);
	m_mouseButtonsState.fill(initialKeyState);

	m_xMouseDelta = m_yMouseDelta = 0.0;
	m_xMousePos = m_yMousePos = 0.0;
	m_isCursorStarted = false;
	m_isCursorLocked = false;

	GLFWwindow*  sourceWindow = window.getWindow();
	glfwSetWindowUserPointer(sourceWindow, this);

	glfwSetKeyCallback(sourceWindow, Events::keyboardCallback);
	glfwSetMouseButtonCallback(sourceWindow, Events::mouseCallback);
	glfwSetCursorPosCallback(sourceWindow, Events::cursorPositionCallback);
}



void Events::pollEvents() {
	++m_currentFrame;

	glfwPollEvents();
}



bool Events::isKeyPressed(int32_t code) {
	if (code < 0 || code >= KEYBOARD_KEYS) {
		return false;
	}
	return m_keyboardKeysState[code].isPressed;
}

bool Events::isKeyJustPressed(int32_t code) {
	return isKeyPressed(code) && m_keyboardKeysState[code].frame == m_currentFrame;
}



bool Events::isButtonPressed(int32_t code) {
	if (code < 0 || code >= MOUSE_BUTTONS) {
		return false;
	}
	return m_keyboardKeysState[code].isPressed;
}

bool Events::isButtonJustPressed(int32_t code) {
	return isButtonPressed(code) && m_mouseButtonsState[code].frame == m_currentFrame;
}





inline void Events::updateKeyboardKeyState(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
	if (action == GLFW_PRESS) {
		m_keyboardKeysState[key].isPressed = true;
	}
	else if (action == GLFW_RELEASE) {
		m_keyboardKeysState[key].isPressed = false;
	}
	m_keyboardKeysState[key].frame = m_currentFrame;
}



inline void Events::updateMouseButtonState(int32_t button, int32_t action, int32_t mode) {
	if (action == GLFW_PRESS) {
		m_keyboardKeysState[button].isPressed = true;
	}
	else if (action == GLFW_RELEASE) {
		m_keyboardKeysState[button].isPressed = false;
	}
	m_keyboardKeysState[button].frame = m_currentFrame;
}



inline void Events::updateCursorPosition(double_t xpos, double_t ypos) {
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



inline void Events::keyboardCallback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mode) {
	auto instance = static_cast<Events*>(glfwGetWindowUserPointer(window));
	instance->updateKeyboardKeyState(key, scancode, action, mode);
}


inline void Events::mouseCallback(GLFWwindow* window, int32_t button, int32_t action, int32_t mode) {
	auto instance = static_cast<Events*>(glfwGetWindowUserPointer(window));
	instance->updateMouseButtonState(button, action, mode);
}


inline void Events::cursorPositionCallback(GLFWwindow* window, double_t xpos, double_t ypos) {
	auto instance = static_cast<Events*>(glfwGetWindowUserPointer(window));
	instance->updateCursorPosition(xpos, ypos);
}