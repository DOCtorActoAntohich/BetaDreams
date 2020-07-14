// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_TYPES_H_INCLUDED
#define BETA_TYPES_H_INCLUDED

#include "utility/types/RgbaColor.h"
#include "utility/types/Hasher.h"

namespace beta {
	using Color = utility::types::RgbaColor;

	using HashVec3f = utility::types::SimpleHasher_glm_vec3;
}

#endif // !BETA_TYPES_H_INCLUDED