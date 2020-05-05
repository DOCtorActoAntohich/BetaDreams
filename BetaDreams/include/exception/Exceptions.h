#ifndef _BETA_EXCEPTIONS_H
#define _BETA_EXCEPTIONS_H

#include "exception/BetaException.h"

namespace beta {
	class InitializationException : public BetaException {
	public:
		InitializationException(std::string message) : BetaException(message) {}
	};
}


#endif // _BETA_EXCEPTIONS_H
