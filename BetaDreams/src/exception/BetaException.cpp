// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "BetaException.h"

using namespace beta;

BetaException::BetaException(std::string message)
	: m_message(message)
{	}

const char* BetaException::what() const noexcept {
	return m_message.c_str();
}