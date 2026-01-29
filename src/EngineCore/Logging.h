#pragma once

#include <string>
#include <iostream>
#include <fstream>

namespace SurrealStudio {

	namespace EngineCore {

		class Logging
		{
		public:

			enum class LogLevel
			{
				Debug,
				Info,
				Warning,
				Error,
				Fatal
			};

			inline static void Log(LogLevel level,
				const std::string& msg,
				const char* file,
				int line,
				const char* func)
			{
				std::ostream& out =
					(level == LogLevel::Error || level == LogLevel::Fatal)
					? std::cerr : std::cout;
				const char* lvl =
					(level == LogLevel::Debug) ? "DEBUG" :
					(level == LogLevel::Info) ? "INFO" :
					(level == LogLevel::Warning) ? "WARNING" :
					(level == LogLevel::Error) ? "ERROR" : "FATAL";
				out << "[" << lvl << "] " << msg << "\n"
					<< "  FILE: " << file << "\n"
					<< "  LINE: " << line << "\n"
					<< "  FUNC: " << func << "\n\n";
			}

#define SS_LOG(lvl, msg) \
	do { \
		SurrealStudio::EngineCore::Logging::Log( \
			lvl, msg, __FILE__, __LINE__, __FUNCTION__ \
		); \
	} while(0)

#define SS_DEBUG_ENABLE  true  // For logging debug messages

#if SS_DEBUG_ENABLE
			
#define SS_DEBUG(msg)	SS_LOG(Logging::LogLevel::Debug, msg)
#define SS_INFO(msg)    SS_LOG(Logging::LogLevel::Info,  msg)
#define SS_WARNING(msg) SS_LOG(Logging::LogLevel::Warning, msg)
#define SS_ERROR(msg)   SS_LOG(Logging::LogLevel::Error, msg)
#define SS_FATAL_ERROR(msg) SS_LOG(Logging::LogLevel::Fatal, msg)

#endif
		};
	}
}