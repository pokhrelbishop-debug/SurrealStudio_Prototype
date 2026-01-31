#include "Engine.h"
#include "Time.h"
#include "Logging.h"

#include "../src/SurrealStudio3D/src/Core/Scene/World3D.h"
#include "../src/SurrealRenderer/src/RendererCore/Renderer.h"

namespace SurrealStudio::EngineCore {

    void Engine::Init()
    {
        if (m_State != EngineState::Uninitialized)
            return;

        m_State = EngineState::Initialized;

        Time::Init();

        m_State = EngineState::Running;
        SS_INFO("Surreal Studio Engine initialized successfully.");
    }

    void Engine::Update()
    {
        if (m_State != EngineState::Running)
            return;

        Time::Update();
        //float dt = Time::GetDeltaTime();

        //m_World.UpdateAllObjects(dt); 
        //m_Renderer.RenderAll(m_World);

        //static int frameCounter = 0;
        //frameCounter++;

        //if (frameCounter % 60 == 0)
        //    SS_INFO("Surreal Studio Engine updated.");
    }

    void Engine::Shutdown()
    {
        if (m_State == EngineState::ShuttingDown || m_State == EngineState::Uninitialized)
            return;

        m_State = EngineState::ShuttingDown;
		SS_INFO("Shutting down Surreal Studio Engine...");

        // Shutdown subsystems here (later)
    }

}
