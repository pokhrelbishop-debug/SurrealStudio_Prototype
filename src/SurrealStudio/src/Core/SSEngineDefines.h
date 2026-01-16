#pragma once

#include <iostream> // for EXIT_SUCCESS & EXIT_FAILURE
#include <string>

namespace SurrealStudio {

	constexpr int ENGINE_SUCCESS = EXIT_SUCCESS;
	constexpr int ENGINE_FAILURE = EXIT_FAILURE;

	inline void ERROR(const std::string& msg) { std::cerr << "[ERROR]" << msg << std::endl; }
	inline void FATAL(const std::string& msg) { std::cerr << "[FATAL]" << msg << std::endl; }
	inline void INFO(const std::string& msg) { std::cout << "[INFO] " << msg << std::endl; }
	inline void DEBUG(const std::string& msg) { std::cout << "[DEBUG]" << msg << std::endl; }
	inline void WARNING(const std::string& msg) { std::cout << "[WARNING]" << msg << std::endl; }
}