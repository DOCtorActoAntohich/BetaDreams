// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef _BETA_GRAPHICS_SHADER_H
#define _BETA_GRAPHICS_SHADER_H

#include <string>
#include <GL/glew.h>

#include "exception/BetaException.h"

namespace beta::graphics {
	class ShaderProgram {
	public:
		class LoadException;

		ShaderProgram() noexcept;
		ShaderProgram(std::string shaderName);
		ShaderProgram(ShaderProgram&& other) noexcept;
		ShaderProgram(const ShaderProgram& other) = delete;

		~ShaderProgram();

		void load(const std::string& shaderName);

		void use();
		
		ShaderProgram& operator=(ShaderProgram& other) noexcept;
		ShaderProgram& operator=(ShaderProgram&& other) noexcept;

	private:
		// RAII wrapper on OpenGL shader program;
		class My_Shader;

		class My_Program {
		public:
			My_Program() noexcept;
			My_Program(ShaderProgram::My_Program& other) = delete;
			My_Program(ShaderProgram::My_Program&& other) noexcept;
			My_Program(std::initializer_list<ShaderProgram::My_Shader> shaders);
			~My_Program();

			uint32_t id() const noexcept;

			void use();

			My_Program& operator=(My_Program& other) noexcept;
			My_Program& operator=(My_Program&& other) noexcept;
			My_Program& operator=(void* pointer) noexcept;
		private:
			uint32_t m_programId;
		};


		My_Program m_shaderProgram;

		void load(const std::string& vertexFile, const std::string& fragmentFile);
	};


	class ShaderProgram::LoadException : public BetaException {
	public:
		LoadException(std::string message);
	};


	class ShaderProgram::My_Shader {
	public:
		My_Shader(const std::string& path, const GLenum shaderType);
		~My_Shader();

		uint32_t id() const;
	private:
		uint32_t m_shaderId;

		std::string readCode(const std::string& path) const;
		void compile(const std::string& code, const GLenum& shaderType);
	};
	


	class ShaderProgramException : public BetaException {
	public:
		ShaderProgramException(std::string message) : BetaException(message) {}
	};
	
}


#endif // !_BETA_GRAPHICS_SHADER_H