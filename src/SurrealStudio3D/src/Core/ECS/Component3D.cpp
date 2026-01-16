#include "Component3D.h"

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

namespace SurrealStudio {

	namespace SurrealStudio3D {

		namespace ECS {

			bool ComponentManager3D::AddComponent(Object3D& object, std::unique_ptr<Component3D>&& componentType) noexcept
			{
				m_Components.push_back(std::move(componentType));
				return true;
			}

			bool ComponentManager3D::DeleteComponent(Object3D& object, Component3D* componentType) noexcept
			{
				auto it = std::remove_if(m_Components.begin(), m_Components.end(),
					[componentType](const std::unique_ptr<Component3D>& c) {return c.get() == componentType; }
				);

				if (it != m_Components.end())
				{
					m_Components.erase(it, m_Components.end());
					return true;
				}
				else
					return false;
			}
		}
	}
}