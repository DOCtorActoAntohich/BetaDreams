#include "graphics/Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Helper.h"

using namespace beta::graphics;

Shader::Shader(uint32_t id) {
	m_id = id;
}

Shader::~Shader() {
	glDeleteProgram(m_id);
}



void Shader::use() {
	glUseProgram(m_id);
}



Shader* Shader::load(std::string vertexFilename, std::string fragmentFilename) {
	std::string vertexCode;
	std::string fragmentCode;
	
	try {
		std::ifstream vertexShaderFile(vertexFilename);
		std::ifstream fragmentShaderFile(fragmentFilename);
		
		vertexShaderFile.exceptions(std::ifstream::badbit);
		fragmentShaderFile.exceptions(std::ifstream::badbit);

		std::stringstream vertexShaderStream;
		std::stringstream fragmentShaderStream;

		vertexShaderStream   << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexCode   = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	}
	catch (std::ifstream::failure) {
		std::cerr << "ERROR: Unable to read shader file." << std::endl;
		return nullptr;
	}

	auto compileShader = [](int32_t shaderType, std::string shaderCode) -> GLuint {
		static const uint32_t AMOUNT = 1;
		GLuint shaderId = glCreateShader(shaderType);
		const GLchar* shaderCode_c = shaderCode.c_str();
		glShaderSource(shaderId, AMOUNT, &shaderCode_c, nullptr);
		glCompileShader(shaderId);

		GLint compilationResult;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationResult);
		if (compilationResult == GL_FALSE) {
			throw Helper::getGlShaderInfoLog(shaderId);
		}
		return shaderId;
	};


	GLuint vertexShader, fragmentShader;

	try {
		vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode);
		fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode);
	}
	catch (std::string errorMessage) {
		std::cerr << errorMessage << std::endl;
		return nullptr;
	}


	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShader);
	glAttachShader(programId, fragmentShader);
	glLinkProgram(programId);

	GLint linkageResult;
	glGetProgramiv(programId, GL_LINK_STATUS, &linkageResult);
	if (linkageResult == GL_FALSE) {
		std::string message = Helper::getGlProgramInfoLog(programId);
		std::cerr << message << std::endl;

		glDeleteProgram(programId);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		
		return nullptr;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return new Shader(programId);
}
