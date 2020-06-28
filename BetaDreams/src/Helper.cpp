// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Helper.h"

#include <filesystem>
#include <fstream>
#include <chrono>
#include <ctime>
#include <regex>

using namespace beta;

Helper::Helper()
{	}



std::string Helper::getCurrentTime() {
	time_t seconds = std::time(nullptr);
	tm timeinfo;
	localtime_s(&timeinfo, &seconds);

	// The format is:
	// Jan 13 2020 00-13-37 PM
	const char* format = "%B %d %Y %I-%M-%S %p";

	static constexpr uint32_t MAX_SIZE = 80;
	char buffer[MAX_SIZE];
	std::strftime(buffer, MAX_SIZE, format, &timeinfo);
	return std::string(buffer);
}



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



std::string Helper::replace(const std::string& str, const std::string& from, const std::string& to) {
	return std::regex_replace(str, std::regex(from), to);
}



void Helper::createFile(const std::filesystem::path& filename) {
	static std::vector<std::string> forbiddenCharacters = {
		"\\", ":", "\"", "?", "<", ">", "|"
	};
	for (auto chr : forbiddenCharacters) {
		if (filename.string().find(chr) != std::string::npos) {
			throw std::ofstream::failure("Forbidden symbol in file path: " + chr);
		}
	}

	if (!std::filesystem::exists(filename)) {
		std::ofstream(filename, std::fstream::trunc);
	}
}