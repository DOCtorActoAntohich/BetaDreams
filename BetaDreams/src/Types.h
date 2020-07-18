// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_TYPES_H_INCLUDED
#define BETA_TYPES_H_INCLUDED

#include "utility/types/RgbaColor.h"
#include "utility/types/Hasher.h"
#include "utility/types/ThreeDimensionalArray.h"

namespace beta {
	using Color = utility::types::RgbaColor;

	using HashVec3f = utility::types::SimpleHasher_glm_vec3;

	template<class Ty, size_t X_SIZE, size_t Y_SIZE, size_t Z_SIZE>
	using Array3 = utility::types::ThreeDimensionalArray<Ty, X_SIZE, Y_SIZE, Z_SIZE>;
}

#endif // !BETA_TYPES_H_INCLUDED