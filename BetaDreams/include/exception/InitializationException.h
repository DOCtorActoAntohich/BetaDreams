#ifndef _BETA_INITIALIZATION_EXCEPTION_H
#define _BETA_INITIALIZATION_EXCEPTION_H

#include "exception/Exception.h"

namespace beta {
	class InitializationException : public Exception {
	public:
		InitializationException(std::string message);
	};
}

#endif // _BETA_INITIALIZATION_EXCEPTION_H
