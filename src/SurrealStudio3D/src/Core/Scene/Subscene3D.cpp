#include "Subscene3D.h"
#include "World3D.h"

#include <string>
#include <vector>
#include <memory>

namespace SurrealStudio {

	namespace SurrealStudio3D {

		namespace SceneSystem3D {

			bool Subscene::AddSubscene() noexcept
			{
				auto newSubscene = std::make_unique<SubsceneData>();
				newSubscene->subsceneName = "New Subscene";

				m_Subscenes.push_back(std::move(newSubscene));
				return true;
			}


			bool Subscene::DeleteSubscene(SubsceneData* data) noexcept
			{
				if (m_Subscenes.empty())
					return false;

				for (auto it = m_Subscenes.begin(); it != m_Subscenes.end(); it++)
				{
					if (it->get() == data)
					{
						m_Subscenes.erase(it);
						// Ensure m_Worlds exists before calling into it
						if (m_Worlds)
							m_Worlds->DeleteAllWorlds();  // Because if a subscene is deleted, all the Worlds in that Subscene will also get deleted as well
						return true;  // Success
					}
				}

				return false;  // Fail
			}

			bool Subscene::GetCurrentSubscene() noexcept
			{
				// If there are no subscenes, clear the world manager and return false
				if (m_Subscenes.empty())
				{
					m_Worlds.reset();
					return false;
				}

				// Choose the first subscene as the "current" subscene for now.
				// (This function can be extended later to support explicit selection.)
				SubsceneData* current = m_Subscenes.front().get();
				if (!current)
				{
					m_Worlds.reset();
					return false;
				}

				// Ensure the Subscene has at least one World object so editor/systems have something to operate on.
				if (current->worlds.empty())
				{
					current->worlds.push_back(std::make_unique<World>());
				}

				// Ensure the internal World manager exists and reflects the current subscene's world count.
				if (!m_Worlds)
					m_Worlds = std::make_unique<World>();

				// Reset m_Worlds to a clean state, then create placeholder worlds to match the subscene's worlds.
				// Note: we avoid moving ownership out of SubsceneData::worlds to keep ownership local to the subscene.
				m_Worlds->DeleteAllWorlds();
				for (size_t i = 0; i < current->worlds.size(); ++i)
				{
					m_Worlds->AddWorld();
				}

				return true;
			}
		}
	}
}