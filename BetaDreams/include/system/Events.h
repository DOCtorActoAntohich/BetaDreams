#ifndef _BETA_EVENTS_H
#define _BETA_EVENTS_H

#include <array>

#include "system/Window.h"

namespace beta {
	class Events {
	public:
		Events(const Window& window);

		void pollEvents();


		bool isKeyPressed(int32_t keycode);
		bool isKeyJustPressed(int32_t keycode);

		bool isButtonPressed(int32_t keycode);
		bool isButtonJustPressed(int32_t keycode);

	private:
		typedef struct {
			uint32_t frame;
			bool isPressed;
		} KeyState;

		GLFWwindow* m_sourceWindow;

		static const uint32_t KEYBOARD_KEYS = 1024;
		static const uint32_t MOUSE_BUTTONS	= 16;

		uint32_t m_currentFrame;

		std::array<KeyState, KEYBOARD_KEYS> m_keyboardKeysState;
		std::array<KeyState, MOUSE_BUTTONS> m_mouseButtonsState;

		double_t m_xMouseDelta;
		double_t m_yMouseDelta;
		double_t m_xMousePos;
		double_t m_yMousePos;
		bool m_isCursorLocked;
		bool m_isCursorStarted;

		void updateKeyboardKeyState(int32_t key, int32_t scancode, int32_t action, int32_t mode);
		void updateMouseButtonState(int32_t button, int32_t action, int32_t mode);
		void updateCursorPosition(double_t xpos, double_t ypos);

		static void keyboardCallback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mode);
		static void mouseCallback(GLFWwindow* window, int32_t button, int32_t action, int32_t mode);
		static void cursorPositionCallback(GLFWwindow* window, double_t xpos, double_t ypos);
	};
}

#endif // _BETA_EVENTS_H