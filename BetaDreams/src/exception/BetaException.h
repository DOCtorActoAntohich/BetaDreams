// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BETA_EXCEPTION_H_INCLUDED
#define BETA_EXCEPTION_H_INCLUDED

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

#endif // !BETA_EXCEPTION_H_INCLUDED
