#pragma once

#include <string>
#include <vector>
#include <memory>
#include <ctime>

#include <glm/glm.hpp>

namespace SurrealStudio {

	namespace SurrealStudio3D {

		namespace AssetManagement {

			class Asset
			{
			public:

				enum class AssetType
				{
					None = 0,
					Mesh,
					Material,
					Texture,
					Animation,
					Other
				};

				struct Transform
				{
					glm::vec3 position{ 0.0f, 0.0f, 0.0f };
					glm::vec3 rotation{ 0.0f, 0.0f, 0.0f }; // Vec3 for Euler angles
					glm::vec3 scale{ 1.0f, 1.0f, 1.0f };
				};

				int m_AssetID;
				std::string m_AssetName;
				std::string m_Asset_FilePathToAsset;

				Transform m_AssetTransform;

				std::unique_ptr<AssetType> m_AssetType;

				// ----------------------
				// Data components
				// ----------------------

				struct MeshData
				{
					std::vector<glm::vec3> vertices;
					std::vector<unsigned int> indices;
					std::vector<glm::vec3> normals;
					std::vector<glm::vec2> uvs; // optional UV coordinates
				};

				struct AnimationData
				{
					std::string animationName;
					float duration = 0.0f; // seconds
					int frameCount = 0;

					struct Keyframe
					{
						float time; // seconds
						Transform transform;
					};
					std::vector<Keyframe> keyframes;
				};

				struct Materials
				{
					std::string materialName;
					glm::vec4 albedoColor{ 1.0f, 1.0f, 1.0f, 1.0f };
					float metallic = 0.0f;
					float roughness = 1.0f;
					float opacity = 1.0f;

					std::string albedoTexturePath;
					std::string normalTexturePath;
					std::string metallicRoughnessTexturePath;
				};

				struct Textures
				{
					std::string textureName;
					std::string textureFilePath;
					int width = 0;
					int height = 0;
					int channels = 0; // 3=RGB, 4=RGBA
				};

				struct BoundingBox
				{
					glm::vec3 min{ 0.0f, 0.0f, 0.0f };
					glm::vec3 max{ 0.0f, 0.0f, 0.0f };
				};

				// ----------------------
				// Asset composition
				// ----------------------
				MeshData m_AssetMeshData;
				std::vector<std::shared_ptr<Materials>> m_AssetMaterials;
				std::vector<std::shared_ptr<Textures>> m_AssetTextures;

				BoundingBox m_AssetBoundingBox;
				std::vector<AnimationData> m_AssetAnimations;

				std::time_t m_AssetDateLoaded = std::time(nullptr);

				bool m_IsDirty = false;
			};
		}
	}
}
