// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Air.h"

using namespace beta::block;

Air::Air()
{	}



const std::string& Air::ingameId() const {
	static const std::string id = "beta_air";
	return id;
}

bool Air::isTransparent() const {
	return true;
}