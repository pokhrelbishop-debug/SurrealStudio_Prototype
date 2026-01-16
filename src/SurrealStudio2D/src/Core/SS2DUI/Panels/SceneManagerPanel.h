#pragma once

#include "SS2DWorldCanvasPanel.h"

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <string>

#include "../src/SurrealStudio2D/src/Core/SS2DEngineDefines.h"
#include "../src/SurrealStudio2D/src/Core/Scene/Scene.h"
#include "../src/SurrealStudio2D/src/Core/Scene/Subscene.h"
#include "../src/SurrealStudio2D/src/Core/Scene/World.h"

namespace SurrealStudio {

	namespace SurrealStudio2D {

		/* Temporary Light2D struct; contains all the data for a light in a World */
		struct Lighting2D
		{
			std::string lightName;   // e.g. "WorldEnvironmentLight"
			int lightIndex = 0;      // Corresponds to selectedLight in lightOptions[]

			glm::vec2 position = { 0.0f, 0.0f };  // Position in world space
			glm::vec2 direction = { 0.0f, -1.0f }; // For directional or spot lights
			float intensity = 1.0f;             // Brightness multiplier
			glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f }; // RGBA

			// Spot/Point light specific
			float radius = 100.0f;  // Affects attenuation for point/spot lights
			float angle = 45.0f;    // Spotlight cone angle in degrees

			bool castsShadows = false; // Optional
		};

		struct Camera2D
		{
			glm::vec2 position = { 0.0f, 0.0f };  // World position
			float rotation = 0.0f;                 // Rotation in degrees
			float zoom = 1.0f;                     // Zoom factor / scale

			glm::vec2 velocity = { 0.0f, 0.0f };  // Movement velocity
			float rotationSpeed = 0.0f;            // Degrees per second
			float zoomSpeed = 0.0f;                // Zoom change per second
			glm::vec2 viewportSize = { 0.0f, 0.0f };
			glm::vec2 target = { 0.0f, 0.0f };

			float orthographicBoundsLeft = 0.0f, orthographicBoundsRight = 0.0f, orthographicBoundsTop = 0.0f, orthographicBoundsBottom = 0.0f;

			// Optional boundaries
			glm::vec2 minBounds = { -1000.0f, -1000.0f };
			glm::vec2 maxBounds = { 1000.0f, 1000.0f };
		};


		class SceneManagerPanel
		{
		public:

			SceneManagerPanel() = default;
			~SceneManagerPanel() = default;

			bool DrawLightProperties(const char* lightingOptions[], int index);
			bool DrawCameraProperties(const char* cameraOptions[], int index);
			bool DrawSceneCreation();

			bool DrawSceneManagerPanel();
			bool DrawLightingCreationAndProperties();
			bool DrawCameraCreationAndProperties();

		private:

			std::vector<std::unique_ptr<Scene>> m_Scenes;
			std::vector<std::unique_ptr<Subscene>> m_Subscenes;
			std::vector<std::unique_ptr<World>> m_Worlds;

			std::vector<std::unique_ptr<Lighting2D>> m_Lights;
			std::vector<std::unique_ptr<Camera2D>> m_Cameras;

			SS2DWorldCanvasPanel m_SS2DWorldCanvasPanel;
		};
	}
}