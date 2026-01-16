#include "World3D.h"

#include "../src/SurrealStudio3D/src/Core/ECS/Object3D.h"

#include <string>
#include <vector>
#include <memory>

namespace SurrealStudio {

	namespace SurrealStudio3D {

		namespace SceneSystem3D {

			bool World::AddWorld() noexcept
			{
				auto newWorld = std::make_unique<WorldData>();
				newWorld->worldName = "New World";

				m_Worlds.push_back(std::move(newWorld));
				return true;
			}

			bool World::DeleteWorld(WorldData* data) noexcept
			{
				for (auto it = m_Worlds.begin(); it != m_Worlds.end(); it++)
				{
					if (it->get() == data)
					{
						m_Worlds.erase(it);
						return true;
					}
				}
				return false;
			}

			bool World::DeleteAllWorlds() noexcept
			{
				if (m_Worlds.empty())
					return false;

				m_Worlds.clear();
				return true;
			}
		}
	}
}