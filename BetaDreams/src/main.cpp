#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "system/Window.h"
#include "system/Events.h"


int main(int argc, char** argv) {
	beta::Window window;
	beta::Events events(window);

	while (!window.shouldClose()) {
		events.pollEvents();

		if (events.isKeyJustPressed(GLFW_KEY_ESCAPE)) {
			window.close();
		}
		window.swapBuffers();
	}

	return 0;
}
