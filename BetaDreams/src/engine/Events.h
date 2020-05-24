// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef _BETA_ENGINE_EVENTS_H
#define _BETA_ENGINE_EVENTS_H

#include <array>

#include "engine/Window.h"

namespace beta::engine {
	/**
	 * A wrapper over GLFW/OpenGL event system.
	 */
	class Events {
	public:
		/**
		 * Creates ah event handler for a specific window.
		 * 
		 * \param window A window to get events from.
		 */
		Events(Window& window);

		/**
		 * Updates the state of keyboard and mouse.
		 */
		void pollEvents();

		
		/**
		 * Checks if a keyboard key is being held.
		 * 
		 * \param code A code of a key.
		 * \return true if the key is pressed, false if it is released.
		 */
		bool isKeyPressed(int32_t code);

		/**
		 * Checks if a keyboard key gets pressed on a current tick.
		 * 
		 * \param code A code of a key.
		 * \return true if a key is pressed on current tick, false otherwise.
		 */
		bool isKeyJustPressed(int32_t code);

		/**
		 * Checks if a mouse button is being held.
		 *
		 * \param code A code of a button.
		 * \return true if the button is pressed, false if it is released.
		 */
		bool isButtonPressed(int32_t code);

		/**
		 * Checks if a mouse button gets pressed on a current tick.
		 *
		 * \param code A code of a button.
		 * \return true if a button is pressed on current tick, false otherwise.
		 */
		bool isButtonJustPressed(int32_t code);

		double_t mouseDeltaX() const noexcept;
		double_t mouseDeltaY() const noexcept;

		void freezeCursor();
		void unfreezeCursor();
		void toggleCursor();
		bool isCursorFrozen() const noexcept;

	private:

		Window& m_sourceWindow;

		/**
		 * Describes a key or a button state at some frame.
		 */
		typedef struct {
			uint32_t frame;
			bool isPressed;
		} KeyState;

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
		void resizeWindow(int32_t width, int32_t height);

		static void keyboardCallback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mode);
		static void mouseCallback(GLFWwindow* window, int32_t button, int32_t action, int32_t mode);
		static void cursorPositionCallback(GLFWwindow* window, double_t xpos, double_t ypos);
		static void windowResizeCallback(GLFWwindow* window, int32_t width, int32_t height);
	};
}

#endif // !_BETA_ENGINE_EVENTS_H