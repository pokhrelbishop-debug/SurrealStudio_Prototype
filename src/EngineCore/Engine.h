#pragma once

#include "EngineState.h"

#include "../src/SurrealStudio3D/src/Core/Scene/World3D.h"
#include "../src/SurrealRenderer/src/RendererCore/Renderer.h"

namespace SurrealStudio {

	namespace EngineCore
	{
		class Engine
		{
		public:

			void Init();
			void Shutdown();
			void Update(); // one frame only

			EngineState GetState() const noexcept { return m_State; }

		private:

			EngineState m_State = EngineState::Uninitialized;
			SurrealStudio3D::SceneSystem3D::World m_World;
			SurrealRenderer::Renderer m_Renderer; 
		};
	}
}