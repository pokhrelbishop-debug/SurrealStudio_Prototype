#include "System3D.h"

namespace SurrealStudio {

	namespace SurrealStudio3D {

		namespace ECS {

			bool MovementSystem::Update(ComponentManager3D& componentManager, float deltaTime) noexcept
			{
				for (auto* component : componentManager.GetAllComponents())
				{
					if (!component) continue;

					component->transformComponent.position.x += component->physicsComponent.velocity.x * deltaTime;
					component->transformComponent.position.y += component->physicsComponent.velocity.y * deltaTime;
					component->transformComponent.position.z += component->physicsComponent.velocity.z * deltaTime;

					component->transformComponent.rotation.x += component->physicsComponent.angularVelocity.x * deltaTime;
					component->transformComponent.rotation.y += component->physicsComponent.angularVelocity.y * deltaTime;
					component->transformComponent.rotation.z += component->physicsComponent.angularVelocity.z * deltaTime;

					component->transformComponent.scale.x += component->physicsComponent.scaleVelocity.x * deltaTime;
					component->transformComponent.scale.y += component->physicsComponent.scaleVelocity.y * deltaTime;
					component->transformComponent.scale.z += component->physicsComponent.scaleVelocity.z * deltaTime;
				}

				return true;
			}

			bool PhysicsSystem::Update(ComponentManager3D& componentManager, float deltaTime) noexcept
			{
				for (auto* component : componentManager.GetAllComponents())
				{
					if (!component) continue;

					auto& position = component->transformComponent.position;
					auto& rotation = component->transformComponent.rotation;
					auto& scale = component->transformComponent.scale;
					auto& velocity = component->physicsComponent.velocity;
					auto& angularVelocity = component->physicsComponent.angularVelocity;
					auto& scaleVelocity = component->physicsComponent.scaleVelocity;

					position += velocity * deltaTime;
					rotation += angularVelocity * deltaTime;
					scale += scaleVelocity * deltaTime;
				}
				return true;
			}

			bool CameraSystem::Update(ComponentManager3D& componentManager, float deltaTime) noexcept
			{
				for (auto* component : componentManager.GetAllComponents())
				{
					if (!component) continue;

					component->cameraComponent.position = component->transformComponent.position;
					component->cameraComponent.velocity = component->physicsComponent.velocity;
					component->cameraComponent.rotation = component->transformComponent.rotation;
				}
				return true;
			}

			bool LightSystem::Update(ComponentManager3D& componentManager, float deltaTime) noexcept
			{
				for (auto* component : componentManager.GetAllComponents())
				{
					if (!component) continue;

					component->lightComponent.position = component->transformComponent.position;
				}

				return true;
			}

			bool AssetSystem::Update(ComponentManager3D& componentManager, float deltaTime) noexcept
			{
				for (auto* component : componentManager.GetAllComponents())
				{
					if (!component) continue;

					component->assetComponent.assetID = static_cast<int>(componentManager.m_Component->assetComponentVector.size()) + 1;
				}

				return true;
			}
		}
	}
}