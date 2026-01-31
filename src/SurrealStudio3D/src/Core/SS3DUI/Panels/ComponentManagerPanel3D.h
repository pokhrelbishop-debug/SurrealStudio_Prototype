#pragma once

#include "../src/SurrealStudio3D/src/Core/ECS/Component3D.h"
#include "../src/SurrealStudio3D/src/Core/ECS/Object3D.h"

namespace SurrealStudio {

	namespace SurrealStudio3D {

		class ECS::Object3D;

		class ComponentManagerPanel3D
		{
		public:

			bool DrawComponentCreation();
			bool DrawComponentProperties(const char* componentOptions[], int index);  // Minimal
			bool DrawComponent3DEditor(const char* componentOptions[], int index); // Large
			bool DrawComponentManagerPanel3D();

		private:
			
			std::vector<std::unique_ptr<ECS::Component3D>> m_Components_ToIntegrateWithUI;

			ECS::ComponentManager3D componentManager;
			ECS::Object3D m_Object_NeededForComponent;
			std::unique_ptr<ECS::Component3D> m_ComponentType = std::make_unique<ECS::Component3D>();
		};
	}
}