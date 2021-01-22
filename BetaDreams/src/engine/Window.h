// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_ENGINE_WINDOW_H_INCLUDED
#define BETA_ENGINE_WINDOW_H_INCLUDED

#include <cstdint>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "exception/BetaException.h"
#include "Types.h"


namespace beta::engine {

	/// <summary>
	/// Represents possible cursor modes.
	/// </summary>
	enum class CursorMode {
		NORMAL = GLFW_CURSOR_NORMAL,
		HIDDEN = GLFW_CURSOR_HIDDEN,
		DISABLED = GLFW_CURSOR_DISABLED
	};
	
	/// <summary>
	/// Allows to interact with game window.
	/// </summary>
	class Window {
	public:
		static int32_t maxWidth();
		static int32_t maxHeight();

		static int32_t width();
		static int32_t height();

		static const std::string& title();
		static bool shouldClose();

		static float_t aspectRatio();

		static void setCursorMode(CursorMode mode);

		static bool isFullscreen();
		static void toggleFullscreen();
		static void makeFullscreen();
		static void makeWindowed();

		
		static void setFillColor(const Color& color);
		static void clear();
		static void swapBuffers();

		static void close();
	private:
		friend class InputHandler;
		
		Window();
		~Window();
		static Window& instance();

		static constexpr int32_t MINIMAL_WIDTH = 640;
		static constexpr int32_t MINIMAL_HEIGHT = 480;

		static constexpr int32_t DEFAULT_WIDTH = 800;
		static constexpr int32_t DEFAULT_HEIGHT = 600;

		int32_t m_maxWidth;
		int32_t m_maxHeight;

		int32_t m_width;
		int32_t m_height;

		std::string m_title;

		bool m_isFullscreen;

		GLFWwindow* m_window;
		static GLFWwindow* getWindowPtr();

		

		void resize(int32_t width, int32_t height);
		void setPosition(int32_t x, int32_t y);
		void centerOnScreen();

		void m_makeFullscreen_impl();
		void m_makeWindowed_impl();
	};
}

#endif // !BETA_ENGINE_WINDOW_H_INCLUDED
