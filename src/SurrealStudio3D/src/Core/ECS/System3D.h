#pragma once

#include "Component3D.h"

namespace SurrealStudio {

	namespace SurrealStudio3D {

		namespace ECS {

			// Base class System; everything inherits from this
			class System
			{
			public:

				System() = default;
				virtual ~System() = default;

				virtual bool Update(ComponentManager3D& componentManager, float deltaTime) noexcept = 0;
			};

			class MovementSystem : public System
			{
			public:

				MovementSystem() = default; ~MovementSystem() = default;

				bool Update(ComponentManager3D& componentManager, float deltaTime) noexcept override;
			};

			class PhysicsSystem : public System
			{
			public:

				PhysicsSystem() = default; ~PhysicsSystem() = default;

				bool Update(ComponentManager3D& componentManager, float deltaTime) noexcept override;
			};

			class CameraSystem : public System
			{
			public:
				CameraSystem() = default; ~CameraSystem() = default;

				bool Update(ComponentManager3D& componentManager, float deltaTime) noexcept override;
			};

			class LightSystem : public System
			{
			public:

				LightSystem() = default; ~LightSystem() = default;

				bool Update(ComponentManager3D& componentManager, float deltaTime) noexcept override;
			};

			class AssetSystem : public System
			{
			public:
				AssetSystem() = default; ~AssetSystem() = default;

				bool Update(ComponentManager3D& componentManager, float deltaTime) noexcept override;
			};
		}
	}
}