#ifndef _BETA_ENGINE_WINDOW_H
#define _BETA_ENGINE_WINDOW_H

#include <cstdint>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace beta::engine {
	/**
	 * Describes a graphical output for an app.
	 */
	class Window {
	public:
		/**
		 * Constructs and initializes window.
		 * OpenGL is also initialized here.
		 */
		Window();
		/**
		 * Finalizes the window.
		 * OpenGL is alse terminated here.
		 */
		~Window();

		/**
		 * Gets the width of a window.
		 * 
		 * \return A width of a window.
		 */
		int32_t getWidth() const noexcept;

		/**
		 * Gets the height of a window.
		 * 
		 * \return A height of a window.
		 */
		int32_t getHeight() const noexcept;

		/**
		 * Gets the name of a window.
		 * 
		 * \return A window caption string.
		 */
		std::string getTitle() const noexcept;

		/**
		 * Checks if the window chould close after a current tick.
		 * 
		 * \return true if window should close after a current tick, false otherwise
		 */
		bool shouldClose() const noexcept;

		/**
		 * Draws the current frame.
		 */
		void swapBuffers();

		/**
		 * Closes the window.
		 * It should allow a window to successfully finish handling current tick.
		 */
		void close();

	private:

		friend class Events;

		/**
		 * Returns a pointer to a window.
		 * 
		 * \return A pointer to GLFW window instance.
		 */
		GLFWwindow* getWindow() const noexcept;
		GLFWwindow* m_window;
	};
}

#endif // !_BETA_ENGINE_WINDOW_H
