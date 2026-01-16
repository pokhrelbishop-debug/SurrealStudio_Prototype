#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <cstdint>

namespace SurrealStudio {

    namespace SurrealStudio2D {

        // Engine status codes
        constexpr int ENGINE_FAILURE = EXIT_FAILURE;
        constexpr int ENGINE_SUCCESS = EXIT_SUCCESS;

        // Logging helpers
        inline void SS2DERROR(const std::string& msg) { std::cerr << "[ERROR] " << msg << std::endl; }
        inline void SS2DFATAL(const std::string& msg) { std::cerr << "[FATAL] " << msg << std::endl; }
        inline void SS2DINFO(const std::string& msg) { std::cout << "[INFO] " << msg << std::endl; }
        inline void SS2DDEBUG(const std::string& msg) { std::cout << "[DEBUG] " << msg << std::endl; }
        inline void SS2DWARNING(const std::string& msg) { std::cout << "[WARNING] " << msg << std::endl; }

        // -------------------------
        // Primitive type aliases
        // -------------------------

        // Signed integers
        using SSInteger8 = int8_t;
        using SSInteger16 = int16_t;
        using SSInteger32 = int32_t;
        using SSInteger64 = int64_t;
        using SSInteger = int; // platform-dependent

        // Unsigned integers
        using SSPositiveInteger8 = uint8_t;
        using SSPositiveInteger16 = uint16_t;
        using SSPositiveInteger32 = uint32_t;
        using SSPositiveInteger64 = uint64_t;
        using SSPositiveInteger = unsigned int; // platform-dependent

        // Floating points
        using SSFloat = float;
        using SSDouble = double;

        // Boolean & char
        using SSBoolean = bool;
        using SS2DCharacter = char;

        // -------------------------
        // Pointer & smart pointer aliases
        // -------------------------
        template<typename T>
        using SSPtr = T*;

        template<typename T>
        using SSUniquePtr = std::unique_ptr<T>;

        template<typename T>
        using SSSharedPtr = std::shared_ptr<T>;

        // -------------------------
        // Const / reference helpers
        // -------------------------
        template<typename T>
        using SSConstant = const T;

        using SSConstantCharPtr = const char*;  // pointer to const char

        template<typename T>
        using SSConstantPtr = const T*;

        template<typename T>
        using SSConstRef = const T&;

        template<typename T>
        using SSRef = T&;

    } // namespace SurrealStudio2D
} // namespace SurrealStudio
