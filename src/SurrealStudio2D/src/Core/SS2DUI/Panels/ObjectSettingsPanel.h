#pragma once

#include "../src/SurrealStudio2D/src/Core/Scene/World.h"

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <memory>

namespace SurrealStudio {

	namespace SurrealStudio2D {

		struct Mesh;
		//{
		//	std::string meshName;
		//	int meshID;

		//	enum class MeshType
		//	{
		//		None = 0,
		//		StaticMesh,
		//		SkeletalMesh,
		//		DynamicMesh
		//	};

		//	MeshType meshType;
		//};

		struct Material2D
		{
			std::string materialName;
			int materialID;

			enum class MaterialType
			{
				None = 0,
				ColorMaterial,
				TextureMaterial,
				CustomMaterial
			};

			MaterialType materialType;
		};

		struct Transform
		{
			glm::vec2 objectPosition;
			glm::vec2 objectScale;
			float objectRotation;
		};

		struct HealthObject2D
		{
			int healthObjectID;

			float health = 100.0f;
			bool isHealthObjectAttachedToPlayerObject = false;  // See if it is a child of Player (OBJECT)
		};
		
		struct Color2D
		{
			float r;
			float g;
			float b;
			float a;
		};

		struct ExtraObject2D
		{
			std::string extraObjectName;
			int extraObjectID;

			struct TriggerObject2D
			{
				int triggerObjectID;

				enum class TriggerObject2DType
				{
					None = 0,
					MoveTrigger
				};
			};

			Transform transform;
			Color2D color;
			HealthObject2D healthObject;

			bool showPlayerObjectFlag = false;
			bool showIfPlayerObjectHasScriptAttachedFlag = false;

			std::vector<std::unique_ptr<Mesh>> meshs;
			std::vector<std::unique_ptr<Component>> components;
			std::vector<std::unique_ptr<TriggerObject2D>> triggerObject2D;
 		};

		struct Object2D
		{
			std::string objectName;
			int objectID;

			Transform transform;
			Color2D color;

			bool enablePhysics = false; // default

			std::vector<std::unique_ptr<Mesh>> meshs;
			std::vector<std::unique_ptr<Component>> components;
		};

		class ObjectSettingsPanel
		{
		public:
			
			bool DrawObjectSettingsPanel();  // basically just OnImGuiRender	
			bool DrawObjectCreation();
			bool ShowAndDrawObjectProperties(const char* objectOptions[], int index);
			bool DrawObjectExtraCreation();
			bool ShowAndDrawExtraObjectProperties(const char* extraObjectOptions[], int index);

		private:

			std::vector<std::unique_ptr<Object2D>> m_Objects;
			std::vector<std::unique_ptr<ExtraObject2D>> m_ExtraObjects;
			std::vector<std::unique_ptr<Material2D>> m_Materials;

			Mesh::MeshType m_CurrentObjectMesh;
			Material2D::MaterialType m_CurrentObjectMaterialType;

			std::unique_ptr<Material2D> m_Material;
		};
	}
}