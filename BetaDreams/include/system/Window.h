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

		int32_t getWidth() const;
		int32_t getHeight() const;
		std::string getTitle() const;

		bool shouldClose();
		void swapBuffers();

	private:

		GLFWwindow* m_window;
	};
}

#endif // _BETA_WINDOW_H
