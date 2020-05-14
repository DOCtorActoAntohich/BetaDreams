// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef _BETA_GRAPHICS_SHADER_H
#define _BETA_GRAPHICS_SHADER_H

#include <string>
#include <filesystem>
#include <GL/glew.h>

#include "exception/BetaException.h"

namespace beta::graphics {
	enum class ShaderType {
		VERTEX = GL_VERTEX_SHADER,
		FRAGMENT = GL_FRAGMENT_SHADER,
		GEOMETRY = GL_GEOMETRY_SHADER,
		COMPUTE = GL_COMPUTE_SHADER
	};



	class ShaderProgram {
	public:
		class LoadException;

		ShaderProgram() noexcept;
		ShaderProgram(std::string shaderName);
		ShaderProgram(ShaderProgram&& other) noexcept;
		ShaderProgram(const ShaderProgram& other) = delete;

		~ShaderProgram();

		void load(const std::string& name);

		void use();
		
		ShaderProgram& operator=(ShaderProgram& other) noexcept;
		ShaderProgram& operator=(ShaderProgram&& other) noexcept;

	private:
		static std::string getFileType(const ShaderType type);
		static std::filesystem::path getShaderPath(const std::string& name, const ShaderType type);

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

		void load(const std::filesystem::path& vertexFile, const std::filesystem::path& fragmentFile);
	};



	class ShaderProgram::LoadException : public BetaException {
	public:
		LoadException(std::string message);
	};


	class ShaderProgram::My_Shader {
	public:
		My_Shader(const std::filesystem::path& path, const ShaderType shaderType);
		~My_Shader();

		uint32_t id() const;
	private:
		uint32_t m_shaderId;

		std::string readCode(const std::filesystem::path& path) const;
		void compile(const std::string& code, const ShaderType shaderType);
	};
	


	class ShaderProgramException : public BetaException {
	public:
		ShaderProgramException(std::string message) : BetaException(message) {}
	};
	
}


#endif // !_BETA_GRAPHICS_SHADER_H