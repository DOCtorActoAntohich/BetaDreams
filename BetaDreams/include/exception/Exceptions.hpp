#ifndef _BETA_EXCEPTIONS_H
#define _BETA_EXCEPTIONS_H

#include "exception/BetaException.h"

namespace beta {
	/**
	 * An exception that should occur if something failed to initialize.
	 */
	class InitializationException : public BetaException {
	public:
		InitializationException(std::string message) : BetaException(message) {}
	};



	class PngLoadException : public BetaException {
	public:
		PngLoadException(std::string message) : BetaException(message) {}
	};
}

#endif // !_BETA_EXCEPTIONS_H
