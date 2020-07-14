// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Hasher.h"

using namespace beta::utility::types;

size_t SimpleHasher_glm_vec3::operator()(const glm::vec3& vector) const noexcept {
	static auto hash = std::hash<float_t>{};
	return hash(vector.x) ^ hash(vector.y) ^ hash(vector.z);
}