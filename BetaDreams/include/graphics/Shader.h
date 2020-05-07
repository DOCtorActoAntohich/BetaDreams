#ifndef _BETA_GRAPHICS_SHADER_H
#define _BETA_GRAPHICS_SHADER_H

#include <string>

namespace beta::graphics {
	class Shader {
	public:
		Shader(uint32_t id);
		~Shader();

		void use();

		static Shader* load(std::string vertexFile, std::string fragmentFile);
	private:
		uint32_t m_id;
	};
}


#endif // !_BETA_GRAPHICS_SHADER_H