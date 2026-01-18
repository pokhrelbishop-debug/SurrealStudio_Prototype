#include "Engine.h"
#include "Time.h"

namespace SurrealStudio {

	namespace EngineCore
	{
		void Engine::Init()
		{
			// Initialization code here
			Time::Init();
		}

		void Engine::Shutdown()
		{
			// Shutdown code here
		}

		void Engine::Update()
		{
			// One frame update code here
			Time::Update();
		}
	}
}