#pragma once

#include <memory>
#include <vector>
#include <string>

#include <glm/glm.hpp>

#include "../src/SurrealStudio3D/src/Core/Scene/Scene3D.h"
#include "../src/SurrealStudio3D/src/Core/Scene/Subscene3D.h"
#include "../src/SurrealStudio3D/src/Core/Scene/World3D.h"	

namespace SurrealStudio {

	namespace SurrealStudio3D {

		struct Lighting3D
		{
			std::string lightName; // eg, WorLdEnvironmentLight
			int lightIndex = 0;  // the selected light index; engine internal

			glm::vec3 lightPosition{ 0.0f, 0.0f, 0.0f };
			glm::vec3 lightDirection{ 0.0f, 0.0f, 0.0f };
			glm::vec4 lightColor{ 0.0f, 0.0f, 0.0f, 0.0f };
			
			float intensity = 0.0f;
			float radius = 0.0f;
			float angle = 0.0f;
			
			bool castsShadows = false;

			enum class LightingType
			{
				None = 0,
				WorldEnvironmentLight,
				SurrealAmbientLight,
				SurrealPointLight,
				SurrealSpotLight,
				SurrealAreaLight,
				SurrealEmissiveLight
			};

			LightingType Lighting3D_LightingType_DETAILS = LightingType::None;  // set default;
		};

		struct Camera3D
		{
			std::string cameraName; // Normal or Orthographic
			int cameraIndex = 0;		

			glm::vec3 cameraPosition{ 0.0f, 0.0f, 0.0f };
			
			float rotation = 0.0f;
			float zoom = 0.0f;
			
			glm::vec3 viewportSize{ 0.0f, 0.0f, 0.0f };
			glm::vec3 cameraTarget{ 0.0f, 0.0f, 0.0f };

			float orthographicBoundsLeft = 0.0f, orthographicBoundsRight = 0.0f, orthographicBoundsBottom = 0.0f, orthographicBoundsTop = 0.0f;

			// Optional boundries
			glm::vec3 cameraMaximumBounds{ 0.0f, 0.0f, 0.0f }; // To be set by the user
			glm::vec3 cameraMinimumBounds{ 0.0f, 0.0f, 0.0f }; // To be set by the user

			float nearClip = 0.1f; // Minimum value, something small
			float farClip = 1000.0f; // Maximum value, set something defualt big IG

			enum class CameraType
			{
				None = 0,
				Normal,
				Orthographic
			};

			CameraType Camera3D_CameraType_DETAILS = CameraType::None;  // set default
		};

		class SceneManagerPanel3D
		{
		public:

			SceneManagerPanel3D() = default;
			~SceneManagerPanel3D() = default;


			bool SceneManagerPanel3D_DrawLighting3DProperties(const char* lighting3D_options[], int index);
			bool SceneManagerPanel3D_DrawCamera3DProperties(const char* camera3D_options[], int index);

			bool SceneManagerPanel3D_DrawSceneCreation();
			
			bool SceneManagerPanel3D_DrawSceneManagerPanel3D();
			bool SceneManagerPanel3D_DrawLighting3DCreation();
			bool SceneManagerPanel3D_DrawCamera3DCreation();

			bool DrawSceneDetailAndProperties3D();

		private:

			std::vector<std::unique_ptr<Lighting3D>> m_SceneManagerPanel3D_Lighting3D_DETAILS;
			std::vector<std::unique_ptr<Camera3D>> m_SceneManagerPanel3D_Camera3D_DETAILS;

			SceneSystem3D::Scene m_SceneManagerPanel3D_Scene3D;
			SceneSystem3D::Subscene m_SceneManagerPanel3D_Subscene3D;
			SceneSystem3D::World m_SceneManagerPanel3D_World3D;

			SceneSystem3D::SceneData m_SceneManagerPanel3D_SceneData;
			SceneSystem3D::SubsceneData m_SceneManagerPanel3D_SubsceneData;
			SceneSystem3D::WorldData m_SceneManagerPanel3D_WorldData;
		};
	}
}