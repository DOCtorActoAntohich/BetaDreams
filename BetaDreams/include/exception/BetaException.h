#ifndef _BETA_EXCEPTION_H
#define _BETA_EXCEPTION_H

#include <exception>
#include <string>

namespace beta {
	/**
	 * A base class for all Beta Dreams exceptions.
	 */
	class BetaException : public std::exception {
	public:
		/**
		 * Constructs an exception object with given message.
		 * 
		 * \param message A description of exception.
		 */
		BetaException(std::string message);

		/**
		 * Gets the description of an exception.
		 * 
		 * \return A C-style string describing an exception.
		 */
		const char* what() const noexcept;
	private:
		std::string m_message;
	};
}

#endif // !_BETA_EXCEPTION_H