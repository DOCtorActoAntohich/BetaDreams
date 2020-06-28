#ifndef BETA_UTILITY_TYPES_H_INCLUDED
#define BETA_UTILITY_TYPES_H_INCLUDED

#include <glm/vec3.hpp>

namespace beta {
	struct HashVec3f {
		size_t operator()(const glm::vec3& vector) const {
			static auto hash = std::hash<float_t>{};
			return hash(vector.x) ^ hash(vector.y) ^ hash(vector.z);
		}
	};
}

#endif // !BETA_UTILITY_TYPES_H_INCLUDED