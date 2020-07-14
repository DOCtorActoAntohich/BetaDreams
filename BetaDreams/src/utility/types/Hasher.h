// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_UTILITY_TYPES_HASHER_H_INCLUDED
#define BETA_UTILITY_TYPES_HASHER_H_INCLUDED

#include <glm/vec3.hpp>

namespace beta::utility::types {
	struct SimpleHasher_glm_vec3 {
		size_t operator()(const glm::vec3& vector) const noexcept;
	};
}

#endif // !BETA_UTILITY_TYPES_HASHER_H_INCLUDED