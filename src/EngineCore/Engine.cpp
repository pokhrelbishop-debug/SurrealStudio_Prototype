#include "Engine.h"
#include "Time.h"

namespace SurrealStudio::EngineCore {

    void Engine::Init()
    {
        if (m_State != EngineState::Uninitialized)
            return;

        m_State = EngineState::Initialized;

        Time::Init();

        m_State = EngineState::Running;
    }

    void Engine::Update()
    {
        if (m_State != EngineState::Running)
            return;

        Time::Update();
    }

    void Engine::Shutdown()
    {
        if (m_State == EngineState::ShuttingDown ||
            m_State == EngineState::Uninitialized)
            return;

        m_State = EngineState::ShuttingDown;

        // Shutdown subsystems here (later)
    }

}
