#ifndef _BETA_HELPER_H
#define _BETA_HELPER_H

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace beta {
	class Helper {
	public:
		/**
		 * Gets the last error occured in GLFW library.
		 * 
		 * \return A string describing the error.
		 */
		static std::string getGlfwError();


		/**
		 * Gets the last error occured in GLEW library.
		 * 
		 * \param code An error code GLEW returned from some function.
		 * \return A string describing the error.
		 */
		static std::string getGlewError(GLenum code);

		/**
		 * Gets the information about a shader with given id.
		 * This function will return the description of an error if it occurs.
		 * 
		 * \param id An identifier of a shader.
		 * \return A string describing the shader.
		 */
		static std::string getGlShaderInfoLog(GLuint id);

		/**
		 * Geth the information about a program with fiven id.
		 * This function will return the description of an error if it occurs.
		 *
		 * \param id An identifier of a program.
		 * \return A string describing the program.
		 */
		static std::string getGlProgramInfoLog(GLuint id);

	private:
		Helper();
	};
}

#endif // !_BETA_HELPER_H
