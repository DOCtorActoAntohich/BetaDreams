#include "graphics/Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "exception/Exceptions.hpp"
#include "Helper.h"

using namespace beta::graphics;




Shader::LoadException::LoadException(std::string message) : BetaException(message)
{	}





Shader::Shader() noexcept {}

Shader::Shader(std::string shaderName) {
	this->load(shaderName);
}

Shader::Shader(Shader&& other) noexcept {
	*this = other;
}

Shader::~Shader() {}



void Shader::use() {
	m_shaderProgram.use();
}



void Shader::load(std::string shaderName) {
	static const std::string PATH = "resource/shader/";
	static const std::string GLSLV = ".glslv";
	static const std::string GLSLF = ".glslf";

	std::string vertexFilename   = PATH + shaderName + GLSLV;
	std::string fragmentFilename = PATH + shaderName + GLSLF;

	try {
		this->load(vertexFilename, fragmentFilename);
	}
	catch (std::istream::failure) {
		throw Shader::LoadException("Unable to read shader file(s) with name: " + shaderName);
	}
}


void Shader::load(std::string vertexFile, std::string fragmentFile) {
	Shader::My_Shader vertexShader(vertexFile, GL_VERTEX_SHADER);
	Shader::My_Shader fragmentShader(fragmentFile, GL_FRAGMENT_SHADER);

	m_shaderProgram = { vertexShader, fragmentShader };
}



Shader& Shader::operator=(Shader& other) noexcept {
	*this = std::move(other);
	return *this;
}

Shader& Shader::operator=(Shader&& other) noexcept {
	this->m_shaderProgram = other.m_shaderProgram;
	other.m_shaderProgram = nullptr;

	return *this;
}






Shader::My_Shader::My_Shader(const std::string& path, const GLenum shaderType) {
	std::string code = this->readCode(path);
	this->compile(code, shaderType);
}

Shader::My_Shader::~My_Shader() {
	glDeleteShader(m_shaderId);
}



uint32_t Shader::My_Shader::id() const {
	return m_shaderId;
}


std::string Shader::My_Shader::readCode(const std::string& path) const {
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


void Shader::My_Shader::compile(const std::string& code, const GLenum& shaderType) {
	static const uint32_t AMOUNT = 1;

	m_shaderId = glCreateShader(shaderType);
	if (glGetError() == GL_INVALID_ENUM) {
		throw Shader::LoadException("Invalid shader type provided");
	}
	else if (m_shaderId == 0) {
		throw Shader::LoadException("Error while creating shader");
	}

	const GLchar* shaderCode_cstr = code.c_str();
	glShaderSource(m_shaderId, AMOUNT, &shaderCode_cstr, nullptr);
	glCompileShader(m_shaderId);

	GLint compilationResult;
	glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &compilationResult);
	if (compilationResult == GL_FALSE) {
		glDeleteShader(m_shaderId);
		std::string message = Helper::getGlShaderInfoLog(m_shaderId);
		throw Shader::LoadException(message);
	}
}





Shader::My_Program::My_Program() noexcept {
	m_programId = 0;
}

Shader::My_Program::My_Program(Shader::My_Program&& other) noexcept {
	*this = other;
}


Shader::My_Program::My_Program(const std::initializer_list<Shader::My_Shader> shaders) {
	m_programId = glCreateProgram();
	if (m_programId == 0) {
		throw Shader::LoadException("Cannot create shader program");
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
		throw Shader::LoadException(std::string(infoLog));
	}
}


Shader::My_Program::~My_Program() {
	*this = nullptr;
}



uint32_t Shader::My_Program::id() const noexcept {
	return m_programId;
}

void Shader::My_Program::use() {
	glUseProgram(m_programId);
	if (glGetError() == GL_INVALID_VALUE) {
		throw ShaderProgramException("The shader program is empty");
	}
}



Shader::My_Program& Shader::My_Program::operator=(My_Program& other) noexcept {
	*this = std::move(other);
	return *this;
}

Shader::My_Program& Shader::My_Program::operator=(My_Program&& other) noexcept {
	this->m_programId = other.m_programId;
	other.m_programId = 0;

	return *this;
}

Shader::My_Program& Shader::My_Program::operator=(void* pointer) noexcept {
	if (pointer == nullptr) {
		glDeleteProgram(m_programId);
		m_programId = 0;
	}
	return *this;
}
