// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_GRAPHICS_SHADER_H_INCLUDED
#define BETA_GRAPHICS_SHADER_H_INCLUDED

#include <string>
#include <filesystem>

#include <GL/glew.h>
#include <glm/glm.hpp>

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
		class UsageException;

		ShaderProgram() noexcept;
		ShaderProgram(std::string shaderName);
		ShaderProgram(ShaderProgram&& other) noexcept;
		ShaderProgram(const ShaderProgram& copy) = delete;

		~ShaderProgram();

		void load(const std::string& name);

		void use();

		void uniformMatrix(const std::string& name, const glm::mat4& matrix);
		
		ShaderProgram& operator=(ShaderProgram& copy) = delete;
		ShaderProgram& operator=(ShaderProgram&& other) noexcept;

	private:
		static std::string getFileType(const ShaderType type);
		static std::filesystem::path getShaderPath(const std::string& name, const ShaderType type);

		// RAII wrapper on OpenGL shader program;
		class My_Shader;

		class My_Program {
		public:
			My_Program() noexcept;
			My_Program(const ShaderProgram::My_Program& copy) = delete;
			My_Program(ShaderProgram::My_Program&& other) noexcept;
			My_Program(std::initializer_list<ShaderProgram::My_Shader> shaders);
			~My_Program();

			uint32_t id() const noexcept;

			void use();

			My_Program& operator=(My_Program& copy) = delete;
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
	


	class ShaderProgram::UsageException : public BetaException {
	public:
		UsageException(std::string message);
	};
}


#endif // !BETA_GRAPHICS_SHADER_H_INCLUDED
