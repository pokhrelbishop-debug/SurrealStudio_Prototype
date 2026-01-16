#include "ObjectSettingsPanel3D.h"
#include "../src/SurrealStudio3D/src/SS3DEngineDefines.h"

#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <vector>
#include <imgui.h>
#include <stdexcept>

namespace SurrealStudio {

	namespace SurrealStudio3D {

		bool ObjectSettingsPanel3D::ObjectSettingsPanel3D_DrawObjectProperties(const char* object3D_options[], int index)
		{
			if (!object3D_options || index < 0 || index >= static_cast<int>(m_Objects.size()))
				return false;

			Object3D* STRUCT_INSTANCE__ObjectSettingsPanel3D_Object3D_object3D = m_Objects[index].get();
			if (!STRUCT_INSTANCE__ObjectSettingsPanel3D_Object3D_object3D)
				return false;

			ImGui::Text("%s Properties", object3D_options[index]);
			ImGui::Spacing();
			
			// //////////////////////
			// TRANSFORM
			// ///////////////////

			if (ImGui::CollapsingHeader("Transform"))
			{
				ImGui::DragFloat3("Position", &STRUCT_INSTANCE__ObjectSettingsPanel3D_Object3D_object3D->STRUCT_INSTANCE__Transform3D_transform.objectPosition[0], 0.1f);
				ImGui::DragFloat3("Rotation", &STRUCT_INSTANCE__ObjectSettingsPanel3D_Object3D_object3D->STRUCT_INSTANCE__Transform3D_transform.objectRotation[0], 0.1f);
				ImGui::DragFloat3("Scale", &STRUCT_INSTANCE__ObjectSettingsPanel3D_Object3D_object3D->STRUCT_INSTANCE__Transform3D_transform.objectScale[0], 0.1f);
			}

			if (ImGui::CollapsingHeader("Color"))
			{
				ImGui::ColorEdit4("Object Color", &STRUCT_INSTANCE__ObjectSettingsPanel3D_Object3D_object3D->STRUCT_INSTANCE__Color3D_color.color[0]);
			}

			if (ImGui::CollapsingHeader("Physics"))
			{
				if (ImGui::Checkbox("Enable Physics", &STRUCT_INSTANCE__ObjectSettingsPanel3D_Object3D_object3D->enablePhysics))
				{
					// TODO: Integrate with physics engine
				}
			}
			
			ImGui::Separator();
			ImGui::Text("Texture/Material");

			// Variables required for this function, and for texture material stuff
			static constexpr unsigned int s_CE_uI__ObjectSettingsPanel3D_Object3D_MAX_TEXTURES_MATERIALS_PER_WORLD_LIMIT = 25; // Limit to 25 for normal texture types
			static constexpr unsigned int s_CE_ui__ObjectSettingsPanel3D_Object3D_MAX_CUSTOM_TEXTURE_MATERIALS_PER_WORLD_LIMIT = 10; // Limit to 10 for custom texture types
			static constexpr unsigned int s_CE_uI__ObjectSettingsPanel3D_Object3D_MAX_OVERALL_TEXTURE_MATERIALS_PER_WORLD_LIMIT =
				s_CE_uI__ObjectSettingsPanel3D_Object3D_MAX_TEXTURES_MATERIALS_PER_WORLD_LIMIT + s_CE_ui__ObjectSettingsPanel3D_Object3D_MAX_CUSTOM_TEXTURE_MATERIALS_PER_WORLD_LIMIT;  // Overall limit for materials of any type
			
			static int s_I__ObjectSettingsPanel3D_Object3D_selectedMaterial3DIndex = 0;
			const char* c_CPTR__ObjectSettingsPanel3D_Object3D_materialTypeOptions[] = {
				"Colour material", "Texture material", "Custom material"
			};

			static bool s_B__ObjectSettingsPanel3D_Object3D_openMaxNormalTextureMaterialsReachedPerWorld_SS3DERROR_DialogBox = true;
			static bool s_B__ObjectSettingsPanel3D_Object3D_openMaxCustomTextureMaterialsReachedPerWorld_SS3DERROR_DialogBox = true;
			static bool s_B__ObjectSettingsPanel3D_Object3D_openMaxOverallTextureMaterialsReachedPerWorld_SS3DERROR_DialogBox = true;
			static bool s_B__ObjectSettingsPanel3D_Object3D_openMaterialTypeConfigurationDialogBox = true;

			if (s_B__ObjectSettingsPanel3D_Object3D_openMaterialTypeConfigurationDialogBox == true)
			{
				ImGui::OpenPopup("Material Type Configuration");
				s_B__ObjectSettingsPanel3D_Object3D_openMaterialTypeConfigurationDialogBox = false;
			}

			if (ImGui::BeginPopupModal("Material Type Configuration", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				if (ImGui::BeginCombo("Material Types", c_CPTR__ObjectSettingsPanel3D_Object3D_materialTypeOptions[s_I__ObjectSettingsPanel3D_Object3D_selectedMaterial3DIndex]))
				{
					for (int n = 0; n < IM_ARRAYSIZE(c_CPTR__ObjectSettingsPanel3D_Object3D_materialTypeOptions); n++)
					{
						bool b_ObjectSettingsPanel3D_Object3D_isMaterialSelected = (s_I__ObjectSettingsPanel3D_Object3D_selectedMaterial3DIndex == n);
						if (ImGui::Selectable(c_CPTR__ObjectSettingsPanel3D_Object3D_materialTypeOptions[n], b_ObjectSettingsPanel3D_Object3D_isMaterialSelected))
							s_I__ObjectSettingsPanel3D_Object3D_selectedMaterial3DIndex = n;

						if (b_ObjectSettingsPanel3D_Object3D_isMaterialSelected == true)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

				// Check if we exceed the material limit
				if (
					m_Materials.size() > s_CE_ui__ObjectSettingsPanel3D_Object3D_MAX_CUSTOM_TEXTURE_MATERIALS_PER_WORLD_LIMIT ||
					m_Materials.size() > s_CE_uI__ObjectSettingsPanel3D_Object3D_MAX_TEXTURES_MATERIALS_PER_WORLD_LIMIT || m_Materials.size() >
					s_CE_uI__ObjectSettingsPanel3D_Object3D_MAX_OVERALL_TEXTURE_MATERIALS_PER_WORLD_LIMIT
					)
				{
					if (s_B__ObjectSettingsPanel3D_Object3D_openMaxNormalTextureMaterialsReachedPerWorld_SS3DERROR_DialogBox == true)
					{
						ImGui::OpenPopup("Surreal Studio (3D) Error - [OBJECT SETTINGS PANEL] Max amount of Texture Materials reached per World");
						s_B__ObjectSettingsPanel3D_Object3D_openMaxNormalTextureMaterialsReachedPerWorld_SS3DERROR_DialogBox = false;
					}

					if (s_B__ObjectSettingsPanel3D_Object3D_openMaxCustomTextureMaterialsReachedPerWorld_SS3DERROR_DialogBox == true)
					{
						ImGui::OpenPopup("Surreal Studio (3D) Error - [OBJECT SETTINGS PANEL] Max amount of Custom Texture Materials reached Per World");
						s_B__ObjectSettingsPanel3D_Object3D_openMaxCustomTextureMaterialsReachedPerWorld_SS3DERROR_DialogBox = false;
					}

					if (s_B__ObjectSettingsPanel3D_Object3D_openMaxOverallTextureMaterialsReachedPerWorld_SS3DERROR_DialogBox == true)
					{
						ImGui::OpenPopup("Surreal Studio (3D) Error - [OBJECT SETTINGS PANEL] Max amount of Materials reached per World");
						s_B__ObjectSettingsPanel3D_Object3D_openMaxOverallTextureMaterialsReachedPerWorld_SS3DERROR_DialogBox = false;
					}

					if (ImGui::BeginPopupModal("Surreal Studio (3D) Error - [OBJECT SETTINGS PANEL] Max amount of Texture Materials reached per World", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text(
							"[OBJECT SETTINGS PANEL] Max amount of Texture Materials per World is %d, got more.", s_CE_uI__ObjectSettingsPanel3D_Object3D_MAX_TEXTURES_MATERIALS_PER_WORLD_LIMIT
						);

						if (ImGui::Button("OK")) {
							ImGui::CloseCurrentPopup();
							// We cant resize, so we'll leave it as is, this is a prototype anyways
							s_B__ObjectSettingsPanel3D_Object3D_openMaxNormalTextureMaterialsReachedPerWorld_SS3DERROR_DialogBox = true; // Reset
						}
						ImGui::EndPopup();
					}

					if (ImGui::BeginPopupModal("Surreal Studio (3D) Error - [OBJECT SETTINGS PANEL] Max amount of Custom Texture Materials reached per World", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text(
							"[OBJECT SETTINGS PANEL] Max amount of Custom Texture Materials per World is %d, got more.", s_CE_uI__ObjectSettingsPanel3D_Object3D_MAX_TEXTURES_MATERIALS_PER_WORLD_LIMIT
						);

						if (ImGui::Button("OK")) {
							ImGui::CloseCurrentPopup();
							// We cant resize, so we'll leave it as is, this is a prototype anyways
							s_B__ObjectSettingsPanel3D_Object3D_openMaxCustomTextureMaterialsReachedPerWorld_SS3DERROR_DialogBox = true; // Reset
						}
						ImGui::EndPopup();
					}

					if (ImGui::BeginPopupModal("Surreal Studio (3D) Error - [OBJECT SETTINGS PANEL] Max amount of Materials reached per World", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text(
							"[OBJECT SETTINGS PANEL] Max amount of Materials per World is %d, got more.", s_CE_uI__ObjectSettingsPanel3D_Object3D_MAX_TEXTURES_MATERIALS_PER_WORLD_LIMIT
						);

						if (ImGui::Button("OK")) {
							ImGui::CloseCurrentPopup();
							m_Materials.resize(s_CE_uI__ObjectSettingsPanel3D_Object3D_MAX_OVERALL_TEXTURE_MATERIALS_PER_WORLD_LIMIT);
							s_B__ObjectSettingsPanel3D_Object3D_openMaxOverallTextureMaterialsReachedPerWorld_SS3DERROR_DialogBox = true; // Reset
						}
						ImGui::EndPopup();
					}
				}
				ImGui::Spacing();
				ImGui::Separator();

				if (ImGui::Button("Apply")) 
				{
					ImGui::CloseCurrentPopup();

					switch (s_I__ObjectSettingsPanel3D_Object3D_selectedMaterial3DIndex)
					{
						case 0:
						{
							m_Material->ENUM_INSTANCE__MaterialType_DETAILS = Material3D::MaterialType::ColorMaterial; 

							m_Material->materialName = "Untitled Material 1";
							m_Material->materialID = static_cast<int>(m_Materials.size()) + 1;
							break;
						}
						case 1: 
						{ 
							m_Material->ENUM_INSTANCE__MaterialType_DETAILS = Material3D::MaterialType::TextureMaterial;

							m_Material->materialName = "Untitled Material 1";
							m_Material->materialID = static_cast<int>(m_Materials.size()) + 1;
							break;
						}
						case 2:
						{
							m_Material->ENUM_INSTANCE__MaterialType_DETAILS = Material3D::MaterialType::CustomMaterial;

							m_Material->materialName = "Untitled Material 1";
							m_Material->materialID = static_cast<int>(m_Materials.size()) + 1;
							break;
						}
					}
				 }

				ImGui::SameLine();
				if (ImGui::Button("Cancel")) {
					ImGui::CloseCurrentPopup();
				}
			}

			return true;
		}

		bool ObjectSettingsPanel3D::ObjectSettingsPanel3D_DrawExtraObjectProperties(const char* extraObject3D_options[], int index)
		{
			if (!extraObject3D_options || index < 0 || index >= static_cast<int>(m_ExtraObjects.size()))
				return false;
			
			ExtraObject3D* STRUCT_INSTANCE__ObjectSettingsPanel3D_ExtraObject3D_extraObject3D = m_ExtraObjects[index].get();
			if (!STRUCT_INSTANCE__ObjectSettingsPanel3D_ExtraObject3D_extraObject3D)
				return false;

			// Variables required for this function
			static int s_I__ObjectSettingsPanel3D_ExtraObject3D_selectedExtraObject3DIndex = index;  // Indexes: 0, 1, 2, 3

			// FOR INDEX 2 ONLY (OR INDICE IN IMGUI SENSE)
			static constexpr unsigned int s_CE_uI__ObjectSettingsPanel3D_ExtraObject3D_TriggerObject3D_MAX_EXTRA_OBJECT_3D_TRIGGER_OBJECTS_REACHED_PER_WORLD_LIMIT = 100;
			static int s_I__ObjectSettingsPanel3D_ExtraObject3D_TriggerObject3D_selectedExtraObject3DTriggerObject3DIndex = 0;	
			const char* c_CPTR__ObjectSettingsPanel3D_ExtraObject3D_TriggerObject3D_triggerObject3D_TriggerOptions[] = {  // TODO: "Borrow" some trigger names from Geometry Dash
				"Move Trigger"
			};
			static bool s_B__ObjectSettingsPanel3D_ExtraObject3D_TriggerObject3D_openMaxExtraObject3D_TriggerObject3DReachedPerWorldLimit_SS3DERROR_DialogBox = true;
			static bool s_B__ObjectSettingsPanel3D_ExtraObject3D_openPlayerObjectHasNoScriptAttachedToItYetForInteractableObjectsToFunction_SS3DWARNING_DialogBox = true;
			
			if (ImGui::CollapsingHeader("Extra Object Properties"))
			{
				// Properties for Player Object of ExtraObgject
				if (s_I__ObjectSettingsPanel3D_ExtraObject3D_selectedExtraObject3DIndex == 0)
				{

					ImGui::Text("%s Properties [EXTRA OBJECT PROPERTIES]", extraObject3D_options[s_I__ObjectSettingsPanel3D_ExtraObject3D_selectedExtraObject3DIndex]);

					ImGui::Checkbox("Show Player", &STRUCT_INSTANCE__ObjectSettingsPanel3D_ExtraObject3D_extraObject3D->b_showPlayerObjectFlag);

					if (ImGui::CollapsingHeader("Transform"))
					{
						ImGui::DragFloat3("Position", &STRUCT_INSTANCE__ObjectSettingsPanel3D_ExtraObject3D_extraObject3D->STRUCT_INSTANCE__Transform3D_transform.objectPosition[0], 0.1f);
						ImGui::DragFloat3("Rotation", &STRUCT_INSTANCE__ObjectSettingsPanel3D_ExtraObject3D_extraObject3D->STRUCT_INSTANCE__Transform3D_transform.objectRotation[0], 0.1f);
						ImGui::DragFloat3("Scale", &STRUCT_INSTANCE__ObjectSettingsPanel3D_ExtraObject3D_extraObject3D->STRUCT_INSTANCE__Transform3D_transform.objectScale[0], 0.1f);
					}

					if (ImGui::Button("Attach Script to Player Object"))
					{
						STRUCT_INSTANCE__ObjectSettingsPanel3D_ExtraObject3D_extraObject3D->b_showIfPlayerObjectHasScriptAttachedFlag = true;
						// TODO: Show the Windows dialog box with .py files or something
					}
				}
				else if (s_I__ObjectSettingsPanel3D_ExtraObject3D_selectedExtraObject3DIndex == 1)
				{
					ImGui::Text("%s Properties [EXTRA OBJECT PROPERTIES]", extraObject3D_options[s_I__ObjectSettingsPanel3D_ExtraObject3D_selectedExtraObject3DIndex]);

					ImGui::DragFloat("Health", &STRUCT_INSTANCE__ObjectSettingsPanel3D_ExtraObject3D_extraObject3D->STRUCT_INSTANCE__HealthObject3D_healthObject.f_Health);
					if (ImGui::Button("Attach Health Object to Player Object"))
					{
						STRUCT_INSTANCE__ObjectSettingsPanel3D_ExtraObject3D_extraObject3D->STRUCT_INSTANCE__HealthObject3D_healthObject.b_IsHealthObjectAttachedToPlayerObject = true;
						// TODO: Update Scene Hierarchy Panel with this
					}
				}
				else if (s_I__ObjectSettingsPanel3D_ExtraObject3D_selectedExtraObject3DIndex == 2)
				{
					ImGui::Text("%s Properties [EXTRA OBJECT PROPERTIES]", extraObject3D_options[s_I__ObjectSettingsPanel3D_ExtraObject3D_selectedExtraObject3DIndex]);

					if (
						ImGui::BeginCombo("Trigger Object Types", c_CPTR__ObjectSettingsPanel3D_ExtraObject3D_TriggerObject3D_triggerObject3D_TriggerOptions
							[s_I__ObjectSettingsPanel3D_ExtraObject3D_TriggerObject3D_selectedExtraObject3DTriggerObject3DIndex])
						)
					{
						for (int n = 0; n < IM_ARRAYSIZE(c_CPTR__ObjectSettingsPanel3D_ExtraObject3D_TriggerObject3D_triggerObject3D_TriggerOptions); n++)
						{
							bool b_ObjectSettingsPanel3D_ExtraObject3D_TriggerObject3D_isTriggerObjectTypeSelected = (s_I__ObjectSettingsPanel3D_ExtraObject3D_TriggerObject3D_selectedExtraObject3DTriggerObject3DIndex == n);
							if (ImGui::Selectable(c_CPTR__ObjectSettingsPanel3D_ExtraObject3D_TriggerObject3D_triggerObject3D_TriggerOptions[n], b_ObjectSettingsPanel3D_ExtraObject3D_TriggerObject3D_isTriggerObjectTypeSelected))
								s_I__ObjectSettingsPanel3D_ExtraObject3D_selectedExtraObject3DIndex = n;

							if (b_ObjectSettingsPanel3D_ExtraObject3D_TriggerObject3D_isTriggerObjectTypeSelected == true)
								ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					if (
						STRUCT_INSTANCE__ObjectSettingsPanel3D_ExtraObject3D_extraObject3D->triggerObject3D.size() >
						s_CE_uI__ObjectSettingsPanel3D_ExtraObject3D_TriggerObject3D_MAX_EXTRA_OBJECT_3D_TRIGGER_OBJECTS_REACHED_PER_WORLD_LIMIT &&
						s_B__ObjectSettingsPanel3D_ExtraObject3D_TriggerObject3D_openMaxExtraObject3D_TriggerObject3DReachedPerWorldLimit_SS3DERROR_DialogBox == true
						)
					{
						ImGui::OpenPopup("Surreal Studio (3D) Error [OBJECT SETTINGS PANEL - EXTRA OBJECTS (TRIGGER OBJECT)] Max amount of Trigger Objects reached per World");
						s_B__ObjectSettingsPanel3D_ExtraObject3D_TriggerObject3D_openMaxExtraObject3D_TriggerObject3DReachedPerWorldLimit_SS3DERROR_DialogBox = false;
					}

					if (ImGui::BeginPopupModal("Surreal Studio (3D) Error [OBJECT SETTINGS PANEL - EXTRA OBJECTS (TRIGGER OBJECT)] Max amount of Trigger Objects reached per World", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text(
							"[OBJECT SETTINGS PANEL - EXTRA OBJECTS (TRIGGER OBJECT)] Max amount of Trigger Objects per World is %d, got %d.",
							s_CE_uI__ObjectSettingsPanel3D_ExtraObject3D_TriggerObject3D_MAX_EXTRA_OBJECT_3D_TRIGGER_OBJECTS_REACHED_PER_WORLD_LIMIT,
							static_cast<int>(STRUCT_INSTANCE__ObjectSettingsPanel3D_ExtraObject3D_extraObject3D->triggerObject3D.size())
						);

						if (ImGui::Button("OK")) {
							ImGui::CloseCurrentPopup();
							STRUCT_INSTANCE__ObjectSettingsPanel3D_ExtraObject3D_extraObject3D->triggerObject3D.resize(
								s_CE_uI__ObjectSettingsPanel3D_ExtraObject3D_TriggerObject3D_MAX_EXTRA_OBJECT_3D_TRIGGER_OBJECTS_REACHED_PER_WORLD_LIMIT
							);  // Clamp to max limit

							s_B__ObjectSettingsPanel3D_ExtraObject3D_TriggerObject3D_openMaxExtraObject3D_TriggerObject3DReachedPerWorldLimit_SS3DERROR_DialogBox = true; // Reset
						}
						ImGui::EndPopup();
					}
				}
				else if (s_I__ObjectSettingsPanel3D_ExtraObject3D_selectedExtraObject3DIndex == 3)
				{
					if (STRUCT_INSTANCE__ObjectSettingsPanel3D_ExtraObject3D_extraObject3D->b_showIfPlayerObjectHasScriptAttachedFlag == false)
					{
						if (s_B__ObjectSettingsPanel3D_ExtraObject3D_openPlayerObjectHasNoScriptAttachedToItYetForInteractableObjectsToFunction_SS3DWARNING_DialogBox == true)
						{
							ImGui::Text("Surreal Studio (3D) Error - [OBJECT SETTINGS PANEL - EXTRA OBJECT] Player Object has no script fttached for Interactable Objects to function");
							s_B__ObjectSettingsPanel3D_ExtraObject3D_openPlayerObjectHasNoScriptAttachedToItYetForInteractableObjectsToFunction_SS3DWARNING_DialogBox = false;
						}

						if (ImGui::BeginPopupModal("Surreal Studio (3D) Error - [OBJECT SETTINGS PANEL - EXTRA OBJECT] Player Object has no script attached for Interactable Objects to function", nullptr,
							ImGuiWindowFlags_AlwaysAutoResize))
						{
							ImGui::Text("[OBJECT SETTINGS PANEL - EXTRA OBJECTS] WARNING - Player Object has no script attached to it that the Interactable Object can use to function. Please implement it.");
							if (ImGui::Button("OK")) {
								ImGui::CloseCurrentPopup();
							}
							ImGui::CloseCurrentPopup();
						}
						// We add this function here, so we have an actual Object that can be interacted with.
						// So, we, by default, have a engine prefab to be a Interactable Object. Importing can also be done here.
						ObjectSettingsPanel3D_DrawObjectCreation();  // Shows the function to create an object, though its not really needed here IG
						// In conclusion: This function is needed so an Object (by default, an engine prefab) can be a interacted with.

					}
				}
			}

			return true;
		}

		bool ObjectSettingsPanel3D::ObjectSettingsPanel3D_DrawObjectCreation()
		{
			if (m_Objects.empty())
				m_Objects.push_back(std::make_unique<Object3D>());

			if (m_ExtraObjects.empty())
				m_ExtraObjects.push_back(std::make_unique<ExtraObject3D>());

			if (m_Materials.empty())
				m_Materials.push_back(std::make_unique<Material3D>());

			if (m_Meshses.empty())
				m_Meshses.push_back(std::make_unique<Mesh3D>());

			static constexpr unsigned int s_CE_uI__ObjectSettingsPanel3D_MAX_OBJECTS_PER_WORLD_LIMIT = 2500;

			// Selection indices (DEAR IMGUI SPECIFIC)
			static int s_I__ObjectSettingsPanel3D_selectedObject3DIndex = 0;
			static int s_I__ObjectSettingsPanel3D_selectedObject3DMesh3DIndex = 0;

			// Popup flags (DEAR IMGUI SPECIFIC)
			static bool s_B__ObjectSettingsPanel3D_openMeshTypeConfigurationDialogBox = false;
			static bool s_B__ObjectSettingsPanel3D_openMaxObjectsReachedPerWorldLimit_SS3DERROR_DialogBox = true;
			
			const char* c_CPTR__ObjectSettingsPanel3D_object3DOptions[] = {
				"Cube Object", "Sphere Object", "Capsule Object", "Cylinder Object",
				"Cone Object", "Torus/Dount Object", "Plane Object"
			};
			const char* c_CPTR__ObjectSettingsPanel3D_MeshTypeConfigurationDialogBox_meshTypeOptions[] = {
				"Static Mesh", "Skeletal Mesh", "Dynamic Mesh"
			};

			if (ImGui::CollapsingHeader("Objects"))
			{
				if (ImGui::BeginCombo("Object Types", c_CPTR__ObjectSettingsPanel3D_object3DOptions[s_I__ObjectSettingsPanel3D_selectedObject3DIndex]))
				{
					for (int n = 0; n < IM_ARRAYSIZE(c_CPTR__ObjectSettingsPanel3D_object3DOptions); n++)
					{
						bool b_ObjectSettingsPanel3D_isObjectSelected = (s_I__ObjectSettingsPanel3D_selectedObject3DIndex == n);
						if (ImGui::Selectable(c_CPTR__ObjectSettingsPanel3D_object3DOptions[n], b_ObjectSettingsPanel3D_isObjectSelected))
							s_I__ObjectSettingsPanel3D_selectedObject3DIndex = n;

						if (b_ObjectSettingsPanel3D_isObjectSelected == true)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

				if (m_Objects.size() > s_CE_uI__ObjectSettingsPanel3D_MAX_OBJECTS_PER_WORLD_LIMIT && s_B__ObjectSettingsPanel3D_openMaxObjectsReachedPerWorldLimit_SS3DERROR_DialogBox == true)
				{
					ImGui::OpenPopup("Surreal Studio (3D) Error - [OBJECT SETTINGS PANEL] Max amount of Objects reached");
					s_B__ObjectSettingsPanel3D_openMaxObjectsReachedPerWorldLimit_SS3DERROR_DialogBox = false;
				}

				if (ImGui::BeginPopupModal("Surreal Studio (3D) Error - [OBJECT SETTINGS PANEL] Max amount of Objects reached", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text(
						"[OBJECT SETTINGS PANEL] Max amount of Objects per World is %d got %d.", s_CE_uI__ObjectSettingsPanel3D_MAX_OBJECTS_PER_WORLD_LIMIT,
						static_cast<int>(m_Objects.size())
					);

					if (ImGui::Button("OK")) {
						ImGui::CloseCurrentPopup();
						m_Objects.resize(s_CE_uI__ObjectSettingsPanel3D_MAX_OBJECTS_PER_WORLD_LIMIT); // Clamp
						s_B__ObjectSettingsPanel3D_openMaxObjectsReachedPerWorldLimit_SS3DERROR_DialogBox = true; // Reset
					}
					ImGui::EndPopup();
				}

				if (ImGui::Button("Create new Object"))
				{
					m_Objects.push_back(std::make_unique<Object3D>());
					s_B__ObjectSettingsPanel3D_openMeshTypeConfigurationDialogBox = true; // Trigger Mesh Type Configuration Popup/dialog box
				}

				if (s_B__ObjectSettingsPanel3D_openMeshTypeConfigurationDialogBox == true)
				{
					ImGui::OpenPopup("Mesh Type Configuration");
					s_B__ObjectSettingsPanel3D_openMeshTypeConfigurationDialogBox = false;
				}

				if (ImGui::BeginPopupModal("Mesh Type Configuration", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					if (ImGui::BeginCombo("Mesh Type", c_CPTR__ObjectSettingsPanel3D_MeshTypeConfigurationDialogBox_meshTypeOptions[s_I__ObjectSettingsPanel3D_selectedObject3DMesh3DIndex]))
					{
						for (int n = 0; n < IM_ARRAYSIZE(c_CPTR__ObjectSettingsPanel3D_MeshTypeConfigurationDialogBox_meshTypeOptions); n++)
						{
							bool b_ObjectSettingsPanel3D_MeshTypeConfiguration_isMeshTypeSelected = (s_I__ObjectSettingsPanel3D_selectedObject3DMesh3DIndex == n);
							if (ImGui::Selectable(c_CPTR__ObjectSettingsPanel3D_MeshTypeConfigurationDialogBox_meshTypeOptions[n], b_ObjectSettingsPanel3D_MeshTypeConfiguration_isMeshTypeSelected))
								s_I__ObjectSettingsPanel3D_selectedObject3DMesh3DIndex = n;

							if (b_ObjectSettingsPanel3D_MeshTypeConfiguration_isMeshTypeSelected == true)
								ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}
					ImGui::Spacing();

					if (ImGui::Button("Apply"))
					{
						ImGui::CloseCurrentPopup();

						switch (s_I__ObjectSettingsPanel3D_selectedObject3DMesh3DIndex)
						{
						case 0: m_Meshses[0]->ENUM_INSTANCE__MeshType_DETAILS = Mesh3D::MeshType::StaticMesh; break;
						case 1: m_Meshses[0]->ENUM_INSTANCE__MeshType_DETAILS = Mesh3D::MeshType::SkeletalMesh; break;
						case 2: m_Meshses[0]->ENUM_INSTANCE__MeshType_DETAILS = Mesh3D::MeshType::DynamicMesh; break;
						}
					}

					ImGui::SameLine();
					if (ImGui::Button("Cancel")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}

				switch (s_I__ObjectSettingsPanel3D_selectedObject3DIndex)
				{
				case 0: m_Objects[0]->ENUM_INSTANCE__ObjectSettingsPanel3D_Object3D_Objec3DType_DETAILS = Object3D::Object3D_Object3DType::CubeObject; break;
				case 1: m_Objects[0]->ENUM_INSTANCE__ObjectSettingsPanel3D_Object3D_Objec3DType_DETAILS = Object3D::Object3D_Object3DType::SphereObject; break;
				case 2: m_Objects[0]->ENUM_INSTANCE__ObjectSettingsPanel3D_Object3D_Objec3DType_DETAILS = Object3D::Object3D_Object3DType::CapsuleObject; break;
				case 3: m_Objects[0]->ENUM_INSTANCE__ObjectSettingsPanel3D_Object3D_Objec3DType_DETAILS = Object3D::Object3D_Object3DType::CylinderObject; break;
				case 4: m_Objects[0]->ENUM_INSTANCE__ObjectSettingsPanel3D_Object3D_Objec3DType_DETAILS = Object3D::Object3D_Object3DType::ConeObject; break;
				case 5: m_Objects[0]->ENUM_INSTANCE__ObjectSettingsPanel3D_Object3D_Objec3DType_DETAILS = Object3D::Object3D_Object3DType::DountObject; break;
				case 6: m_Objects[0]->ENUM_INSTANCE__ObjectSettingsPanel3D_Object3D_Objec3DType_DETAILS = Object3D::Object3D_Object3DType::PlaneObject; break;
				}
			}

			return true;
		}

		bool ObjectSettingsPanel3D::ObjectSettingsPanel3D_DrawObjectExtraCreation()
		{
			if (m_Objects.empty())
				m_Objects.push_back(std::make_unique<Object3D>());

			if (m_ExtraObjects.empty())
				m_ExtraObjects.push_back(std::make_unique<ExtraObject3D>());

			if (m_Materials.empty())
				m_Materials.push_back(std::make_unique<Material3D>());

			if (m_Meshses.empty())
				m_Meshses.push_back(std::make_unique<Mesh3D>());

			static constexpr unsigned int s_CE_uI__ObjectSettingsPanel3D_ExtraObject3D_MAX_EXTRA_OBJECTS_REACHED_PER_WORLD_LIMIT = 250;
			static int s_I__ObjectSettingsPanel3D_ExtraObject3D_selectedExtraObject3DIndex = 0;
			const char* c_CPTR__ObjectSettingsPanel3D_ExtraObject3D_extraObject3D_Options[] = {
				"Player Object", "Health Object", "Trigger Object", "Interactable Object"
			};
			static bool s_B__ObjectSettingsPanel3D_ExtraObject3D_openMaxExtraObjectsReachedPerWorldLimit_SS3DERROR_DialogBox = true;

			if (ImGui::CollapsingHeader("Extra Objects"))
			{
				if (ImGui::BeginCombo("Extra Object Type", c_CPTR__ObjectSettingsPanel3D_ExtraObject3D_extraObject3D_Options[s_I__ObjectSettingsPanel3D_ExtraObject3D_selectedExtraObject3DIndex]))
				{
					for (int n = 0; n < IM_ARRAYSIZE(c_CPTR__ObjectSettingsPanel3D_ExtraObject3D_extraObject3D_Options); n++)
					{
						bool b_ObjectSettingsPanel3D_ExtraObject3D_isExtraObject3DSelected = (s_I__ObjectSettingsPanel3D_ExtraObject3D_selectedExtraObject3DIndex == n);
						if (ImGui::Selectable(c_CPTR__ObjectSettingsPanel3D_ExtraObject3D_extraObject3D_Options[n], b_ObjectSettingsPanel3D_ExtraObject3D_isExtraObject3DSelected))
							s_I__ObjectSettingsPanel3D_ExtraObject3D_selectedExtraObject3DIndex = n;

						if (b_ObjectSettingsPanel3D_ExtraObject3D_isExtraObject3DSelected == true)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();

					if (
						m_Objects.size() < s_CE_uI__ObjectSettingsPanel3D_ExtraObject3D_MAX_EXTRA_OBJECTS_REACHED_PER_WORLD_LIMIT &&
						s_B__ObjectSettingsPanel3D_ExtraObject3D_openMaxExtraObjectsReachedPerWorldLimit_SS3DERROR_DialogBox == true
						)
					{
						ImGui::OpenPopup("Surreal Studio (3D) Error - [OBJECT SETTINGS PANEL] Max amount of Extra Objects reached per World");
						s_B__ObjectSettingsPanel3D_ExtraObject3D_openMaxExtraObjectsReachedPerWorldLimit_SS3DERROR_DialogBox = false;
					}

					if (ImGui::BeginPopupModal("Surreal Studio (3D) Error - [OBJECT SETTINGS PANEL] Max amount of Extra Objects reached per World", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text(
							"[OBJECT SETTINGS PANEL] Max amount of Extra Objects per World is %d, got %d.", s_CE_uI__ObjectSettingsPanel3D_ExtraObject3D_MAX_EXTRA_OBJECTS_REACHED_PER_WORLD_LIMIT,
							static_cast<int>(m_ExtraObjects.size())
						);

						if (ImGui::Button("OK")) {
							ImGui::CloseCurrentPopup();
							m_ExtraObjects.resize(s_CE_uI__ObjectSettingsPanel3D_ExtraObject3D_MAX_EXTRA_OBJECTS_REACHED_PER_WORLD_LIMIT); // Clamp to max limit
							s_B__ObjectSettingsPanel3D_ExtraObject3D_openMaxExtraObjectsReachedPerWorldLimit_SS3DERROR_DialogBox = true;  // Reset so if it happens again, this popup will trigger
						}
						ImGui::EndPopup();
					}

					if (ImGui::Button("Create Extra Object")) 
					{
						if (
							m_ExtraObjects.size() < s_CE_uI__ObjectSettingsPanel3D_ExtraObject3D_MAX_EXTRA_OBJECTS_REACHED_PER_WORLD_LIMIT && !
							s_B__ObjectSettingsPanel3D_ExtraObject3D_openMaxExtraObjectsReachedPerWorldLimit_SS3DERROR_DialogBox
							)
						{
							m_ExtraObjects.push_back(std::make_unique<ExtraObject3D>());
						}
						else;  // LOL
					}
				}
			}

			return true;
		}

		bool ObjectSettingsPanel3D::ObjectSettingsPanel3D_DrawObjectSettingsPanel3D()
		{
			ImGui::Begin("Object Settings Panel");

			try { ObjectSettingsPanel3D_DrawObjectCreation(); }
			catch (const std::exception& e) {
				SS3D_ERROR(e.what()); return false;
			}
			catch (...) { SS3D_ERROR("Some unknown exception occurred!"); return false; }

			try { ObjectSettingsPanel3D_DrawObjectExtraCreation(); }
			catch (const std::exception& e) {
				SS3D_ERROR(e.what()); return false;
			}
			catch (...) { SS3D_ERROR("Some unknown exception occurred!"); return false; }

			ImGui::End();

			return true;
		}
	}
}