#include "Object3D.h"

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include <glm/glm.hpp>

namespace SurrealStudio {

	namespace SurrealStudio3D {

		namespace ECS {

			bool Object3D::Object3D_AddObject(std::unique_ptr<Object3D_ObjectData> objects, const std::string& objectName) noexcept
			{
				objects = std::make_unique<Object3D_ObjectData>();
				if (!objects) return false;

				objects->objectName = objectName;
				objects->objectID = m_NextID++;
				objects->enablePhysics = false;  // Default
				objects->objectTransform.position = { 0.0f, 0.0f, 0.0f };
				objects->objectTransform.rotation = { 0.0f, 0.0f, 0.0f };
				objects->objectTransform.scale = { 1.0f, 1.0f, 1.0f };

				m_Objects.push_back(std::move(objects));
				return true;
			}

			bool Object3D::Object3D_RemoveObject(int objectID) noexcept
			{
				auto it = std::find_if(m_Objects.begin(), m_Objects.end(),
					[objectID](const std::unique_ptr<Object3D_ObjectData>& object) {
						return object->objectID == objectID;
					}
				);

				if (it != m_Objects.end())
				{
					m_Objects.erase(it);
					return true;
				}
				return false;
			}

			bool Object3D::Object3D_UpdateObject(int objectID, float deltaTime) noexcept
			{
				for (auto& object : m_Objects)
				{
					if (object->objectID == objectID)
					{
						object->objectTransform.position.x += 10.0f * deltaTime;
						object->objectTransform.rotation.x += 45.0f * deltaTime;
						object->objectTransform.scale.x += 1.0f * deltaTime;
						return true; // Found; updated
					}
				}

				return false;  // Failed to find object, falied to update
			}

			Object3D_ObjectData* Object3D::GetObject(int objectID) const noexcept
			{
				for (const auto& object : m_Objects)
				{
					if (object->objectID == objectID)
						return object.get(); // found
				}
				return nullptr; // Not found
			}
		}
	}
}