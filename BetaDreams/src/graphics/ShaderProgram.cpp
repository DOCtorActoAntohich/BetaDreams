// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "graphics/ShaderProgram.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "exception/Exceptions.hpp"
#include "Helper.h"

using namespace beta::graphics;




ShaderProgram::LoadException::LoadException(std::string message) : BetaException(message)
{	}





ShaderProgram::ShaderProgram() noexcept {}

ShaderProgram::ShaderProgram(std::string shaderName) {
	this->load(shaderName);
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept {
	*this = other;
}

ShaderProgram::~ShaderProgram() {}



void ShaderProgram::use() {
	m_shaderProgram.use();
}



void ShaderProgram::load(const std::string& shaderName) {
	static const std::string PATH = "resource/shader/";
	static const std::string GLSLV = ".glslv";
	static const std::string GLSLF = ".glslf";

	std::string vertexFilename   = PATH + shaderName + GLSLV;
	std::string fragmentFilename = PATH + shaderName + GLSLF;

	try {
		this->load(vertexFilename, fragmentFilename);
	}
	catch (std::istream::failure&) {
		throw ShaderProgram::LoadException("Unable to read shader file(s) with name: " + shaderName);
	}
}


void ShaderProgram::load(const std::string& vertexFile, const std::string& fragmentFile) {
	ShaderProgram::My_Shader vertexShader(vertexFile, GL_VERTEX_SHADER);
	ShaderProgram::My_Shader fragmentShader(fragmentFile, GL_FRAGMENT_SHADER);

	m_shaderProgram = { vertexShader, fragmentShader };
}



ShaderProgram& ShaderProgram::operator=(ShaderProgram& other) noexcept {
	*this = std::move(other);
	return *this;
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept {
	this->m_shaderProgram = other.m_shaderProgram;
	other.m_shaderProgram = nullptr;

	return *this;
}






ShaderProgram::My_Shader::My_Shader(const std::string& path, const GLenum shaderType) {
	std::string code = this->readCode(path);
	this->compile(code, shaderType);
}

ShaderProgram::My_Shader::~My_Shader() {
	glDeleteShader(m_shaderId);
}



uint32_t ShaderProgram::My_Shader::id() const {
	return m_shaderId;
}


std::string ShaderProgram::My_Shader::readCode(const std::string& path) const {
	std::ifstream programFile(path);
	if (!programFile.is_open()) {
		throw std::ifstream::failure("Cannot open file");
	}
	programFile.exceptions(std::ifstream::badbit);

	std::stringstream codeStream;
	codeStream << programFile.rdbuf();

	programFile.close();

	return codeStream.str();
}


void ShaderProgram::My_Shader::compile(const std::string& code, const GLenum& shaderType) {
	static const uint32_t AMOUNT = 1;

	m_shaderId = glCreateShader(shaderType);
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
	*this = other;
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
		throw ShaderProgramException("The shader program is empty");
	}
}



ShaderProgram::My_Program& ShaderProgram::My_Program::operator=(My_Program& other) noexcept {
	*this = std::move(other);
	return *this;
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
