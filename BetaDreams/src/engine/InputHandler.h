// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_ENGINE_EVENTS_H_INCLUDED
#define BETA_ENGINE_EVENTS_H_INCLUDED

#include <array>

#include "engine/Window.h"

namespace beta::engine {
	class InputHandler {
	public:
		static void pollEvents();

		static bool isKeyPressed(int32_t code);
		static bool isKeyJustPressed(int32_t code);
		static bool isButtonPressed(int32_t code);
		static bool isButtonJustPressed(int32_t code);

		static double_t mouseDeltaX();
		static double_t mouseDeltaY();

		static void freezeCursor();
		static void unfreezeCursor();
		static void toggleCursor();
		static bool isCursorFrozen();

	private:
		InputHandler();

		static InputHandler& instance();

		using KeyState = struct {
			uint32_t frame;
			bool isPressed;
		};

		static const uint32_t KEYBOARD_KEYS = 1024;
		static const uint32_t MOUSE_BUTTONS = 16;

		uint32_t m_currentFrame;

		std::array<KeyState, KEYBOARD_KEYS> m_keyboardKeysState;
		std::array<KeyState, MOUSE_BUTTONS> m_mouseButtonsState;

		double_t m_xMouseDelta;
		double_t m_yMouseDelta;
		double_t m_xMousePos;
		double_t m_yMousePos;
		bool m_isCursorLocked;
		bool m_isCursorStarted;

		void m_pollEvents_impl();
		void m_subExtraFrames();

		void updateKeyboardKeyState(int32_t key, int32_t scancode, int32_t action, int32_t mode);
		void updateMouseButtonState(int32_t button, int32_t action, int32_t mode);
		void updateCursorPosition(double_t xpos, double_t ypos);
		void resizeWindow(int32_t width, int32_t height);

		static void keyboardCallback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mode);
		static void mouseCallback(GLFWwindow* window, int32_t button, int32_t action, int32_t mode);
		static void cursorPositionCallback(GLFWwindow* window, double_t xpos, double_t ypos);
		static void windowResizeCallback(GLFWwindow* window, int32_t width, int32_t height);
	};
}

#endif // !BETA_ENGINE_EVENTS_H_INCLUDED
