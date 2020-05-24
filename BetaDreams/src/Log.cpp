// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Log.h"

#include "Helper.h"

using namespace beta;



Log::Level Log::getLevel() {
	return static_cast<Log::Level>(Log::instance()->level());
}

void Log::setLevel(Log::Level level) {
	Log::instance()->set_level(static_cast<spdlog::level::level_enum>(level));
}



Log::Log() {
	const std::filesystem::path LOGS = "logs";
	const std::filesystem::path FORMAT = ".log";
	std::filesystem::path filename = LOGS / Helper::getCurrentTime();
	filename += FORMAT;

	// Format is:
	// [Jan 13 2020 00:13:37 pm] (debug): message.
	spdlog::set_pattern("[%b %d %Y %r] (%l): %v");
	
	spdlog::sinks_init_list sinks = {
		std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename.string(), true),
		std::make_shared<spdlog::sinks::stdout_sink_mt>()
	};

	m_logger = std::make_shared<spdlog::logger>("Beta::Logger", sinks.begin(), sinks.end());

#if defined(_DEBUG)
	m_logger->set_level(spdlog::level::level_enum::debug);
#elif defined(NDEBUG)
	m_logger->set_level(spdlog::level::level_enum::info);
#endif
}



Log::logger_t& Log::instance() noexcept {
	static Log logger;
	return logger.m_logger;
}
