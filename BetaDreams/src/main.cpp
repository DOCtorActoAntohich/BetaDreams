#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "system/Window.h"

int main(int argc, char** argv) {
	beta::Window window;

	while (!window.shouldClose()) {
		glfwPollEvents();
		window.swapBuffers();
	}

	return 0;
}
