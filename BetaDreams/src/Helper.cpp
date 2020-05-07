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



std::string Helper::getGlShaderInfoLog(GLuint id) {
	static const uint32_t SIZE = 512;
	GLchar infoLog[SIZE];
	glGetShaderInfoLog(id, SIZE, nullptr, infoLog);
	return std::string(infoLog);
}



std::string Helper::getGlProgramInfoLog(GLuint id) {
	static const uint32_t SIZE = 512;
	GLchar infoLog[SIZE];
	glGetProgramInfoLog(id, SIZE, nullptr, infoLog);
	return std::string(infoLog);
}
