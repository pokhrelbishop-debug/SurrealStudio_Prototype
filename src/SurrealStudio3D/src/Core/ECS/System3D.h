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
				System(const System&) = delete;
				System& operator=(const System&) = delete;
				System(System&&) noexcept = default;
				System& operator=(System&&) noexcept = default;

				virtual bool Update(ComponentManager3D& componentManager, float deltaTime) noexcept = 0;
			};

			class MovementSystem : public System
			{
			public:

				MovementSystem() = default; ~MovementSystem() = default;
				MovementSystem(const MovementSystem&) = delete;
				MovementSystem& operator=(const MovementSystem&) = delete;
				MovementSystem(MovementSystem&&) noexcept = default;
				MovementSystem& operator=(MovementSystem&&) noexcept = default;

				bool Update(ComponentManager3D& componentManager, float deltaTime) noexcept override;
			};

			class PhysicsSystem : public System
			{
			public:

				PhysicsSystem() = default; ~PhysicsSystem() = default;
				PhysicsSystem(const PhysicsSystem&) = delete;
				MovementSystem& operator=(const PhysicsSystem&) = delete;
				PhysicsSystem(PhysicsSystem&&) noexcept = default;
				PhysicsSystem& operator=(PhysicsSystem&&) noexcept = default;

				bool Update(ComponentManager3D& componentManager, float deltaTime) noexcept override;
			};

			class CameraSystem : public System
			{
			public:
				CameraSystem() = default; ~CameraSystem() = default;
				CameraSystem(const CameraSystem&) = delete;
				CameraSystem& operator=(const CameraSystem&) = delete;
				CameraSystem(CameraSystem&&) noexcept = default;
				CameraSystem& operator=(CameraSystem&&) noexcept = default;

				bool Update(ComponentManager3D& componentManager, float deltaTime) noexcept override;
			};

			class LightSystem : public System
			{
			public:

				LightSystem() = default; ~LightSystem() = default;
				LightSystem(const LightSystem&) = delete;
				LightSystem& operator=(const LightSystem&) = delete;
				LightSystem(LightSystem&&) noexcept = default;
				LightSystem& operator=(LightSystem&&) noexcept = default;

				bool Update(ComponentManager3D& componentManager, float deltaTime) noexcept override;
			};

			class AssetSystem : public System
			{
			public:
				AssetSystem() = default; ~AssetSystem() = default;
				AssetSystem(const AssetSystem&) = delete;
				AssetSystem& operator=(const AssetSystem&) = delete;
				AssetSystem(AssetSystem&&) noexcept = default;
				AssetSystem& operator=(AssetSystem&&) noexcept = default;

				bool Update(ComponentManager3D& componentManager, float deltaTime) noexcept override;
			};
		}
	}
}