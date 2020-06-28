// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_H_INCLUDEDELPER_H_INCLUDED
#define BETA_H_INCLUDEDELPER_H_INCLUDED

#include <string>
#include <filesystem>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace beta {
	class Helper {
	public:
		/**
		 * Gets the string describing current time.
		 *
		 * \return A string with current time.
		 */
		static std::string getCurrentTime();

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

		/**
		 * Replaces substring.
		 *
		 * \param str A string to handle.
		 * \param from What substring to replace.
		 * \param to Replacement.
		 * \return A string with replaced substrings.
		 */
		static std::string replace(const std::string& str, const std::string& from, const std::string& to);

		static void createFile(const std::filesystem::path& path);

	private:
		Helper();
	};
}

#endif // !BETA_H_INCLUDEDELPER_H_INCLUDED
