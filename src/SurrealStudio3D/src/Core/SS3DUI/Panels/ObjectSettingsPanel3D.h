#pragma once

#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <vector>

namespace SurrealStudio {

	namespace SurrealStudio3D {

		struct Mesh3D
		{
			std::string meshName;
			int meshID;

			enum class MeshType
			{
				None = 0,
				StaticMesh,
				SkeletalMesh,
				DynamicMesh
			};

			MeshType ENUM_INSTANCE__MeshType_DETAILS = MeshType::None;
		};

		struct Material3D
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

			MaterialType ENUM_INSTANCE__MaterialType_DETAILS = MaterialType::None;
		};

		struct Transform3D
		{
			glm::vec3 objectPosition{ 0.0f, 0.0f, 0.0f };
			glm::vec3 objectScale{ 1.0f, 1.0f, 1.0f };
			glm::vec3 objectRotation{ 0.0f, 0.0f, 0.0f };
		};

		struct HealthObject3D
		{
			int i_HealthObjectID;

			float f_Health = 100.0f;
			bool b_IsHealthObjectAttachedToPlayerObject = false;  // See if it is a child of Player (OBJECT)
		};

		struct Color3D
		{
			glm::vec4 color{ 0.0f, 0.0f, 0.0f, 0.0f };
		};

		struct ExtraObject3D
		{
			std::string extraObjectName;
			int extraObjectID;

			struct TriggerObject3D
			{
				int triggerObjectID;

				enum class TriggerObject3DType
				{
					None = 0,
					MoveTrigger
				};

				TriggerObject3DType ENUM_INSTANCE__TriggerObject3DType_triggerObject3DType = TriggerObject3DType::None;
			};

			Transform3D STRUCT_INSTANCE__Transform3D_transform;
			Color3D STRUCT_INSTANCE__Color3D_color;
			HealthObject3D STRUCT_INSTANCE__HealthObject3D_healthObject;

			bool b_showPlayerObjectFlag = false;
			bool b_showIfPlayerObjectHasScriptAttachedFlag = false;

			std::vector<std::unique_ptr<Mesh3D>> meshs;
			std::vector<std::unique_ptr<TriggerObject3D>> triggerObject3D;
		};

		struct Object3D
		{
			std::string objectName;
			int objectID;

			Transform3D STRUCT_INSTANCE__Transform3D_transform;
			Color3D STRUCT_INSTANCE__Color3D_color;

			bool enablePhysics = false; // default

			std::vector<std::unique_ptr<Mesh3D>> meshes;

			enum class Object3D_Object3DType
			{
				None = 0,
				CubeObject,
				SphereObject,
				CapsuleObject,
				CylinderObject,
				ConeObject,
				DountObject,
				PlaneObject
			};

			Object3D_Object3DType ENUM_INSTANCE__ObjectSettingsPanel3D_Object3D_Objec3DType_DETAILS = Object3D_Object3DType::None;
		};


		class ObjectSettingsPanel3D
		{
		public:

			bool ObjectSettingsPanel3D_DrawObjectSettingsPanel3D();

			bool ObjectSettingsPanel3D_DrawObjectCreation();
			bool ObjectSettingsPanel3D_DrawObjectExtraCreation();

			bool ObjectSettingsPanel3D_DrawObjectProperties(const char* object3D_options[], int index);
			bool ObjectSettingsPanel3D_DrawExtraObjectProperties(const char* extraObject3D_options[], int index);

		private:

			std::vector<std::unique_ptr<Object3D>> m_Objects;
			std::vector<std::unique_ptr<ExtraObject3D>> m_ExtraObjects;
			std::vector<std::unique_ptr<Material3D>> m_Materials;
			std::vector<std::unique_ptr<Mesh3D>> m_Meshses;

			std::unique_ptr<Material3D> m_Material = std::make_unique<Material3D>();
		};
	}
}