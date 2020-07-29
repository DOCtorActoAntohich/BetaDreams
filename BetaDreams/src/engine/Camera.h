// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_GRAPHICS_CAMERA_H_INCLUDED
#define BETA_GRAPHICS_CAMERA_H_INCLUDED

#include <memory>
#include <glm/glm.hpp>

#include "engine/Window.h"

namespace beta::engine {
	class Camera {
	public:
		using Ptr = std::unique_ptr<Camera>;
		static Camera::Ptr create(engine::Window& window, const glm::vec3& position, float_t fov);
		
		glm::mat4 getProjection();
		glm::mat4 getView();

		void moveForward(double_t value);
		void moveRight(double_t value);
		void moveUp(double_t value);

		/**
		 * Rotates camera by given angles (in radians).
		 * Positive values rotate camera in stated direction,
		 * while negative ones rotate it in opposite direction.
		 * 
		 * \param up Changes how camera looks up and down.
		 * \param right Changes how camera looks right and left.
		 * \param clockwise Rotates camera clockwise and counter-clockwise.
		 */
		void rotate(double_t up, double_t right, double_t clockwise) noexcept;

		Camera& operator=(const Camera& copy) = delete;
	private:
		Camera(engine::Window& window, const glm::vec3& position, float_t fov);
		Camera(const Camera& copy) = delete;

		engine::Window& m_sourceWindow;

		float_t m_FOV;
		glm::vec3 m_position;

		glm::mat4 m_rotation;

		glm::vec3 m_front;
		glm::vec3 m_right;
		glm::vec3 m_up;
		glm::vec3 m_facing;
		void updateVectors();
	};
}

#endif // !BETA_GRAPHICS_CAMERA_H_INCLUDED
