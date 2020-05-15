// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef _BETA_ENGINE_WINDOW_H
#define _BETA_ENGINE_WINDOW_H

#include <cstdint>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "exception/BetaException.h"
#include "utility/Color.h"


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
		 * OpenGL is also terminated here.
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
		 * Checks if the window should close after a current tick.
		 * 
		 * \return true if window should close after a current tick, false otherwise.
		 */
		bool shouldClose() const noexcept;

		/**
		 * Sets color to be drawn first on every frame.
		 *
		 * \param color A color to fill the window.
		 */
		void setFillColor(const utility::Color& color) noexcept;

		/**
		 * Fills the window with color set by setFillColor.
		 */
		void clear() const noexcept;

		/**
		 * Draws the current frame.
		 */
		void swapBuffers();

		/**
		 * Closes the window.
		 * It should allow a window to successfully finish handling current tick.
		 */
		void close();



		/**
		 * An exception that should occur if something failed to initialize.
		 */
		class InitializationException;

	private:

		class GlfwState final {
		public:
			GlfwState();
			~GlfwState();

			GLFWwindow* createWindow(uint32_t width, uint32_t height, const std::string& title, bool isResizable);
		private:
			static bool isInitialized;
			static bool isWindowCreated;
		};

		friend class Events;

		GlfwState m_glfw;

		/**
		 * Returns a pointer to a window.
		 * 
		 * \return A pointer to GLFW window instance.
		 */
		GLFWwindow* getWindow() const noexcept;
		GLFWwindow* m_window;
	};


	
	class Window::InitializationException : public BetaException {
	public:
		InitializationException(std::string message);
	};
	
}

#endif // !_BETA_ENGINE_WINDOW_H
