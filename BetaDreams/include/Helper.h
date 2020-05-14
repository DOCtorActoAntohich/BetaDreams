// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef _BETA_HELPER_H
#define _BETA_HELPER_H

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace beta {
	class Helper {
	public:
		/**
		 * Gets the last error occurred in GLFW library.
		 * 
		 * \return A string describing the error.
		 */
		static std::string getGlfwError();


		/**
		 * Gets the last error occurred in GLEW library.
		 * 
		 * \param code An error code GLEW returned from some function.
		 * \return A string describing the error.
		 */
		static std::string getGlewError(GLenum code);

	private:
		Helper();
	};
}

#endif // !_BETA_HELPER_H
