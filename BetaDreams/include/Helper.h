#ifndef _BETA_HELPER_H
#define _BETA_HELPER_H

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace beta {
	class Helper {
	public:
		static std::string getGlfwError();
		static std::string getGlewError(GLenum code);

	private:
		Helper();
	};
}

#endif // _BETA_HELPER_H
