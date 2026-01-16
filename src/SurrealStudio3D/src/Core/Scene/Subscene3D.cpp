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
						m_Worlds->DeleteAllWorlds();  // Because if a subscene is deleted, all the Worlds in that Subscene will also get deleted as well
						return true;  // Success
					}
				}

				return false;  // Fail
			}
		}
	}
}