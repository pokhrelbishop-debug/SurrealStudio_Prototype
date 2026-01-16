#include "ObjectSettingsPanel.h"

#include "../src/SurrealStudio2D/src/Core/SS2DEngineDefines.h"
#include "../src/SurrealStudio2D/src/Core/Scene/World.h"

#include <stdexcept>
#include <imgui.h>
#include <memory>

namespace SurrealStudio {

	namespace SurrealStudio2D {

		bool ObjectSettingsPanel::ShowAndDrawObjectProperties(const char* objectOption[], int index)
		{
			/* This function shows the editable properties of the selected Object (Entites) */
			try
			{
				if (!objectOption || index < 0 || index >= static_cast<int>(m_Objects.size()))
					return false;  // out of bounds; return
				
				Object2D* object = m_Objects[index].get();
				if (!object)
					return false;

				ImGui::Text("%s Properties", objectOption[index]);
				ImGui::Spacing();

				// //////////////////////////
				// Transform
				// ///////////////////////////

				ImGui::Text("Transform");

				ImGui::DragFloat2("Position ", &object->transform.objectPosition[0], 0.1f);
				ImGui::DragFloat("Rotation ", &object->transform.objectRotation, 0.1f);
				ImGui::DragFloat2("Scale ", &object->transform.objectScale[0], 0.1f);

				// Physics
				if (ImGui::Checkbox("Enable Physics", &object->enablePhysics))
				{
					// TODO: Integrate with physics engine
				}

				// Rendering specific
				float col[4] = { object->color.r, object->color.g, object->color.b, object->color.a };

				if (ImGui::ColorEdit4("Object Color ", col))
				{
					object->color.r = col[0];
					object->color.g = col[1];
					object->color.b = col[2];
					object->color.a = col[3];
				}

				ImGui::Separator();
				ImGui::Text("Texture/Material");

				// Variables required for texture management in ObjectSettingsPanel.cpp in ShowAndDrawObjectProperties function
				static constexpr unsigned int MAX_TEXTURE_MATERIALS = 25;  // Limit to 25 texture amterial per world & this only works with Texture Material
				static constexpr unsigned int MAX_CUSTOM_MATERIAL = 10; // Limit to 25 custom amterial per world & this only works with Custom Material
				static constexpr unsigned int MAX_OVERALL_MATERIALS = MAX_TEXTURE_MATERIALS + MAX_CUSTOM_MATERIAL;  // Overall material limit per World

				static int selectedMaterialIndex = 0;
				const char* materialOptions[] = {
					"Color Material", "Texture material", "Custom material"
				};
				static bool openMaxTextureMaterialsReachedSS2DErrorDialogBox = true;
				static bool openMaxCustomMaterialsReachedSS2DErrorDialogBox = true;
				static bool openMaterialTypeConfigurationDialogBox = true;

				if (openMaterialTypeConfigurationDialogBox == true)
				{
					ImGui::OpenPopup("Material Type Configuration");
					openMaterialTypeConfigurationDialogBox = false;
				}

				if (ImGui::BeginPopupModal("Material Type Configuration", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text("Materials");
					ImGui::Spacing();

					if (ImGui::BeginCombo("Material Type", materialOptions[selectedMaterialIndex]))
					{
						for (int n = 0; n < IM_ARRAYSIZE(materialOptions); n++)
						{
							bool isMaterialSelected = (selectedMaterialIndex == n);
							if (ImGui::Selectable(materialOptions[n], isMaterialSelected))
								selectedMaterialIndex = n;

							if (isMaterialSelected == true)
								ImGui::SetItemDefaultFocus();
						}

						ImGui::EndCombo();
					}
				}

				// Check if we exceeded either material limit
				if (m_Materials.size() > MAX_CUSTOM_MATERIAL || selectedMaterialIndex > MAX_CUSTOM_MATERIAL)
				{
					// Open the Texture Materials error popup if needed
					if (openMaxTextureMaterialsReachedSS2DErrorDialogBox)
					{
						ImGui::OpenPopup("Texture Material Error");
						openMaxTextureMaterialsReachedSS2DErrorDialogBox = false;
					}

					// Open the Custom Materials error popup if needed
					if (openMaxCustomMaterialsReachedSS2DErrorDialogBox)
					{
						ImGui::OpenPopup("Custom Material Error");
						openMaxCustomMaterialsReachedSS2DErrorDialogBox = false;
					}

					// Texture Material Popup
					if (ImGui::BeginPopupModal("Surreal Studio (2D) Error - Texture Material Error", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text("Max amount of Texture Materials per world is %d, got %d.", MAX_TEXTURE_MATERIALS, selectedMaterialIndex);
						if (ImGui::Button("OK"))
						{
							ImGui::CloseCurrentPopup();
							openMaxTextureMaterialsReachedSS2DErrorDialogBox = true; // reset
						}
						ImGui::EndPopup();
					}

					// Custom Material Popup
					if (ImGui::BeginPopupModal("Surreal Studio (2D) Error - Custom Material Error", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text("Max amount of Custom Materials per world is %d, got %d.", MAX_CUSTOM_MATERIAL, selectedMaterialIndex);
						if (ImGui::Button("OK"))
						{
							ImGui::CloseCurrentPopup();
							openMaxCustomMaterialsReachedSS2DErrorDialogBox = true; // reset
						}
						ImGui::EndPopup();
					}
				}

				switch (selectedMaterialIndex)
				{
					case 0:
					{
						m_Material = std::make_unique<Material2D>();

						m_CurrentObjectMaterialType = Material2D::MaterialType::ColorMaterial;
						m_Material->materialName = "Untitled Material 1";
						m_Material->materialID = static_cast<int>(m_Materials.size()) + 1;
						m_Material->materialType = m_CurrentObjectMaterialType;
						break;
					}
					case 1:
					{
						m_Material = std::make_unique<Material2D>();

						m_CurrentObjectMaterialType = Material2D::MaterialType::TextureMaterial;
						m_Material->materialName = "Untitled Material 1";
						m_Material->materialID = static_cast<int>(m_Materials.size()) + 1;
						m_Material->materialType = m_CurrentObjectMaterialType;
						break;
					}
					case 2:
					{
						m_Material = std::make_unique<Material2D>();

						m_CurrentObjectMaterialType = Material2D::MaterialType::CustomMaterial;
						m_Material->materialName = "Untitled Material 1";
						m_Material->materialID = static_cast<int>(m_Materials.size()) + 1;
						m_Material->materialType = m_CurrentObjectMaterialType;
						break;
					}
				}
				
				return true;
			}
			catch (const std::exception& e)
			{
				SS2DERROR(e.what());
				return false;
			}
			catch (...)
			{
				SS2DERROR("A unknown exception occurred!");
				return false;
			}
		}

		bool ObjectSettingsPanel::ShowAndDrawExtraObjectProperties(const char* extraObjectOptions[], int index)
		{
			try
			{
				// Variables required for ShowAndDrawExtraObjectProperties function
				static int selectedExtraObjectIndex = index;
				std::unique_ptr<ExtraObject2D> extraObject = std::make_unique<ExtraObject2D>();

				// ///////////////////////////////////////////////////////////////////
				// Show properties for Player Object of Extra Object Properties
				// //////////////////////////////////////////////////////////////////

				if (selectedExtraObjectIndex == 0)
				{
					// Player Object Properties
					ImGui::Text("%s Properties [EXTRA OBJECT PROPERTIES]", extraObjectOptions[selectedExtraObjectIndex]);

					if (ImGui::Checkbox("Show Player", &extraObject->showPlayerObjectFlag))
					{
						// TOOD: Show the player 
					}

					ImGui::Spacing();

					ImGui::Text("Transform");

					ImGui::DragFloat2("Position ", &extraObject->transform.objectPosition[0], 0.1f);
					ImGui::DragFloat("Rotation ", &extraObject->transform.objectRotation, 0.1f);
					ImGui::DragFloat2("Scale ", &extraObject->transform.objectScale[0], 0.1f);

					if (ImGui::Button("Attach script to Player Object"))
					{
						extraObject->showIfPlayerObjectHasScriptAttachedFlag = true;
						// TOOD: Show the Windows dialog box with the .py files or something
					}
				}
				else if (selectedExtraObjectIndex == 1)
				{
					ImGui::Text("%s Properties [EXTRA OBJECT PROPERTIES]", extraObjectOptions[selectedExtraObjectIndex]);

					ImGui::DragFloat("Health", &extraObject->healthObject.health);
					if (ImGui::Button("Attach Health Object to Player Object"))
					{
						extraObject->healthObject.isHealthObjectAttachedToPlayerObject = true;
						// TODO: Update Scene Hieracrhy Panel with this
					}
				}
				else if (selectedExtraObjectIndex == 2)
				{
					ImGui::Text("%s Properties [EXTRA OBJECT PROPERTIES]", extraObjectOptions[selectedExtraObjectIndex]);
				
					static constexpr unsigned int MAX_EXTRA_OBJECTS_TRIGGER_OBJECTS = 100;
					static int selectedExtraObjectTriggerObjectIndex = 0;
					const char* extraObjectTriggerObjectOptions[] = {
						"Move Trigger"  // TODO: Add more triggers later
					};
					static bool showMaxExtraObjectTriggerObjectsReachedSS2DErrorDialogBox = true;

					if (ImGui::BeginCombo("Trigger Objects", extraObjectTriggerObjectOptions[selectedExtraObjectTriggerObjectIndex]))
					{
						for (int n = 0; n < IM_ARRAYSIZE(extraObjectTriggerObjectOptions); n++)
						{
							bool isExtraObjectTriggerObjectSelected = (selectedExtraObjectTriggerObjectIndex == n);
							if (ImGui::Selectable(extraObjectTriggerObjectOptions[n], isExtraObjectTriggerObjectSelected))
								selectedExtraObjectTriggerObjectIndex = n;

							if (isExtraObjectTriggerObjectSelected == true)
								ImGui::SetItemDefaultFocus();
						}

						if ((extraObject->triggerObject2D.size() > MAX_EXTRA_OBJECTS_TRIGGER_OBJECTS || selectedExtraObjectTriggerObjectIndex > MAX_EXTRA_OBJECTS_TRIGGER_OBJECTS) && showMaxExtraObjectTriggerObjectsReachedSS2DErrorDialogBox == true)
						{
							ImGui::OpenPopup("Surreal Studio (2D) Error - [EXTRA OBJECT] Max Trigger Objects Reached");
							showMaxExtraObjectTriggerObjectsReachedSS2DErrorDialogBox = false;
						}

						ImGui::EndCombo();
					}

					if (ImGui::BeginPopupModal("Surreal Studio (2D) Error - [EXTRA OBJECT] Max Trigger Objects Reached", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text("[EXTRA OBJECT] Max amount of Trigger Object(s) per world is %d got %d", MAX_EXTRA_OBJECTS_TRIGGER_OBJECTS, static_cast<int>(extraObject->triggerObject2D.size()));

						if (ImGui::Button("OK"))
						{
							ImGui::CloseCurrentPopup();
							extraObject->triggerObject2D.resize(MAX_EXTRA_OBJECTS_TRIGGER_OBJECTS); // Clamp
							showMaxExtraObjectTriggerObjectsReachedSS2DErrorDialogBox = true; // Reset
						}
					}
				}
				else if (selectedExtraObjectIndex == 3)
				{
					if (extraObject->showIfPlayerObjectHasScriptAttachedFlag == false)
					{
						static bool openPlayerObjectHasNoScriptAttachedToItYetForInteractableObjectsToFunctionSS2DWarningDialogBox = true;

						if (openPlayerObjectHasNoScriptAttachedToItYetForInteractableObjectsToFunctionSS2DWarningDialogBox == true)
						{
							ImGui::OpenPopup("Surreal Studio (2D) Warning - [EXTRA OBJECT] Player Object Has No Script Attached for Interactable Objects To Function");
							openPlayerObjectHasNoScriptAttachedToItYetForInteractableObjectsToFunctionSS2DWarningDialogBox = false;
						}

						if (ImGui::BeginPopupModal("Surreal Studio (2D) Warning - [EXTRA OBJECT] Player Object Has No Script Attached for Interactable Objects To Function", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
						{
							ImGui::Text("WARNING - Player Object has no script attached to it that the Interactable Object can use to function. Please implement it.");
							if (ImGui::Button("OK"))
							{
								ImGui::CloseCurrentPopup();
							}
							ImGui::EndPopup();
						}

						if (ImGui::Button("Attach Script for functionality of this Object"))
						{
							// TODO: Show Open File Dialog that asks for .py files only 
						}

					}
				}

				return true;
			}
			catch (const std::exception& e)
			{
				SS2DERROR(e.what());
				return false;
			}
			catch (...)
			{
				SS2DERROR("A unknown exception occurred!");
				return false;
			}
		}

		bool ObjectSettingsPanel::DrawObjectExtraCreation()
		{
			try
			{
				static constexpr unsigned int MAX_EXTRA_OBJECTS = 250;
				static int selectedExtraObjectIndex = 0;
				const char* extraObjectOptions[] = { "Player Object", "Health Object", "Trigger Object", "Interactable Object" };
				static bool openMaxExtraObjectsReachedSS2DErrorDialogBox = true;

				if (ImGui::BeginPopupModal("Extra Object Creation & Properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					if (ImGui::BeginCombo("Extra Objects", extraObjectOptions[selectedExtraObjectIndex]))
					{
						for (int n = 0; n < IM_ARRAYSIZE(extraObjectOptions); n++)
						{
							bool isExtraObjectSelected = (selectedExtraObjectIndex == n);
							if (ImGui::Selectable(extraObjectOptions[n], isExtraObjectSelected))
								selectedExtraObjectIndex = n;
							if (isExtraObjectSelected) ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					if ((m_ExtraObjects.size() > MAX_EXTRA_OBJECTS || selectedExtraObjectIndex > MAX_EXTRA_OBJECTS) && openMaxExtraObjectsReachedSS2DErrorDialogBox)
					{
						ImGui::OpenPopup("Surreal Studio (2D) Error - Max Extra Objects Reached");
						openMaxExtraObjectsReachedSS2DErrorDialogBox = false;
					}

					ImGui::EndPopup();
				}

				// Max Extra Objects Error Popup
				if (ImGui::BeginPopupModal("Surreal Studio (2D) Error - Max Extra Objects Reached", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text("Max amount of extra objects per world is %d, got %d.", MAX_EXTRA_OBJECTS, selectedExtraObjectIndex);
					if (ImGui::Button("OK"))
					{
						ImGui::CloseCurrentPopup();
						selectedExtraObjectIndex = MAX_EXTRA_OBJECTS;
						openMaxExtraObjectsReachedSS2DErrorDialogBox = true;
					}
					ImGui::EndPopup();
				}

				// Create Button
				if (ImGui::Button("Create Extra Object"))
				{
					if (m_ExtraObjects.size() < MAX_EXTRA_OBJECTS)
						m_ExtraObjects.push_back(std::make_unique<ExtraObject2D>());
					else
						ImGui::OpenPopup("Surreal Studio (2D) Error - Max Extra Objects Reached");
				}

				return true;
			}
			catch (const std::exception& e)
			{
				SS2DERROR(e.what());
				return false;
			}
			catch (...)
			{
				SS2DERROR("An unknown exception occurred!");
				return false;
			}
		}

		bool ObjectSettingsPanel::DrawObjectCreation()
		{
			try
			{
				static constexpr unsigned int MAX_OBJECTS = 2500;

				// Selection indices
				static int selectedObjectIndex = 0;
				static int selectedObjectMeshIndex = 0;

				// Popup state flags
				static bool showMeshTypePopup = true;                  // first-time popup
				static bool openMaxObjectsReachedErrorPopup = false;   // error popup

				const char* objectOptions[] = { "SquareObject", "CircleObject", "Triangle Object" };
				const char* objectMeshOptions[] = { "Static Mesh", "Skeletal Mesh", "Dynamic Mesh" };

				// "Create new Object" button
				if (ImGui::Button("Create new Object"))
				{
					if (m_Objects.size() >= MAX_OBJECTS)
					{
						openMaxObjectsReachedErrorPopup = true; // trigger error popup
					}
					else
					{
						m_Objects.push_back(std::make_unique<Object2D>());
						showMeshTypePopup = true; // open Mesh Type popup for new object
					}
				}

				// Object selection combo
				if (ImGui::BeginCombo("Objects", objectOptions[selectedObjectIndex]))
				{
					for (int n = 0; n < IM_ARRAYSIZE(objectOptions); n++)
					{
						bool isSelected = (selectedObjectIndex == n);
						if (ImGui::Selectable(objectOptions[n], isSelected))
							selectedObjectIndex = n;
						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

				// First-time Mesh Type popup
				if (showMeshTypePopup)
				{
					ImGui::OpenPopup("Mesh Type Configuration");
					showMeshTypePopup = false;
				}

				// Mesh Type Configuration popup
				if (ImGui::BeginPopupModal("Mesh Type Configuration", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text("Select Mesh Type");
					ImGui::Spacing();

					if (ImGui::BeginCombo("Mesh Type", objectMeshOptions[selectedObjectMeshIndex]))
					{
						for (int n = 0; n < IM_ARRAYSIZE(objectMeshOptions); n++)
						{
							bool isSelected = (selectedObjectMeshIndex == n);
							if (ImGui::Selectable(objectMeshOptions[n], isSelected))
								selectedObjectMeshIndex = n;
							if (isSelected)
								ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					ImGui::Spacing();
					if (ImGui::Button("OK"))
					{
						// Apply mesh type using switch
						switch (selectedObjectMeshIndex)
						{
						case 0: m_CurrentObjectMesh = Mesh::MeshType::StaticMesh; break;
						case 1: m_CurrentObjectMesh = Mesh::MeshType::SkeletalMesh; break;
						case 2: m_CurrentObjectMesh = Mesh::MeshType::DynamicMesh; break;
						}
						ImGui::CloseCurrentPopup();
					}

					ImGui::SameLine();
					if (ImGui::Button("Cancel"))
					{
						ImGui::CloseCurrentPopup();
					}

					ImGui::EndPopup();
				}

				// Error popup if max objects reached
				if (openMaxObjectsReachedErrorPopup)
				{
					ImGui::OpenPopup("Surreal Studio (2D) Error");
					openMaxObjectsReachedErrorPopup = false;
				}

				if (ImGui::BeginPopupModal("Surreal Studio (2D) Error", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text("Max amount of objects reached: %d", MAX_OBJECTS);
					ImGui::Spacing();
					if (ImGui::Button("OK"))
					{
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}

				return true;
			}
			catch (const std::exception& e)
			{
				SS2DERROR(e.what());
				return false;
			}
			catch (...)
			{
				SS2DERROR("An unknown exception occurred!");
				return false;
			}
		}

		bool ObjectSettingsPanel::DrawObjectSettingsPanel()
		{
			bool result = true;
			ImGui::Begin("Object Settings"); // ? always paired with End

			try
			{
				if (!DrawObjectCreation()) result = false;
				if (!DrawObjectExtraCreation()) result = false;
			}
			catch (const std::exception& e)
			{
				SS2DERROR(e.what());
				result = false;
			}
			catch (...)
			{
				SS2DERROR("An unknown exception occurred!");
				result = false;
			}

			ImGui::End(); // ? always called
			return result;
		}
	}
}