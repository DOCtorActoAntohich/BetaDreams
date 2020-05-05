#ifndef _BETA_WINDOW_H
#define _BETA_WINDOW_H

#include <cstdint>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace beta {
	class Window {
	public:
		Window();
		~Window();

		int32_t getWidth() const noexcept;
		int32_t getHeight() const noexcept;
		std::string getTitle() const noexcept;

		bool shouldClose() const noexcept;
		void swapBuffers();

		void close();

	private:

		friend class Events;

		GLFWwindow* getWindow() const noexcept;

		GLFWwindow* m_window;
	};
}

#endif // _BETA_WINDOW_H
