#pragma once

#include "EngineState.h"

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
			
		};
	}
}