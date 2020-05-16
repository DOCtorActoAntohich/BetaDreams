// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "graphics/Camera.h"

#include <glm/ext.hpp>


using namespace beta::graphics;

Camera::Camera(engine::Window& window, const glm::vec3& position, float_t fov)
	: m_sourceWindow(window),
	  m_position(position), m_FOV(fov), m_rotation(1.0f) {
	this->updateVectors();
}



glm::mat4 Camera::getProjection() {
	float_t aspect = m_sourceWindow.acpectRatio();
	return glm::perspective(m_FOV, aspect, 0.1f, 100.0f);
}



glm::mat4 Camera::getView() {
	return glm::lookAt(m_position, m_position + m_front, m_up);
}



void Camera::moveForward(double_t value) {
	m_position += m_front * static_cast<float_t>(value);
}

void Camera::moveRight(double_t value) {
	m_position += m_right * static_cast<float_t>(value);
}

void Camera::moveUp(double_t value) {
	m_position += m_up * static_cast<float_t>(value);
}



void Camera::rotate(double_t up, double_t right, double_t clockwise) noexcept {
	m_rotation = glm::mat4(1.0f);

	static double_t aroundZ = 0;
	static double_t aroundY = 0;
	static double_t aroundX = 0;
	
	aroundZ += -clockwise;
	aroundY += -right;
	aroundX += -up;

	static const constexpr float_t VERTICAL_BOUNDARY = glm::radians(89.0f);
	if (aroundX < -VERTICAL_BOUNDARY) {
		aroundX = -VERTICAL_BOUNDARY;
	}
	else if (aroundX > VERTICAL_BOUNDARY) {
		aroundX = VERTICAL_BOUNDARY;
	}

	// The order is strict.
	m_rotation = glm::rotate(m_rotation, static_cast<float_t>(aroundZ), glm::vec3(0, 0, 1));
	m_rotation = glm::rotate(m_rotation, static_cast<float_t>(aroundY), glm::vec3(0, 1, 0));
	m_rotation = glm::rotate(m_rotation, static_cast<float_t>(aroundX), glm::vec3(1, 0, 0));

	updateVectors();
}



void Camera::updateVectors() {
	// For me not to forget:
	// X-axis goes to the right from the camera.
	// Y-axis goes up, Z-axis goes back.

	m_front = glm::vec3(m_rotation * glm::vec4(0, 0, -1, 1));
	m_right	= glm::vec3(m_rotation * glm::vec4(1, 0, 0, 1));
	m_up	= glm::vec3(m_rotation * glm::vec4(0, 1, 0, 1));
}
