#pragma once
#include <string>

namespace SurrealStudio::EngineCore {

    struct EngineMainConfiguration
    {
        int WindowWidth = 1280;
        int WindowHeight = 720;
        std::string WindowTitle = "Surreal Studio Engine";
        bool VSyncEnabled = true;
        bool FullscreenEnabled = false;
    };

    [[nodiscard]]
    inline EngineMainConfiguration GetDefaultEngineMainConfiguration() noexcept
    {
        return EngineMainConfiguration{};
    }
}
