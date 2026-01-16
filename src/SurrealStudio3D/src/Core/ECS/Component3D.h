#pragma once

#include "Object3D.h"

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <memory>

namespace SurrealStudio {

	namespace SurrealStudio3D {

		namespace ECS {

			using Vector3 = glm::vec3;

			struct TransformComponent
			{
				Vector3 position;
				Vector3 rotation;
				Vector3 scale;
			};

			struct PositionComponent
			{
				Vector3 position;
			};

			struct VelocityComponent
			{
				Vector3 velocity{ 0.0f, 0.0f, 0.0f };
			};

			struct MeshComponent
			{
				std::string meshName;
				int meshID;

				enum class MeshType
				{
					None = 0,
					StaticMesh,
					SkeletalMesh,
					CustomMesh
				};

				MeshType meshType;
			};
				
			struct PhysicsComponent
			{
				float mass = 1.0f;

				Vector3 velocity{ 0.0f, 0.0f, 0.0f };
				Vector3 angularVelocity{ 0.0f, 0.0f, 0.0f };
				Vector3 scaleVelocity{ 0.0f, 0.0f, 0.0f };

				bool isKinematic = false;
			};

			struct LightComponent
			{
				std::string lightName;   // e.g. "WorldEnvironmentLight"
				int lightIndex = 0;      // Corresponds to selectedLight in lightOptions[]

				glm::vec3 position = { 0.0f, 0.0f, 0.0f };  // Position in world space
				glm::vec3 direction = { 0.0f, -1.0f, 1.0f }; // For directional or spot lights
				float intensity = 1.0f;             // Brightness multiplier
				glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f }; // RGBA

				// Spot/Point light specific
				float radius = 100.0f;  // Affects attenuation for point/spot lights
				float angle = 45.0f;    // Spotlight cone angle in degrees

				// ADVANCED SETTINGS
				bool castsShadows = false; // Optional
				float shadowSoftness = 0.0f;
				float shadowBias = 0.0f;

				// Flicker/Noise
				float flickerIntensityMaximum = 0.0f;
				float flickerIntensityMinimum = 0.0f;
				float flickerSpeed = 0.0f;

				float glowRadius = 0.0f;
				float glowIntensity = 0.0f;

				glm::vec4 GLMVEC4_glowColor{ 0.0f, 0.0f, 0.0f, 0.0f };
				glm::vec4 GLMVEC4_colorStart{ 0.0f, 0.0f, 0.0f, 0.0f };
				glm::vec4 GLMVEC4_colorEnd{ 0.0f, 0.0f, 0.0f, 0.0f };
				glm::vec2 GLMVEC2_movementVector{ 0.0f, 0.0f };

				float gradientRadius = 0.0f;
				float tempature = 0.0f;

				float pulseAmplitude = 0.0f;
				float pulseFrequency = 0.0f;

				struct LightShape
				{
					float coneAngle = 0.0f; // For Spot Light
					float width = 0.0f;
					float height = 0.0f;
				};

				LightShape STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightShape_DETAILS;

				// Layer/Blending
				int layerMask = 0;
				float intensityBlend = 0.0f;

				struct LightAttenuation
				{
					float constant = 1.0f;
					float linear = 0.09f;
					float quadratic = 0.032f;
				};

				LightAttenuation STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightAttenuation_DETAILS;

				enum class WorldCanvas_WorldCanvas_Lighting2D_LightingType
				{
					None = 0,
					WorldEnvironmentLight, SurrealAmbientLight,
					SurrealPointLight, SurrealSpotLight, SurrealAreaLight,
					SurrealEmissiveLight
				};
				WorldCanvas_WorldCanvas_Lighting2D_LightingType STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightingType_DETAILS;
			};

			struct CameraComponent
			{
				Vector3 position{ 0.0f, 0.0f, 0.0f };
				Vector3 rotation{ 0.0f, 0.0f, 0.0f };
				float zoom{ 1.0f };

				Vector3 velocity{ 0.0f, 0.0f, 0.0f };
				float rotationSpeed{ 0.0f };
				float zoomSpeed{ 0.0f };

				Vector3 minBounds{ -1000.0f, -1000.0f , -1000.0f};
				Vector3 maxBounds{ 1000.0f, 1000.0f, 1000.0f };

				float orthoLeft{ 0.0f }, orthoRight{ 0.0f }, orthoTop{ 0.0f }, orthoBottom{ 0.0f };

				enum class CameraType
				{
					None = 0,
					Normal, Orthographic
				};

				CameraType cameraType;
			};

			struct AssetComponent
			{
				using AssetID = uint64_t;

				AssetID assetID = 0;               // Stable system ID
				std::string assetName;             // Editor / debug name

				enum class AssetType
				{
					None = 0,
					Mesh
				};

				enum class LoadState
				{
					Unloaded = 0,
					Loading,
					Loaded,
					Failed
				};

				AssetType assetType = AssetType::None;
				LoadState loadState = LoadState::Unloaded;
			};

			class Component3D
			{
			public:
				std::vector<std::unique_ptr<TransformComponent>> transformComponentVector;
				std::vector<std::unique_ptr<MeshComponent>> meshComponentVector;
				std::vector<std::unique_ptr<PhysicsComponent>> physicsComponentVector;
				std::vector<std::unique_ptr<LightComponent>> lightComponentVector;
				std::vector<std::unique_ptr<CameraComponent>> cameraComponentVector;
				std::vector<std::unique_ptr<AssetComponent>> assetComponentVector;

				TransformComponent transformComponent;
				MeshComponent meshComponent;
				PhysicsComponent physicsComponent;
				LightComponent lightComponent;
				CameraComponent cameraComponent;
				AssetComponent assetComponent;
				VelocityComponent velocityComponent;
			};

			class ComponentManager3D
			{
			public:

				bool AddComponent(Object3D& object,std::unique_ptr<Component3D>&& componetType) noexcept;
				bool DeleteComponent(Object3D& object, Component3D* componentType) noexcept;

				Component3D* GetComponent() const noexcept { return m_Component.get(); }

				std::vector<Component3D*> GetAllComponents() const noexcept {
					std::vector<Component3D*> ptrs;
					for (auto& c : m_Components)
						ptrs.push_back(c.get());
					return ptrs;
				}
				std::unique_ptr<Component3D> m_Component;
			private:

				std::vector<std::unique_ptr<Component3D>> m_Components;
			};
		}
	}
}