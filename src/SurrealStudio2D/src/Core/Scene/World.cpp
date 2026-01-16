#include "World.h"
#include <iostream>
#include <algorithm>

namespace SurrealStudio {

	namespace SurrealStudio2D {

		void World::AddWorld(std::unique_ptr<WorldData> world)
		{
			if (!world)
				return;

			// You can let the editor set this later, but for now:
			if (world->worldName.empty())
				world->worldName = "World" + std::to_string(static_cast<int>(m_Worlds.size() + 1));

			world->worldID = static_cast<int>(m_Worlds.size());

			std::cout << "[World] Added: " << world->worldName << std::endl;
			m_Worlds.push_back(std::move(world)); // move the unique_ptr in
		}

		void World::DeleteWorld(const std::string& worldName)
		{
			auto it = std::remove_if(m_Worlds.begin(), m_Worlds.end(),
				[&](const std::unique_ptr<WorldData>& w) {
					return w && w->worldName == worldName;
				});

			if (it != m_Worlds.end())
			{
				std::cout << "[World] Deleted: " << (*it)->worldName << std::endl;
				m_Worlds.erase(it, m_Worlds.end());
			}
			else
			{
				std::cout << "[World] Could not find: " << worldName << std::endl;
			}
		}

		std::string World::GetWorldName(int index) const
		{
			if (index < 0 || index >= static_cast<int>(m_Worlds.size()))
				return "Invalid";

			return m_Worlds[index]->worldName;
		}
	}

} // namespace SurrealStudio2D


