#pragma once

#include <iostream>

namespace SurrealStudio {

	namespace EngineCore {

		constexpr int ENGINE_SUCCESS = EXIT_SUCCESS;
		constexpr int ENGINE_FAILURE = EXIT_FAILURE;

        // Engine level constants/defines etc

        constexpr uint32_t SS_MAX_OBJECTS_PER_WORLD = 250;
        constexpr uint32_t SS_MAX_COMPONENTS_PER_WORLD = 10000;
        constexpr uint32_t SS_MAX_FPS_ENGINE = 144;

        constexpr float SS_DEFAULT_ZOOM = 100.0f;
        constexpr float SS_MAX_ZOOM = 200.0f;
        constexpr float SS_MIN_ZOOM = 10.0f;

        constexpr uint32_t SS_MAX_COMPONENTS_PER_WORLD = 10000000;

	} // namespace EngineCore
}