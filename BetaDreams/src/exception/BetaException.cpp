#include "exception/BetaException.h"

using namespace beta;

BetaException::BetaException(std::string message) {
	m_message = message;
}

const char* BetaException::what() const noexcept {
	return m_message.c_str();
}