#pragma once

namespace SurrealStudio {

	namespace EngineCore
	{
		class Engine
		{
		public:

			void Init();
			void Shutdown();
			void Update(); // one frame only
		};
	}
}