// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ShaderProgram.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include "Helper.h"
#include "Log.h"

using namespace beta::graphics;




ShaderProgram::LoadException::LoadException(std::string message) : BetaException(message)
{	}

ShaderProgram::UsageException::UsageException(std::string message) : BetaException(message)
{	}





ShaderProgram::ShaderProgram() noexcept {}

ShaderProgram::ShaderProgram(std::string shaderName) {
	this->load(shaderName);
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept {
	*this = std::move(other);
}

ShaderProgram::~ShaderProgram() {}



void ShaderProgram::use() {
	m_shaderProgram.use();
}



void ShaderProgram::uniformMatrix(const std::string& name, const glm::mat4& matrix) {
	GLuint transformLoc = glGetUniformLocation(m_shaderProgram.id(), name.c_str());
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}



std::string ShaderProgram::getFileType(const ShaderType type) {
	switch (type)
	{
	case ShaderType::VERTEX:
		return ".glslv";

	case ShaderType::FRAGMENT:
		return ".glslf";

	case ShaderType::GEOMETRY:
		return ".glslg";

	case ShaderType::COMPUTE:
		return ".glslc";

	default:
		throw std::exception("Unknown shader type provided");
	}
}



std::filesystem::path ShaderProgram::getShaderPath(const std::string& name, const ShaderType type) {
	std::filesystem::path path = "resource/shader";
	path /= name;
	path /= name;
	std::string fileFormat = ShaderProgram::getFileType(type);
	path += fileFormat;
	return path;
}



void ShaderProgram::load(const std::string& name) {
	std::filesystem::path vertexFilename = ShaderProgram::getShaderPath(name, ShaderType::VERTEX);
	std::filesystem::path fragmentFilename = ShaderProgram::getShaderPath(name, ShaderType::FRAGMENT);

	try {
		this->load(vertexFilename, fragmentFilename);
		Log::debug("Loaded shader file(s): {0}.", name);
	}
	catch (std::istream::failure&) {
		throw ShaderProgram::LoadException("Unable to read shader file(s) with name: " + name);
	}
}


void ShaderProgram::load(const std::filesystem::path& vertexFile, const std::filesystem::path& fragmentFile) {
	ShaderProgram::My_Shader vertexShader(vertexFile, ShaderType::VERTEX);
	ShaderProgram::My_Shader fragmentShader(fragmentFile, ShaderType::FRAGMENT);

	m_shaderProgram = { vertexShader, fragmentShader };
}



ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept {
	this->m_shaderProgram = std::move(other.m_shaderProgram);
	other.m_shaderProgram = nullptr;

	return *this;
}






ShaderProgram::My_Shader::My_Shader(const std::filesystem::path& path, const ShaderType shaderType) {
	std::string code = this->readCode(path);
	this->compile(code, shaderType);
}

ShaderProgram::My_Shader::~My_Shader() {
	glDeleteShader(m_shaderId);
}



uint32_t ShaderProgram::My_Shader::id() const {
	return m_shaderId;
}


std::string ShaderProgram::My_Shader::readCode(const std::filesystem::path& path) const {
	std::ifstream programFile(path);
	if (!programFile.is_open()) {
		throw std::ifstream::failure("Cannot open file");
	}
	programFile.exceptions(std::ifstream::badbit);

	std::string code{std::istreambuf_iterator<char>(programFile), std::istreambuf_iterator<char>()};
	return code;
}


void ShaderProgram::My_Shader::compile(const std::string& code, const ShaderType shaderType) {
	static const uint32_t AMOUNT = 1;

	m_shaderId = glCreateShader(static_cast<GLenum>(shaderType));
	if (glGetError() == GL_INVALID_ENUM) {
		throw ShaderProgram::LoadException("Invalid shader type provided");
	}
	else if (m_shaderId == 0) {
		throw ShaderProgram::LoadException("Error while creating shader");
	}

	const GLchar* shaderCode_cstr = code.c_str();
	glShaderSource(m_shaderId, AMOUNT, &shaderCode_cstr, nullptr);
	glCompileShader(m_shaderId);

	GLint compilationResult;
	glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &compilationResult);
	if (compilationResult == GL_FALSE) {
		glDeleteShader(m_shaderId);

		static const uint32_t BUFFER_SIZE = 512;
		GLchar infoLog[BUFFER_SIZE];
		glGetShaderInfoLog(m_shaderId, BUFFER_SIZE, nullptr, infoLog);

		std::string message(infoLog);
		throw ShaderProgram::LoadException(message);
	}
}





ShaderProgram::My_Program::My_Program() noexcept {
	m_programId = 0;
}

ShaderProgram::My_Program::My_Program(ShaderProgram::My_Program&& other) noexcept {
	*this = std::move(other);
}


ShaderProgram::My_Program::My_Program(std::initializer_list<ShaderProgram::My_Shader> shaders) {
	m_programId = glCreateProgram();
	if (m_programId == 0) {
		throw ShaderProgram::LoadException("Cannot create shader program");
	}

	for (auto shader = shaders.begin(); shader != shaders.end(); ++shader) {
		glAttachShader(m_programId, shader->id());
	}


	glLinkProgram(m_programId);

	GLint linkageResult;
	glGetProgramiv(m_programId, GL_LINK_STATUS, &linkageResult);
	if (linkageResult == GL_FALSE) {
		static const uint32_t SIZE = 512;
		GLchar infoLog[SIZE];
		glGetProgramInfoLog(m_programId, SIZE, nullptr, infoLog);

		glDeleteProgram(m_programId);
		throw ShaderProgram::LoadException(std::string(infoLog));
	}
}


ShaderProgram::My_Program::~My_Program() {
	*this = nullptr;
}



uint32_t ShaderProgram::My_Program::id() const noexcept {
	return m_programId;
}

void ShaderProgram::My_Program::use() {
	glUseProgram(m_programId);
	if (glGetError() == GL_INVALID_VALUE) {
		throw ShaderProgram::UsageException("The shader program is empty");
	}
}



ShaderProgram::My_Program& ShaderProgram::My_Program::operator=(My_Program&& other) noexcept {
	this->m_programId = other.m_programId;
	other.m_programId = 0;

	return *this;
}

ShaderProgram::My_Program& ShaderProgram::My_Program::operator=(void* pointer) noexcept {
	if (pointer == nullptr) {
		glDeleteProgram(m_programId);
		m_programId = 0;
	}
	return *this;
}
