#include "Helper.h"

using namespace beta;

Helper::Helper()
{	}



std::string Helper::getGlfwError() {
	const char* error;
	glfwGetError(&error);
	if (error != nullptr) {
		return std::string(error);
	}
	return "";
}



std::string Helper::getGlewError(const GLenum code) {
	char* buffer = (char*)glewGetErrorString(code);
	return std::string(buffer);
}
