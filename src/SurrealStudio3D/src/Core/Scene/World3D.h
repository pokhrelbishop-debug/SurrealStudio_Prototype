#pragma once

#include "../src/SurrealStudio3D/src/Core/ECS/Object3D.h"

#include <string>
#include <vector>
#include <memory>

namespace SurrealStudio {

	namespace SurrealStudio3D {

		namespace SceneSystem3D {

			struct WorldData
			{
				std::string worldName;
				std::vector<std::unique_ptr<ECS::Object3D_ObjectData>> objects;
			};

			class World
			{
			public:

				World() = default;
				~World() = default;

				bool AddWorld() noexcept;
				bool DeleteWorld(WorldData* data) noexcept;

				bool DeleteAllWorlds() noexcept;

				WorldData GetAllWorlds() const noexcept { return worldData; }

			private:

				WorldData worldData;
				std::vector<std::unique_ptr<WorldData>> m_Worlds;
			};
		}
	}
}