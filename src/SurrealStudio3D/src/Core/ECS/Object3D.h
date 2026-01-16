#pragma once

#include <string>
#include <vector>
#include <memory>

#include <glm/glm.hpp>

namespace SurrealStudio {

	namespace SurrealStudio3D {

		namespace ECS {

			using Vector3 = glm::vec3;

			struct Transform3D
			{
				Vector3 position{ 0.0f, 0.0f, 0.0f };
				Vector3 rotation{ 0.0f, 0.0f, 0.0f };
				Vector3 scale{ 1.0f, 1.0f, 1.0f };
			};

			struct Object3D_ObjectData
			{
				std::string objectName;
				int objectID;

				Transform3D objectTransform;
				bool enablePhysics;
			};

			class Object3D
			{
			public:

				bool Object3D_AddObject(std::unique_ptr<Object3D_ObjectData> object, const std::string& objectName) noexcept;
				bool Object3D_RemoveObject(int objectID) noexcept;
				bool Object3D_UpdateObject(int objectID, float deltaTime) noexcept;
				bool Object3D_ClearAllObjects() noexcept { m_Objects.clear(); return true; }

				Object3D_ObjectData* GetObject(int objectID) const noexcept;
				const std::vector<std::unique_ptr<Object3D_ObjectData>>& GetAllObjects() const noexcept { return m_Objects; }
				Object3D_ObjectData objectData;

			private:

				std::vector<std::unique_ptr<Object3D_ObjectData>> m_Objects;
				int m_NextID = 0;
			};
		}
	}
}