// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef _BETA_LOG_H
#define _BETA_LOG_H

#include <memory>

// spdlog/fmt gives many warnings.
#pragma warning(push, 0)
#pragma warning( disable : 26812 26812 26495 26451 6385)
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#pragma warning(pop)

namespace beta {
	class Log {
	public:
		using logger_t = std::shared_ptr<spdlog::logger>;
		enum class Level {
			CRITICAL	= spdlog::level::level_enum::critical,
			ERR			= spdlog::level::level_enum::err,
			WARN		= spdlog::level::level_enum::warn,
			INFO		= spdlog::level::level_enum::info,
			DEBUG		= spdlog::level::level_enum::debug,
			TRACE		= spdlog::level::level_enum::trace,
		};

		static Level getLevel();
		static void setLevel(Level level);
		
		template<class T>
		static void critical(const T& msg) {
			Log::instance()->critical(msg);
		}

		template<class... Args>
		static void critical(spdlog::string_view_t fmt, const Args&... args) {
			Log::instance()->critical(fmt, args...);
		}

		template<class T>
		static void error(const T& msg) {
			Log::instance()->error(msg);
		}

		template<class... Args>
		static void error(spdlog::string_view_t fmt, const Args&... args) {
			Log::instance()->error(fmt, args...);
		}

		template<class T>
		static void warn(const T& msg) {
			Log::instance()->warn(msg);
		}

		template<class... Args>
		static void warn(spdlog::string_view_t fmt, const Args&... args) {
			Log::instance()->warn(fmt, args...);
		}

		template<class T>
		static void info(const T& msg) {
			Log::instance()->info(msg);
		}

		template<class... Args>
		static void info(spdlog::string_view_t fmt, const Args&... args) {
			Log::instance()->info(fmt, args...);
		}

		template<class T>
		static void debug(const T& msg) {
			Log::instance()->debug(msg);
		}

		template<class... Args>
		static void debug(spdlog::string_view_t fmt, const Args&... args) {
			Log::instance()->debug(fmt, args...);
		}

		template<class T>
		static void trace(const T& msg) {
			Log::instance()->trace(msg);
		}

		template<class... Args>
		static void trace(spdlog::string_view_t fmt, const Args&... args) {
			Log::instance()->trace(fmt, args...);
		}


		// Forbidden operations.
		Log(const Log&) = delete;
		Log(Log&&) = delete;
		Log& operator=(const Log&) = delete;
		Log& operator=(Log&&) = delete;
	private:
		Log();

		static logger_t& instance() noexcept;

		logger_t m_logger;
	};
}

#endif // !_BETA_UTILITY_LOG_H
