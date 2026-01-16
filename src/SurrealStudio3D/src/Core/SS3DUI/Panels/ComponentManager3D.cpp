#include "ComponentManagerPanel3D.h"

#include "../src/SurrealStudio3D/src/Core/ECS/Component3D.h"
#include "../src/SurrealStudio3D/src/Core/ECS/Object3D.h"
#include "../src/SurrealStudio3D/src/SS3DEngineDefines.h"

#include <imgui.h>
#include <stdexcept>
#include <imgui_stdlib.h>

namespace SurrealStudio {

	namespace SurrealStudio3D {

		bool ComponentManagerPanel3D::DrawComponentCreation()
		{
			// Variables needed for this  function
			static constexpr uint32_t s_CE_uI_MAX_COMPONENTS_PER_WORLD = 10000;
			static int s_I_selectedComponentIndex = 0;
			const char* c_CPTR_componentOptions[] = {
				"Transform Component", "Position Component", "Velocity Component",
				"Mesh Component", "Physics Component", "Light Component",
				"Camera Component", "Asset Component"
			};
			static bool s_B_openMaxComponentsReachedPerWorld_SS3DERROR_DialogBox = true;

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// TODO: Make sure to add a dialog or whatever to choose an Object so a new Component can be created
			// Also, add the underlying logic in the engine system
			// Add a DoesComponentHaveObjectSelected_OrIsComponentAChildOfSelectedObject() const noexcept function to identify whether
			// a component is a child of an Object
			// Then, using that function, open a dialog forcing the user to select an Object if DoesComponentHaveObjectSelected_OrIsComponentAChildOfSelectedObject returns false, otherwise
			// dont show the dialog
			// If all that is a sucess, exit the dialog and then only show the properties and creation
			// Note: Add this as a function in ComponentManagerPanel3D and in DrawComponentManagerPanel3D() function, add this at the first like:
			/*
			try
			{
				if (!AskUserToSelectObject_DialogBox())  // Starting function name
				{ return false; }
			}
			catch (const std::exception& e)
			{
				SS3D_ERROR(e.what(); return false;
			}
			catch (...) { SS3D_ERROR("Some unknown exception occurred!"); return false; }
			*/
			// To better enforce this rule in the engine
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			if (ImGui::CollapsingHeader("Component Creation"))
			{
				if (ImGui::BeginCombo("Component Types", c_CPTR_componentOptions[s_I_selectedComponentIndex]))
				{
					for (int n = 0; n < IM_ARRAYSIZE(c_CPTR_componentOptions); n++)
					{
						bool b_isComponentSelected = (s_I_selectedComponentIndex == n);
						if (ImGui::Selectable(c_CPTR_componentOptions[n], b_isComponentSelected))
							s_I_selectedComponentIndex = n;

						if (b_isComponentSelected == true)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

				if (m_Components_ToIntegrateWithUI.size() > s_CE_uI_MAX_COMPONENTS_PER_WORLD && s_B_openMaxComponentsReachedPerWorld_SS3DERROR_DialogBox == true)
				{
					ImGui::OpenPopup("Surreal Studio (3D) Error - Max Components Reached per World");
					s_B_openMaxComponentsReachedPerWorld_SS3DERROR_DialogBox = false;
				}

				if (ImGui::BeginPopupModal("Surreal Studio (3D) Error - Max Components Reached per World", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text(
						"[COMPONENT MANAGER PANEL] Max Amount of Components per World is %d got %d.",
						s_CE_uI_MAX_COMPONENTS_PER_WORLD, static_cast<int>(m_Components_ToIntegrateWithUI.size())
					);

					if (ImGui::Button("OK")) {
						ImGui::CloseCurrentPopup();
						m_Components_ToIntegrateWithUI.resize(s_CE_uI_MAX_COMPONENTS_PER_WORLD); // Clamp  to max value
						s_B_openMaxComponentsReachedPerWorld_SS3DERROR_DialogBox = true; // Reset
					}
					ImGui::EndPopup();
				}

				if (m_Components_ToIntegrateWithUI.size() < s_CE_uI_MAX_COMPONENTS_PER_WORLD && !s_B_openMaxComponentsReachedPerWorld_SS3DERROR_DialogBox)
				{
					componentManager.AddComponent(m_Object_NeededForComponent, std::move(m_ComponentType));
				}

				DrawComponentProperties(c_CPTR_componentOptions, s_I_selectedComponentIndex);
			}
			return true;
		}

		bool ComponentManagerPanel3D::DrawComponentProperties(const char* componentOptions[], int index)
		{
			if (componentManager.m_Component == nullptr) {
				SS3D_ERROR("Variable componentManager.m_Component is null!");
				return false;
			}

			if (!componentOptions || index < 0 || index >= static_cast<int>(m_Components_ToIntegrateWithUI.size()))
				return false;

			ECS::Component3D* STRUCT_INSTANCE__ComponentManagerPanel_components = m_Components_ToIntegrateWithUI[index].get();
			if (!STRUCT_INSTANCE__ComponentManagerPanel_components)
				return false;

			// For Mesh Component
			static constexpr uint32_t s_CE_uI__MAX_MESH_COMPONENTS = 250;   // A Mesh Component is essentially just a mesh, and a MeshObject just has a MeshComponent
			static int s_I_selectedMeshComponentIndex = 0;
			const char* c_CPTR_meshComponentOptions[] = {
				"Static Mesh", "Skeletal Mesh", "Custom Mesh"
			};
			static bool s_B_openMaxMeshComponentsReached_SS3DERROR_DialogBox = true;

			// For Light Component
			static constexpr uint32_t s_CE_uI__MAX_LIGHT_COMPONENTS = 100;
			static int s_I_selectedLightComponentIndex = 0;
			const char* c_CPTR_lightComponent_TypeOptions[] = {
				"WorldEnvironmentLight", "SurrealAmbientLight",
				"SurrealPointLight", "SurrealSpotLight", "SurrealAreaLight",
				"SurrealEmissiveLight"
			};
			static bool s_B_openMaxLightComponentsReachedPerWorld_SS3DERROR_DialogBox = true;

			// For Camera Component
			static constexpr uint32_t s_CE_uI__MAX_CAMERA_COMPONENTS = 10;
			static int s_I_selectedCameraComponentIndex = 0;
			const char* c_CPTR_cameraComponent_TypeOptions[] = {
				"Normal", "Orthographic"
			};
			static bool s_B_openMaxCameraComponentsReachedPerWorld_SS3DERROR_DialogBox = true;

			// For Asset Component
			constexpr uint32_t MAX_OBJECTS = 2500;
			constexpr uint32_t EXPECTED_ASSETS_PER_OBJECTS = 4;
			constexpr uint32_t CE_uI_MAX_ASSETS_COMPONENTS_PER_WORLD = MAX_OBJECTS * EXPECTED_ASSETS_PER_OBJECTS;
			static int s_I_selectedAssetComponentIndex = 0;
			const char* c_CPTR_assetComponentTypeOptions[] = {
				"Mesh"
			};
			static bool s_B_openMaxAssetComponentsReachedPerWorld_SS3DERROR_DialogBox = true;
			const char* c_CPTR_assetComponentLoadStateOptions[] = {
				"Unloaded", "Loading", "Loaded", "Failed"
			};
			static int s_I_selectedAssetComponentLoadStateOptionsIndex = 0;

			if (ImGui::CollapsingHeader("Component Properties"))
			{
				if (index == 0)
				{
					ImGui::Text("%s Properties", componentOptions[index]);

					// Transform component properties
					ImGui::DragFloat3("Position", &STRUCT_INSTANCE__ComponentManagerPanel_components->transformComponent.position[0], 0.1f);
					ImGui::DragFloat3("Rotation", &STRUCT_INSTANCE__ComponentManagerPanel_components->transformComponent.rotation[0], 0.1f);
					ImGui::DragFloat3("Scale", &STRUCT_INSTANCE__ComponentManagerPanel_components->transformComponent.scale[0], 0.1f);
				}
				else if (index == 1)
				{
					ImGui::Text("%s Properties", componentOptions[index]);

					// Position Component properties
					ImGui::DragFloat3("Position", &STRUCT_INSTANCE__ComponentManagerPanel_components->transformComponent.position[0], 0.1f);
				}
				else if (index == 2)
				{
					// Velocity Component properties
					ImGui::Text("%s Properties", componentOptions[index]);
					ImGui::DragFloat3("Velocity:", &STRUCT_INSTANCE__ComponentManagerPanel_components->velocityComponent.velocity[0], 0.1f);
				}
				else if (index == 3)
				{
					// Mesh Component properties
					ImGui::Text("%s Properties", componentOptions[index]);
					
					if (ImGui::BeginCombo("Mesh Types", c_CPTR_meshComponentOptions[s_I_selectedMeshComponentIndex]))
					{
						for (int n = 0; n < IM_ARRAYSIZE(c_CPTR_meshComponentOptions); n++)
						{
							bool b_IsMeshComponentTypeSelected = (s_I_selectedMeshComponentIndex == n);
							if (ImGui::Selectable(c_CPTR_meshComponentOptions[n], b_IsMeshComponentTypeSelected))
								s_I_selectedMeshComponentIndex = n;

							if (b_IsMeshComponentTypeSelected == true)
								ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					if (componentManager.m_Component->meshComponentVector.size() > s_CE_uI__MAX_MESH_COMPONENTS && s_B_openMaxMeshComponentsReached_SS3DERROR_DialogBox == true)
					{
						ImGui::OpenPopup("Surreal Studio (3D) Error - [COMPONENT MANAGER PANEL] Max Mesh Components Reached Per World");
						s_B_openMaxMeshComponentsReached_SS3DERROR_DialogBox = false;
					}

					if (
						ImGui::BeginPopupModal("Surreal Studio (3D) Error - [COMPONENT MANAGER PANEL] Max Mesh Components Reached Per World", nullptr, 
							ImGuiWindowFlags_AlwaysAutoResize
					))
					{
						ImGui::Text("[COMPONENT MANAGER PANEL] Max amount of Mesh Components is %d, got %d.",
							s_CE_uI__MAX_MESH_COMPONENTS, static_cast<int>(componentManager.m_Component->meshComponentVector.size())
						);

						if (ImGui::Button("OK")) {
							ImGui::CloseCurrentPopup();
							componentManager.m_Component->meshComponentVector.resize(s_CE_uI__MAX_MESH_COMPONENTS); // Clamp to max value forcefully
							s_B_openMaxMeshComponentsReached_SS3DERROR_DialogBox = true; // Reset
						}
						ImGui::EndPopup();
					}

					if (s_I_selectedMeshComponentIndex == 0)
					{
						componentManager.m_Component->meshComponent.meshType = ECS::MeshComponent::MeshType::StaticMesh;
					}
					else if (s_I_selectedMeshComponentIndex == 1)
					{
						componentManager.m_Component->meshComponent.meshType = ECS::MeshComponent::MeshType::SkeletalMesh;
					}
					else if (s_I_selectedMeshComponentIndex == 2)
					{
						componentManager.m_Component->meshComponent.meshType = ECS::MeshComponent::MeshType::CustomMesh;
					}

					ImGui::Spacing();
					ImGui::Text("Current Mesh Component Type: %s", c_CPTR_meshComponentOptions[s_I_selectedMeshComponentIndex]);
				}
				else if (index == 4)
				{
					// Physics Component Properties
					ImGui::Text("%s Properties ", componentOptions[index]);

					ImGui::DragFloat("Mass", &componentManager.m_Component->physicsComponent.mass, 1.0f);
					ImGui::DragFloat3("Velocity", &componentManager.m_Component->physicsComponent.velocity[0], 1.0f);
					ImGui::DragFloat3("Angular Velocity", &componentManager.m_Component->physicsComponent.angularVelocity[0], 1.0f);
					ImGui::DragFloat3("Scale Velocity", &componentManager.m_Component->physicsComponent.scaleVelocity[0], 1.0f);
					
					if (ImGui::Checkbox("Is Kinematic", &componentManager.m_Component->physicsComponent.isKinematic))
					{
						// TODO: Integrate with the Physics System and set make the Component kinematic.
					}
				}
				else if (index == 5)
				{
					// Light Component Properties
					ImGui::Text("%s Properties", componentOptions[index]);

					// Set a unique light ID/Index
					componentManager.m_Component->lightComponent.lightIndex =
						static_cast<int>(componentManager.m_Component->lightComponentVector.size()) + 1;

					if (ImGui::BeginCombo("Light Component Types", c_CPTR_lightComponent_TypeOptions
						[s_I_selectedLightComponentIndex]))
					{
						for (int n = 0; n < IM_ARRAYSIZE(c_CPTR_lightComponent_TypeOptions); n++)
						{
							bool b_IsLightComponentSelected = (s_I_selectedLightComponentIndex == n);
							if (ImGui::Selectable(c_CPTR_lightComponent_TypeOptions[n], b_IsLightComponentSelected))
								s_I_selectedLightComponentIndex = n;

							if (b_IsLightComponentSelected == true)
								ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					if (
						componentManager.m_Component->lightComponentVector.size() > s_CE_uI__MAX_LIGHT_COMPONENTS &&
						s_B_openMaxLightComponentsReachedPerWorld_SS3DERROR_DialogBox == true
						)
					{
						ImGui::OpenPopup("Surreal Studio (3D) Error - [COMPONENT MANAGER PANEL] Max amount of Light Components Reached Per World");

						s_B_openMaxLightComponentsReachedPerWorld_SS3DERROR_DialogBox = false;
					}

					if (ImGui::BeginPopupModal(
						"Surreal Studio (3D) Error - [COMPONENT MANAGER PANEL] Max amount of Light Components Reached Per World",
						nullptr, ImGuiWindowFlags_AlwaysAutoResize
					))
					{
						ImGui::Text("[COMPONENT MANAGER PANEL] Max amount of Light Components per World is %d, got %d.",
							s_CE_uI__MAX_LIGHT_COMPONENTS, static_cast<int>(
								componentManager.m_Component->lightComponentVector.size()
								));

						if (ImGui::Button("OK")) {
							ImGui::CloseCurrentPopup();
							componentManager.m_Component->lightComponentVector.resize(s_CE_uI__MAX_LIGHT_COMPONENTS); // Clamp
							s_B_openMaxLightComponentsReachedPerWorld_SS3DERROR_DialogBox = true; // Reset
						}
						ImGui::EndPopup();
					}

					if (s_I_selectedLightComponentIndex == 0)
					{
						componentManager.m_Component->
							lightComponent.STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightingType_DETAILS =
							ECS::LightComponent::WorldCanvas_WorldCanvas_Lighting2D_LightingType::WorldEnvironmentLight;
					}
					else if (s_I_selectedLightComponentIndex == 1)
					{
						componentManager.m_Component->
							lightComponent.STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightingType_DETAILS =
							ECS::LightComponent::WorldCanvas_WorldCanvas_Lighting2D_LightingType::SurrealAmbientLight;
					}
					else if (s_I_selectedLightComponentIndex == 2)
					{
						componentManager.m_Component->
							lightComponent.STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightingType_DETAILS =
							ECS::LightComponent::WorldCanvas_WorldCanvas_Lighting2D_LightingType::SurrealPointLight;
					}
					else if (s_I_selectedLightComponentIndex == 3)
					{
						componentManager.m_Component->
							lightComponent.STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightingType_DETAILS =
							ECS::LightComponent::WorldCanvas_WorldCanvas_Lighting2D_LightingType::SurrealSpotLight;
					}
					else if (s_I_selectedLightComponentIndex == 4)
					{
						componentManager.m_Component->
							lightComponent.STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightingType_DETAILS =
							ECS::LightComponent::WorldCanvas_WorldCanvas_Lighting2D_LightingType::SurrealAreaLight;
					}
					else if (s_I_selectedLightComponentIndex == 5)
					{
						componentManager.m_Component->
							lightComponent.STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightingType_DETAILS =
							ECS::LightComponent::WorldCanvas_WorldCanvas_Lighting2D_LightingType::SurrealEmissiveLight;
					}

					// REAL LIGHT PROPERTIES
					ImGui::DragFloat3("Light Position", &componentManager.m_Component->lightComponent.position[0], 1.0f);
					ImGui::DragFloat3("Light Direction", &componentManager.m_Component->lightComponent.direction[0], 1.0f);
					ImGui::DragFloat("Light Intensity", &componentManager.m_Component->lightComponent.intensity, 1.0f);
					ImGui::Spacing();

					ImGui::ColorEdit4("Light Color", &componentManager.m_Component->lightComponent.color[0]);
					ImGui::Spacing();

					ImGui::Text("Spot/Point Light Component specific");
					ImGui::DragFloat("Light Radius", &componentManager.m_Component->lightComponent.radius, 1.0f);
					ImGui::DragFloat("Light Angle", &componentManager.m_Component->lightComponent.angle, 1.0f);

					// Rest of other properties to happen in the next function: Component editor
				}
				else if (index == 6)
				{
					// Camera Component properites
					ImGui::Text("%s Properties", componentOptions[index]);

					if (ImGui::BeginCombo("Camera Component Type", c_CPTR_cameraComponent_TypeOptions[s_I_selectedCameraComponentIndex]))
					{
						for (int n = 0; n < IM_ARRAYSIZE(c_CPTR_cameraComponent_TypeOptions); n++)
						{
							bool b_IsCameraComponentSelected = (s_I_selectedCameraComponentIndex == n);
							if (ImGui::Selectable(c_CPTR_cameraComponent_TypeOptions[n], b_IsCameraComponentSelected))
								s_I_selectedCameraComponentIndex = n;

							if (b_IsCameraComponentSelected == true)
								ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					if (
						componentManager.m_Component->cameraComponentVector.size() > s_CE_uI__MAX_CAMERA_COMPONENTS &&
						s_B_openMaxCameraComponentsReachedPerWorld_SS3DERROR_DialogBox == true
						)
					{
						ImGui::OpenPopup("Surreal Studio (3D) Error - Max amount of Camera Components Reached Per World");
						s_B_openMaxCameraComponentsReachedPerWorld_SS3DERROR_DialogBox = false;
					}

					if (ImGui::BeginPopupModal("Surreal Studio (3D) Error - [COMPONENT MANAGER PANEL] Max amount of Camera Components Reached Per World", 
						nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text("[COMPONENT MANAGER PANEL] Max amount of Camera Components per world is %d, got %d.",
							s_CE_uI__MAX_CAMERA_COMPONENTS, static_cast<int>(componentManager.m_Component->cameraComponentVector.size()));

						if (ImGui::Button("OK")) {
							ImGui::CloseCurrentPopup();
							componentManager.m_Component->cameraComponentVector.resize(s_CE_uI__MAX_CAMERA_COMPONENTS); // Clamp to max value
							s_B_openMaxCameraComponentsReachedPerWorld_SS3DERROR_DialogBox = true; // Reset
						}
						ImGui::EndPopup();
					}

					if (s_I_selectedCameraComponentIndex == 0)
					{
						componentManager.m_Component->cameraComponent.cameraType = ECS::CameraComponent::CameraType::Normal;
					}
					else if (s_I_selectedCameraComponentIndex == 1)
					{
						componentManager.m_Component->cameraComponent.cameraType = ECS::CameraComponent::CameraType::Orthographic;
					}

					ImGui::DragFloat3("Position", &componentManager.m_Component->cameraComponent.position[0], 1.0f);
					ImGui::DragFloat3("Rotation", &componentManager.m_Component->cameraComponent.rotation[0], 1.0f);
					ImGui::DragFloat("Zoom", &componentManager.m_Component->cameraComponent.zoom, 1.0f);

					ImGui::DragFloat3("Velocity", &componentManager.m_Component->cameraComponent.velocity[0], 1.0f);
					ImGui::DragFloat("Rotation Speed", &componentManager.m_Component->cameraComponent.rotationSpeed, 1.0f);
					ImGui::DragFloat("Zoom Speed", &componentManager.m_Component->cameraComponent.zoomSpeed, 1.0f);
					ImGui::DragFloat3("Maximum Bounds", &componentManager.m_Component->cameraComponent.maxBounds[0], 1.0f);
					ImGui::DragFloat3("Minimum Bounds", &componentManager.m_Component->cameraComponent.minBounds[0], 1.0f);

					ImGui::Spacing();
					ImGui::Text("Orthographic Camera Component Specific Properties");

					ImGui::DragFloat("Ortho left", &componentManager.m_Component->cameraComponent.orthoLeft, 1.0f);
					ImGui::DragFloat("Ortho right", &componentManager.m_Component->cameraComponent.orthoRight, 1.0f);
					ImGui::DragFloat("Ortho bottom", &componentManager.m_Component->cameraComponent.orthoBottom, 1.0f);
					ImGui::DragFloat("Ortho top", &componentManager.m_Component->cameraComponent.orthoTop, 1.0f);
				}
				else if (index == 7)
				{
					// Asset Component Properties
					ImGui::Text("%s Properties", componentOptions[index]);
					
					if (ImGui::BeginCombo("Asset Component Type", c_CPTR_assetComponentTypeOptions[s_I_selectedAssetComponentIndex]))
					{
						for (int n = 0; n < IM_ARRAYSIZE(c_CPTR_assetComponentTypeOptions); n++)
						{
							bool b_IsAssetComponentTypeSelected = (s_I_selectedAssetComponentIndex == n);
							if (ImGui::Selectable(c_CPTR_assetComponentTypeOptions[n], b_IsAssetComponentTypeSelected))
								s_I_selectedAssetComponentIndex = n;

							if (b_IsAssetComponentTypeSelected == true)
								ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					if (
						componentManager.m_Component->assetComponentVector.size() > CE_uI_MAX_ASSETS_COMPONENTS_PER_WORLD &&
						s_B_openMaxAssetComponentsReachedPerWorld_SS3DERROR_DialogBox == true
						)
					{
						ImGui::OpenPopup("Surreal Studio (3D) Error - [COMPONENT MANAGER PANEL] Max amount of Asset Components Per World Reached");
						s_B_openMaxAssetComponentsReachedPerWorld_SS3DERROR_DialogBox = false;
					}

					if (ImGui::BeginPopupModal("Surreal Studio (3D) Error - [COMPONENT MANAGER PANEL] Max amount of Asset Components Per World Reached"
						, nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text("[COMPONENT MANAGER PANEL] Max amoutn of Asset Component Per World is %d, got %d.",
							CE_uI_MAX_ASSETS_COMPONENTS_PER_WORLD, static_cast<int>(componentManager.m_Component->assetComponentVector.size()));

						if (ImGui::Button("OK")) {
							ImGui::CloseCurrentPopup();
							componentManager.m_Component->assetComponentVector.resize(CE_uI_MAX_ASSETS_COMPONENTS_PER_WORLD); // Clamp to max value
							s_B_openMaxAssetComponentsReachedPerWorld_SS3DERROR_DialogBox = true; // Reset
						}
						ImGui::EndPopup();
					}

					ImGui::InputText("Asset Name", &componentManager.m_Component->assetComponent.assetName);

					if (ImGui::BeginCombo("Asset Load State Options", c_CPTR_assetComponentLoadStateOptions[s_I_selectedAssetComponentLoadStateOptionsIndex]))
					{
						for (int n = 0; n < IM_ARRAYSIZE(c_CPTR_assetComponentLoadStateOptions); n++)
						{
							bool b_IsAssetComponentLoadStateOptionSelected = (s_I_selectedAssetComponentLoadStateOptionsIndex == n);
							if (ImGui::Selectable(c_CPTR_assetComponentLoadStateOptions[n], b_IsAssetComponentLoadStateOptionSelected))
								s_I_selectedAssetComponentLoadStateOptionsIndex = n;

							if (b_IsAssetComponentLoadStateOptionSelected == true)
								ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					if (s_I_selectedAssetComponentLoadStateOptionsIndex == 0)
						componentManager.m_Component->assetComponent.loadState = ECS::AssetComponent::LoadState::Unloaded;
					else if (s_I_selectedAssetComponentLoadStateOptionsIndex == 1)
						componentManager.m_Component->assetComponent.loadState = ECS::AssetComponent::LoadState::Loading;
					else if (s_I_selectedAssetComponentLoadStateOptionsIndex == 2)
						componentManager.m_Component->assetComponent.loadState = ECS::AssetComponent::LoadState::Loaded;
					else if (s_I_selectedAssetComponentLoadStateOptionsIndex == 3)
						componentManager.m_Component->assetComponent.loadState = ECS::AssetComponent::LoadState::Failed;
				}
			}

			return true;
		}

		bool ComponentManagerPanel3D::DrawComponent3DEditor(const char* componentOptions[], int index)
		{
			DrawComponentProperties(componentOptions, index);
			// TODO: add advanced properties later

			return true;
		}

		bool ComponentManagerPanel3D::DrawComponentManagerPanel3D()
		{
			ImGui::Begin("Component Manager Panel");

			try { DrawComponentCreation(); }
			catch (const std::exception& e) {
				SS3D_ERROR(e.what()); return false;
			}
			catch (...) { SS3D_ERROR("Some unknown error occurred!"); return false; }

			ImGui::End();
		}
	}
}