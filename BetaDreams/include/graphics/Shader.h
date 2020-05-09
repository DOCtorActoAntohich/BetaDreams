#ifndef _BETA_GRAPHICS_SHADER_H
#define _BETA_GRAPHICS_SHADER_H

#include <string>
#include <GL/glew.h>

#include "exception/BetaException.h"

namespace beta::graphics {
	class Shader {
	public:
		class LoadException;

		Shader() noexcept;
		Shader(std::string shaderName);
		Shader(Shader&& other) noexcept;
		Shader(const Shader& other) = delete;

		~Shader();

		void load(std::string shaderName);

		void use();
		
		Shader& operator=(Shader& other) noexcept;
		Shader& operator=(Shader&& other) noexcept;

	private:
		// RAII wrapper on OpenGL shader program;
		class My_Shader;

		class My_Program {
		public:
			My_Program() noexcept;
			My_Program(Shader::My_Program& other) = delete;
			My_Program(Shader::My_Program&& other) noexcept;
			My_Program(const std::initializer_list<Shader::My_Shader> shaders);
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

		void load(std::string vertexFile, std::string fragmentFile);
	};


	class Shader::LoadException : public BetaException {
	public:
		LoadException(std::string message);
	};


	class Shader::My_Shader {
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