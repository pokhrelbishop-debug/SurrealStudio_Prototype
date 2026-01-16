#pragma once

#include <string>
#include <vector>
#include <memory>

namespace SurrealStudio {

	namespace SurrealStudio2D {

		struct Object
		{
			std::string objectName;
			int objectID;

			// TODO: Replace with ECS later

			// ////////////////////////////////
			// Transform
			// //////////////////////////

			// Position
			double objectPositionSizeX{};
			double objectPositionSizeY{};

			// Rotation (degrees)
			double objectRotationSizeX{};
			double objectRotationSizeY{};

			// Scale
			double objectScaleSizeX{ 1.0 };
			double objectScaleSizeY{ 1.0 };
		};

		struct Component
		{
			std::string componentName;
		};

		struct Mesh
		{
			std::string meshName;
			int meshID{};
			std::string meshType;

			enum class MeshType
			{
				None = 0,
				StaticMesh,
				SkeletalMesh,
				CustomMesh,
				DynamicMesh
			};
		};

		struct WorldData
		{
			std::string worldName;
			int worldID{};

			std::vector<Object> objects;
			std::vector<Component> components;
			std::vector<Mesh> mesh;
		};

		class World
		{
		public:
			void AddWorld(std::unique_ptr<WorldData> world);
			void DeleteWorld(const std::string& worldName);

			std::string GetWorldName(int index) const;

		private:
			std::vector<std::unique_ptr<WorldData>> m_Worlds;
		};
	}

} // namespace SurrealStudio2D
