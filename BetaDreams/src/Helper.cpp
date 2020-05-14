// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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
	const char* buffer = reinterpret_cast<const char*>(glewGetErrorString(code));
	return std::string(buffer);
}