#pragma once

#include "World3D.h"

#include <string>
#include <vector>
#include <memory>

namespace SurrealStudio {

	namespace SurrealStudio3D {

		namespace SceneSystem3D {

			struct SubsceneData
			{
				std::string subsceneName;
				std::vector<std::unique_ptr<World>> worlds;
			};

			class Subscene
			{
			public:

				Subscene() = default;
				~Subscene() = default;

				bool AddSubscene() noexcept;
				bool DeleteSubscene(SubsceneData* data) noexcept;

			private:

				//SubsceneData m_SubsceneData;
				std::vector<std::unique_ptr<SubsceneData>> m_Subscenes; // Just the data for Subscenes
				
				std::unique_ptr<World> m_Worlds;
			};
		}
	}
}