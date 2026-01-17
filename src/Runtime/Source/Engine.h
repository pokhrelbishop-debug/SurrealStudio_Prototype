#pragma once

namespace SurrealStudio {

	namespace Runtime
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