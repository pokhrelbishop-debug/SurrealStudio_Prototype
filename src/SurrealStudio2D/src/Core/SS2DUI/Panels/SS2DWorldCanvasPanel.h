#pragma once

#include <string>
#include <vector>
#include <memory>

#include <glm/glm.hpp>

namespace SurrealStudio {

	namespace SurrealStudio2D {

		struct WorldCanvas
		{
			struct WorldCanvas_GroundSettings
			{
				glm::vec4 WorldCanvas_GroundSettings_WorldGroundCOLOR{ 0.0f, 0.0f, 0.0f, 0.0f };
				glm::vec2 WorldCanvas_WorldGroundSize{};  // By default, there IS no World Ground

				bool WorldCanvas_DoesWorldGroundHaveMaterialAsGroundColor = false;
			};

			struct WorldCanvas_MiddleGroundSettings
			{
				glm::vec4 WorldCanvas_MiddleGroundSettings_WorldMiddleGroundCOLOR{ 0.0f, 0.0f, 0.0f, 0.0f };
				glm::vec2 WorldCanvas_MiddleGroundSize{};

				bool WorldCanvas_DoesWorldMiddleGroundHaveMaterialAsMiddleGroundColor = false;
			};

			struct WorldCanvas_SkySettings
			{
				glm::vec4 WorldCanvas_SkySettings_SkySettingsCOLOR{ 0.0f, 0.0f, 0.0f, 0.0f };
				glm::vec2 WorldCanvas_SkySettingsSize{};

				bool WorldCanvas_DoesWorldSkyHaveMaterialAsSkyColor = false;
			};

			struct WorldCanvasMaterial
			{
				std::string WorldCanvas_MaterialName; 
				int WorldCanvas_MaterialID;
			};

			struct WorldCanvas_Lighting2D
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

			struct WorldCanvas_Particle2D
			{
				int i_particleID;
				
				// Basic transform for particles
				glm::vec2 GLMVEC2_particlePosition{ 0.0f, 0.0f };
				float f_particleRotation = 0.0f;
				glm::vec2 GLMVEC2_particleScale{ 0.0f, 0.0f };

				glm::vec4 GLMVEC4_particleColor{ 0.0f, 0.0f, 0.0f, 0.0f };
				int i_particleTextureID = -1;

				glm::vec2 GLMVEC2_particleVelocity{ 0.0f, 0.0f };
				float f_particleAngularVelocity;
				glm::vec2 GLMVEC2_particleScaleVelocity{ 0.0f, 0.0f };

				float f_particleLifetime = 0.0f;
				float f_particleAge = 0.0f;

				bool b_isParticleActive = true; // Default value, use with ImGui::Checkbox
				float f_particleDrag;
				float f_particleGravityEffect;
				bool b_ParticleFadeOut = false; // Default value, use with ImGui::Checbox

				struct WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter
				{
					// Timing
					float f_SpawnRate = 0.0f;
					float f_StartDelay = 0.0f;
					float f_Duration = 0.0f;

					bool b_Looping = false;

					// Emitter Shape / Type
					enum class WorldCanvas_Particle2D_ParticleEmitter_ParticleEmitterType
					{
						None = 0,
						Point,
						Box,
						Circle,
						Cone
					};

					WorldCanvas_Particle2D_ParticleEmitter_ParticleEmitterType ENUMCLASS_INSTANCE_WorldCanvas_Particle2D_ParticleEmitterType_DETAILS = WorldCanvas_Particle2D_ParticleEmitter_ParticleEmitterType::None;

					// Emitter size and direction
					glm::vec2 GLMVEC2_Size{ 0.0f, 0.0f };
					glm::vec2 GLMVEC2_Direction{ 0.0f, 1.0f }; // default pointing up

					// Randomization
					float f_AngleVariance = 0.0f;
					float f_SpeedMin = 0.0f;
					float f_SpeedMax = 0.0f;

					// Particle limits
					int i_MaxParticles = 100;

					// Physics influence
					bool b_UseGravity = false;
					float f_GravityScale = 1.0f;
				};

				std::vector<std::unique_ptr<WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter>> WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter_DETAILS;	


				enum class WorldCanvas_Particle2D_ParticleType
				{
					None = 0,
					BrightParticle,
					DarkParticle,
					FireParticle,
					SmokeParticle,
					CustomParticle
				};

				struct WorldCanvas_Particle2D_Material
				{
					std::string WorldCanvas_Particle2D_Material_Name;
					int WorldCanvas_Particle2D_Material_ID;
				};

				WorldCanvas_Particle2D_ParticleType ENUMCLASS_INSTANCE__WorldCanvas_Particle2D_ParticleType_DETAILS = WorldCanvas_Particle2D_ParticleType::None; // Set default
				std::vector<std::unique_ptr<WorldCanvas_Particle2D_Material>> STRUCT_INSTANCE_VEC_UNIQUEPTR_WorldCanvas_Particle2D_Material_DETAILS;
			};

			struct WorldCanvas_Physics2D
			{
				bool b_IsPhysicsEnable = false;
				bool b_UseGravity = false;
				bool b_IsKinematic = false;
				bool b_Trigger = false;
				bool b_Sleeping = false;

				float f_Mass = 0.0f;
				float f_GravityScale = 0.0f;
				float f_Drag = 0.0f;
				float f_AngularDrag = 0.0f;
				float f_Density = 0.0f;
				float f_Friction = 0.0f;
				float f_Bounciness = 0.0f;
				float f_AngularVelocity = 0.0f;

				int i_CollisionLayer = 0;
				int i_CollisionMask = 0;

				glm::vec2 GLMVEC2_Size{ 0.0f, 0.0f };
				glm::vec2 GLMVEC2_Velocity{ 0.0f, 0.0f };

				enum class WorldCanvas_Physics2D_CollisionShape
				{
					None = 0,
					Square,
					Circle,
					Polygon,
					Capsule,
					Edge,
					Triangle,
					Chain
				};

				WorldCanvas_Physics2D_CollisionShape ENUMCLASS_INSTANCE__WorldCanvas_Physics2D_CollisionShape_DETAILS = WorldCanvas_Physics2D_CollisionShape::None; // Set default
			};

			struct WorldCanvas_Camera2D
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

				enum class WorldCanvas_Camera2D_CameraType { None = 0, Normal, Orthographic };
				WorldCanvas_Camera2D_CameraType SI_WorldCanvas_Camera2D_CameraType_DETAILS;
			}; 

			std::vector<std::unique_ptr<WorldCanvasMaterial>> WorldCanvas_WorldCanvasMaterial_DETAILS;
			std::vector<std::unique_ptr<WorldCanvas_Lighting2D>> WorldCanvas_WorldCanvas_Lighting2D_DETAILS;
			std::vector<std::unique_ptr<WorldCanvas_Camera2D>> WorldCanvas_WorldCanvas_Camera2D_DETAILS;
			std::vector<std::unique_ptr<WorldCanvas_Particle2D>> WorldCanvas_WorldCanvas_Particle2D_DETAILS;
		};

		class SS2DWorldCanvasPanel
		{
		public:

			bool DrawSS2DWorldCanvasPanel();
			bool DrawWorldGroundSettings();
			bool DrawWorldMiddleGroundSettings();
			bool DrawWorldSkySettings();

			bool DrawWorldCanvas_CameraCreation();
			bool DrawWorldCanvas_CameraProperties(const char* WorldCanvas_cameraOptions[], int index);

			bool DrawWorldCanvas_LightCreation();
			bool DrawWorldCanvas_LightProperties(const char* WorldCanvas_lightingOptions[], int index);

			bool DrawWorldCanvas_2DParticleCreation();
			bool DrawWorldCanvas_2DParticleProperties(const char* WorldCanvas_2DparticleOptions[], int index);

			bool DrawWorldCanvas_2DParticleEditor_Properties(const char* WorldCanvas_2DparticleOptions[], int index);
			bool DrawWorldCanvas_2DLightEditor_Properties();

			bool b_WorldCanvas_isWindowOpen = true;

		private:

			std::vector<std::unique_ptr<WorldCanvas>> m_SS2DWorldCanvas_DETAILS;
			std::vector<std::unique_ptr<WorldCanvas::WorldCanvas_GroundSettings>> m_WorldCanvas_WorldGround_DETAILS;
			std::vector<std::unique_ptr<WorldCanvas::WorldCanvas_MiddleGroundSettings>> m_WorldCanvas_WorldMiddleGround_DETAILS;
			std::vector<std::unique_ptr<WorldCanvas::WorldCanvas_SkySettings>> m_WorldCanvas_WorldSky_DETAILS;
		};
	}
}