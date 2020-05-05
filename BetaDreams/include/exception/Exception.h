#ifndef _BETA_EXCEPTION_H
#define _BETA_EXCEPTION_H

#include <exception>
#include <string>

namespace beta {
	class Exception : public std::exception {
	public:
		Exception(std::string message);

		const char* what() const noexcept;
	private:
		std::string m_message;
	};
}

#endif // _BETA_EXCEPTION_H
