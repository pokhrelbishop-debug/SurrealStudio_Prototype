#pragma once

namespace SurrealStudio {

	namespace EngineCore {

		enum class EngineState
		{
			Uninitialized,
			Initialized,
			Running,
			ShuttingDown
		};
	}
}