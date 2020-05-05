#include "exception/InitializationException.h"

using namespace beta;

InitializationException::InitializationException(std::string message)
	: Exception(message)
{	}
