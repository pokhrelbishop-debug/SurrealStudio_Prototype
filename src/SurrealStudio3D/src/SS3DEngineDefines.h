#pragma once

#include <iostream>
#include <string>
#include <fstream>

namespace SurrealStudio {

    namespace SurrealStudio3D {

        constexpr int ENGINE_FAILURE = EXIT_FAILURE;
        constexpr int ENGINE_SUCCESS = EXIT_SUCCESS;

        enum class LogLevel {
            Debug,
            Info,
            Warning,
            Error,
            Fatal
        };

        inline void Log(LogLevel level,
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

#define SS3D_LOG(lvl, msg) \
    do { \
        SurrealStudio::SurrealStudio3D::Log( \
            lvl, msg, __FILE__, __LINE__, __FUNCTION__ \
        ); \
    } while(0)

#define GLFW_INCLUDE_NONE // to be used in rendering, does not affect UI or core stuff I think

#define SS_DEBUG_ENABLE   true   // For debug using ImGui in some debug panels not really used for Debug/Release builds

#if SS_DEBUG_ENABLE

    #define SS3D_DEBUG(msg)   SS3D_LOG(SurrealStudio::SurrealStudio3D::LogLevel::Debug,   msg)
    #define SS3D_INFO(msg)    SS3D_LOG(SurrealStudio::SurrealStudio3D::LogLevel::Info,    msg)
    #define SS3D_WARNING(msg) SS3D_LOG(SurrealStudio::SurrealStudio3D::LogLevel::Warning, msg)
    #define SS3D_ERROR(msg)   SS3D_LOG(SurrealStudio::SurrealStudio3D::LogLevel::Error,   msg)
    #define SS3D_FATAL(msg)   SS3D_LOG(SurrealStudio::SurrealStudio3D::LogLevel::Fatal,   msg)

#endif

    } // namespace SurrealStudio3D
} // namespace SurrealStudio
