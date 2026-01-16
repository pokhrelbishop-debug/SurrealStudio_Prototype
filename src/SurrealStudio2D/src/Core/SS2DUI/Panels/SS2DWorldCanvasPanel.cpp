#include "SS2DWorldCanvasPanel.h"
#include "../src/SurrealStudio2D/src/Core/SS2DEngineDefines.h"

#include <imgui.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <Windows.h>
#include <codecvt>
#include <glm/glm.hpp>

namespace SurrealStudio {

	namespace SurrealStudio2D {

		std::wstring OpenFileDialogPNG(HWND owner = nullptr)
		{
			OPENFILENAMEW ofn;             // wide-char version
			wchar_t szFile[MAX_PATH]{};    // buffer for file name

			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = owner;
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = MAX_PATH;

			// Filter for PNG files only
			ofn.lpstrFilter = L"PNG Files (*.png)\0*.png\0";
			ofn.nFilterIndex = 1;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

			if (GetOpenFileNameW(&ofn) == TRUE)
			{
				return std::wstring(szFile);
			}

			return L""; // empty string if canceled
		}

#pragma region DrawWorldGroundSettings Function

		bool SS2DWorldCanvasPanel::DrawWorldGroundSettings()
		{
			if (m_SS2DWorldCanvas_DETAILS.empty())
				m_SS2DWorldCanvas_DETAILS.push_back(std::make_unique<WorldCanvas>());

			if (m_WorldCanvas_WorldGround_DETAILS.empty())
				m_WorldCanvas_WorldGround_DETAILS.push_back(std::make_unique<WorldCanvas::WorldCanvas_GroundSettings>());

			static constexpr unsigned int MAX_WORLD_GROUND_MATERIALS = 5;
			static int selectedIndex = 0;
			const char* options[] = { "Color", "Size" };
			static bool openMaxMaterialsDialog = true;

			if (ImGui::CollapsingHeader("World Ground"))
			{
				if (ImGui::BeginCombo("World Ground Setting Options", options[selectedIndex]))
				{
					for (int n = 0; n < IM_ARRAYSIZE(options); n++)
					{
						bool isSelected = (selectedIndex == n);
						if (ImGui::Selectable(options[n], isSelected))
							selectedIndex = n;

						if (isSelected) ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

				if (selectedIndex == 0)
				{
					ImGui::Text("World %s Properties", options[selectedIndex]);
					float color[4] = { 0.f, 0.f, 0.f, 0.f };

					if (!m_WorldCanvas_WorldGround_DETAILS.empty())
					{
						const auto& ground = m_WorldCanvas_WorldGround_DETAILS[0]->WorldCanvas_GroundSettings_WorldGroundCOLOR;
						color[0] = ground.x; color[1] = ground.y; color[2] = ground.z; color[3] = ground.w;
					}

					ImGui::ColorEdit4("Color: ", color);
					// TODO: Update WorldGround color
				}
				else if (selectedIndex == 1)
				{
					if (!m_SS2DWorldCanvas_DETAILS.empty() &&
						m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvasMaterial_DETAILS.size() > MAX_WORLD_GROUND_MATERIALS &&
						openMaxMaterialsDialog)
					{
						ImGui::OpenPopup("Max materials reached for World Ground");
						openMaxMaterialsDialog = false;
					}
					else
					{
						std::wstring wFile = OpenFileDialogPNG();
						if (!wFile.empty())
						{
							// Convert to UTF-8 std::string using WideCharToMultiByte
							int size_needed = WideCharToMultiByte(CP_UTF8, 0, wFile.c_str(), -1, nullptr, 0, nullptr, nullptr);
							std::string filePath(size_needed, 0);
							WideCharToMultiByte(CP_UTF8, 0, wFile.c_str(), -1, filePath.data(), size_needed, nullptr, nullptr);

							SS2DINFO(filePath.c_str());
						}
					}
				}

				if (ImGui::BeginPopupModal("Max materials reached for World Ground", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text("Max materials per World Ground is %d, got %d",
						MAX_WORLD_GROUND_MATERIALS,
						static_cast<int>(m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvasMaterial_DETAILS.size()));

					if (ImGui::Button("OK"))
					{
						ImGui::CloseCurrentPopup();
						m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvasMaterial_DETAILS.resize(MAX_WORLD_GROUND_MATERIALS);
						openMaxMaterialsDialog = true;
					}
					ImGui::EndPopup();
				}
			}

			return true;
		}

#pragma endregion


#pragma region DrawWorldMiddleGroundSettings Function

		bool SS2DWorldCanvasPanel::DrawWorldMiddleGroundSettings()
		{
			if (m_SS2DWorldCanvas_DETAILS.empty())
				m_SS2DWorldCanvas_DETAILS.push_back(std::make_unique<WorldCanvas>());

			if (m_WorldCanvas_WorldMiddleGround_DETAILS.empty())
				m_WorldCanvas_WorldMiddleGround_DETAILS.push_back(std::make_unique<WorldCanvas::WorldCanvas_MiddleGroundSettings>());

			static constexpr unsigned int MAX_MATERIALS = 5;
			static int selectedIndex = 0;
			const char* options[] = { "Color", "Material/Texture" };
			static bool openMaxMaterialsDialog = true;

			if (ImGui::CollapsingHeader("World Middle Ground"))
			{
				if (ImGui::BeginCombo("World Middle Ground", options[selectedIndex]))
				{
					for (int n = 0; n < IM_ARRAYSIZE(options); n++)
					{
						bool isSelected = (selectedIndex == n);
						if (ImGui::Selectable(options[n], isSelected))
							selectedIndex = n;
						if (isSelected) ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

				if (selectedIndex == 0)
				{
					ImGui::Text("World Middle Ground %s Properties", options[selectedIndex]);
					float color[4] = { 0.f, 0.f, 0.f, 0.f };

					if (!m_WorldCanvas_WorldMiddleGround_DETAILS.empty())
					{
						const auto& c = m_WorldCanvas_WorldMiddleGround_DETAILS[0]->WorldCanvas_MiddleGroundSettings_WorldMiddleGroundCOLOR;
						color[0] = c.x; color[1] = c.y; color[2] = c.z; color[3] = c.w;
					}

					ImGui::ColorEdit4("World MiddleGround Color", color);
					// TODO: Update middle ground color
				}
				else
				{
					if (!m_SS2DWorldCanvas_DETAILS.empty() &&
						m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvasMaterial_DETAILS.size() > MAX_MATERIALS &&
						openMaxMaterialsDialog)
					{
						ImGui::OpenPopup("Max materials reached for World Middle Ground");
						openMaxMaterialsDialog = false;
					}
					else
					{
						std::wstring wFile = OpenFileDialogPNG();
						if (!wFile.empty())
						{
							int size_needed = WideCharToMultiByte(CP_UTF8, 0, wFile.c_str(), -1, nullptr, 0, nullptr, nullptr);
							std::string filePath(size_needed, 0);
							WideCharToMultiByte(CP_UTF8, 0, wFile.c_str(), -1, filePath.data(), size_needed, nullptr, nullptr);

							SS2DINFO(filePath.c_str());
						}
					}
				}

				if (ImGui::BeginPopupModal("Max materials reached for World Middle Ground", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text("Max materials per World Middle Ground is %d, got %d",
						MAX_MATERIALS,
						static_cast<int>(m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvasMaterial_DETAILS.size()));
					if (ImGui::Button("OK"))
					{
						ImGui::CloseCurrentPopup();
						m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvasMaterial_DETAILS.resize(MAX_MATERIALS);
						openMaxMaterialsDialog = true;
					}
					ImGui::EndPopup();
				}
			}

			return true;
		}

#pragma endregion

#pragma region DrawWorldSkySettings Function

		bool SS2DWorldCanvasPanel::DrawWorldSkySettings()
		{
			if (m_SS2DWorldCanvas_DETAILS.empty())
				m_SS2DWorldCanvas_DETAILS.push_back(std::make_unique<WorldCanvas>());

			if (m_WorldCanvas_WorldSky_DETAILS.empty())
				m_WorldCanvas_WorldSky_DETAILS.push_back(std::make_unique<WorldCanvas::WorldCanvas_SkySettings>());

			static constexpr unsigned int MAX_MATERIALS = 5;
			static int selectedIndex = 0;
			const char* options[] = { "Color", "Material/Texture" };
			static bool openMaxMaterialsDialog = true;

			if (ImGui::CollapsingHeader("World Sky"))
			{
				if (ImGui::BeginCombo("World Sky Settings Options", options[selectedIndex]))
				{
					for (int n = 0; n < IM_ARRAYSIZE(options); n++)
					{
						bool isSelected = (selectedIndex == n);
						if (ImGui::Selectable(options[n], isSelected))
							selectedIndex = n;
						if (isSelected) ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

				if (selectedIndex == 0)
				{
					ImGui::Text("World Sky %s Properties", options[selectedIndex]);
					float color[4] = { 0.f, 0.f, 0.f, 0.f };

					if (!m_WorldCanvas_WorldSky_DETAILS.empty())
					{
						const auto& c = m_WorldCanvas_WorldSky_DETAILS[0]->WorldCanvas_SkySettings_SkySettingsCOLOR;
						color[0] = c.x; color[1] = c.y; color[2] = c.z; color[3] = c.w;
					}

					ImGui::ColorEdit4("World Sky Color", color);
					// TODO: Update sky color
				}
				else
				{
					if (!m_SS2DWorldCanvas_DETAILS.empty() &&
						m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvasMaterial_DETAILS.size() > MAX_MATERIALS &&
						openMaxMaterialsDialog)
					{
						ImGui::OpenPopup("Max materials reached for World Sky");
						openMaxMaterialsDialog = false;
					}
					else
					{
						std::wstring wFile = OpenFileDialogPNG();
						if (!wFile.empty()) 
						{
							int size_needed = WideCharToMultiByte(CP_UTF8, 0, wFile.c_str(), -1, nullptr, 0, nullptr, nullptr);
							std::string filePath(size_needed, 0);
							WideCharToMultiByte(CP_UTF8, 0, wFile.c_str(), -1, filePath.data(), size_needed, nullptr, nullptr);

							SS2DINFO(filePath.c_str());
						}
					}
				}

				if (ImGui::BeginPopupModal("Max materials reached for World Sky", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text("Max materials per World Sky is %d, got %d",
						MAX_MATERIALS,
						static_cast<int>(m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvasMaterial_DETAILS.size()));
					if (ImGui::Button("OK"))
					{
						ImGui::CloseCurrentPopup();
						m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvasMaterial_DETAILS.resize(MAX_MATERIALS);
						openMaxMaterialsDialog = true;
					}
					ImGui::EndPopup();
				}
			}

			return true;
		}

#pragma endregion


#pragma region DrawWorldCanvas_CameraCreation Function

		bool SS2DWorldCanvasPanel::DrawWorldCanvas_CameraCreation()
		{
			if (m_SS2DWorldCanvas_DETAILS.empty())
				m_SS2DWorldCanvas_DETAILS.push_back(std::make_unique<WorldCanvas>());

			if (m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Camera2D_DETAILS.empty())
			{
				m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Camera2D_DETAILS.push_back(std::make_unique<WorldCanvas::WorldCanvas_Camera2D>());
			}
			else
				m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Camera2D_DETAILS.push_back(std::make_unique<WorldCanvas::WorldCanvas_Camera2D>());

			// Set default
			m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Camera2D_DETAILS[0]->SI_WorldCanvas_Camera2D_CameraType_DETAILS = WorldCanvas::WorldCanvas_Camera2D::WorldCanvas_Camera2D_CameraType::None;

			/* This function is the second way of creating Cameras in SS2D */
			static constexpr unsigned int s_CE_uI__WorldCanvas_CameraCreation_MAX_CAMERAS_PER_WORLD_LIMIT = 3; 
			static int s_I__WorldCanvas_selectedCameraIndex = 0;
			const char* c_CPTR_WorldCanvas_CameraCreation_CameraOptions[] = {
				"Normal", "Orthographic"
			};
			static bool s_B__WorldCanvas_openMaxCamerasReachedPerWorldLimit_SS2DERROR_DialogBox = true;

			if (ImGui::CollapsingHeader("Camera"))
			{
				if (ImGui::BeginCombo("World Canvas - Camera Options", c_CPTR_WorldCanvas_CameraCreation_CameraOptions[s_I__WorldCanvas_selectedCameraIndex]))
				{
					for (int n = 0; n < IM_ARRAYSIZE(c_CPTR_WorldCanvas_CameraCreation_CameraOptions); n++)
					{
						bool b_WorldCanvas_CameraCreation_isCameraSelected = (s_I__WorldCanvas_selectedCameraIndex == n);
						if (ImGui::Selectable(c_CPTR_WorldCanvas_CameraCreation_CameraOptions[n], b_WorldCanvas_CameraCreation_isCameraSelected))
							s_I__WorldCanvas_selectedCameraIndex = n;

						if (b_WorldCanvas_CameraCreation_isCameraSelected == true)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}

				if (
					m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Camera2D_DETAILS.size() > s_CE_uI__WorldCanvas_CameraCreation_MAX_CAMERAS_PER_WORLD_LIMIT
					&& s_B__WorldCanvas_openMaxCamerasReachedPerWorldLimit_SS2DERROR_DialogBox == true
					)
				{
					ImGui::OpenPopup("Surreal Studio (2D) Error - [WORLD CANVAS] Max amount of cameras reached per world");
					s_B__WorldCanvas_openMaxCamerasReachedPerWorldLimit_SS2DERROR_DialogBox = false;
				}

				if (ImGui::BeginPopupModal("Surreal Studio (2D) Error - [WORLD CANVAS] Max amount of cameras reached per world", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text(
						"[WORLD CANVAS] Max amount of Cameras per world is %d got %d.",
						s_CE_uI__WorldCanvas_CameraCreation_MAX_CAMERAS_PER_WORLD_LIMIT, static_cast<int>(m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Camera2D_DETAILS.size())
					);

					if (ImGui::Button("OK")) {
						ImGui::CloseCurrentPopup();
						m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Camera2D_DETAILS.resize(s_CE_uI__WorldCanvas_CameraCreation_MAX_CAMERAS_PER_WORLD_LIMIT);
						s_B__WorldCanvas_openMaxCamerasReachedPerWorldLimit_SS2DERROR_DialogBox = false;
					}
					ImGui::EndPopup();
				}

				if (s_I__WorldCanvas_selectedCameraIndex == 0)
				{
					m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Camera2D_DETAILS[0]->SI_WorldCanvas_Camera2D_CameraType_DETAILS = WorldCanvas::WorldCanvas_Camera2D::WorldCanvas_Camera2D_CameraType::Normal;
					DrawWorldCanvas_CameraProperties(c_CPTR_WorldCanvas_CameraCreation_CameraOptions, s_I__WorldCanvas_selectedCameraIndex);
				}
				else if (s_I__WorldCanvas_selectedCameraIndex == 1)
				{
					m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Camera2D_DETAILS[0]->SI_WorldCanvas_Camera2D_CameraType_DETAILS = WorldCanvas::WorldCanvas_Camera2D::WorldCanvas_Camera2D_CameraType::Orthographic;
					DrawWorldCanvas_CameraProperties(c_CPTR_WorldCanvas_CameraCreation_CameraOptions, s_I__WorldCanvas_selectedCameraIndex);
				}
			}
			return true;
		}

#pragma endregion

#pragma region DrawWorldCanvas_CameraProperties Function

		bool SS2DWorldCanvasPanel::DrawWorldCanvas_CameraProperties(const char* WorldCanvas_cameraOptions[], int index)
		{
			if (m_SS2DWorldCanvas_DETAILS.empty())
				m_SS2DWorldCanvas_DETAILS.push_back(std::make_unique<WorldCanvas>());

			if (!WorldCanvas_cameraOptions || index < 0 || index >= static_cast<int>(m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Camera2D_DETAILS.size()))
				return false;

			WorldCanvas::WorldCanvas_Camera2D* STRUCT_WorldCanvas_WorldCanvas_Camera2D_camera = m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Camera2D_DETAILS[index].get();
			if (!STRUCT_WorldCanvas_WorldCanvas_Camera2D_camera)
				return false;

			ImGui::Text("%s Camera Properties", WorldCanvas_cameraOptions[index]);

			ImGui::DragFloat2("Camera Position ", &STRUCT_WorldCanvas_WorldCanvas_Camera2D_camera->position[0], 0.1f);
			ImGui::DragFloat("Camera Rotation/Direction ", &STRUCT_WorldCanvas_WorldCanvas_Camera2D_camera->rotation, 0.1f);
			ImGui::SliderFloat("Camera Zoom ", &STRUCT_WorldCanvas_WorldCanvas_Camera2D_camera->zoom, 1.0f, 10.0f);
			ImGui::DragFloat2("Viewport Size ", &STRUCT_WorldCanvas_WorldCanvas_Camera2D_camera->viewportSize[0], 0.1f);
			ImGui::DragFloat2("Target ", &STRUCT_WorldCanvas_WorldCanvas_Camera2D_camera->target[0], 0.1f);

			ImGui::Spacing();
			ImGui::Text("Orthographic Bounds");
			ImGui::DragFloat("Left: ", &STRUCT_WorldCanvas_WorldCanvas_Camera2D_camera->orthographicBoundsLeft, 0.1f);
			ImGui::DragFloat("Right: ", &STRUCT_WorldCanvas_WorldCanvas_Camera2D_camera->orthographicBoundsRight, 0.1f);
			ImGui::DragFloat("Top: ", &STRUCT_WorldCanvas_WorldCanvas_Camera2D_camera->orthographicBoundsTop, 0.1f);
			ImGui::DragFloat("Bottom: ", &STRUCT_WorldCanvas_WorldCanvas_Camera2D_camera->orthographicBoundsBottom, 0.1f);

			return true;
		}

#pragma endregion

#pragma region DrawWorldCanvas_LightCreation Function

		bool SS2DWorldCanvasPanel::DrawWorldCanvas_LightCreation()
		{
			if (m_SS2DWorldCanvas_DETAILS.empty())
				m_SS2DWorldCanvas_DETAILS.push_back(std::make_unique<WorldCanvas>());

			if (m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS.empty())
				m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS.push_back(std::make_unique<WorldCanvas::WorldCanvas_Lighting2D>());
			else
				m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS.push_back(std::make_unique<WorldCanvas::WorldCanvas_Lighting2D>());

			// Set default
			m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS[0]->STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightingType_DETAILS = 
				WorldCanvas::WorldCanvas_Lighting2D::WorldCanvas_WorldCanvas_Lighting2D_LightingType::None;

			/* This function is the second way of creating a Light (Object) in SS2D */
			static constexpr unsigned int s_CE_uI__WorldCanvas_WorldCanvas_Lighting2D_MAX_LIGHTS_REACHED_PER_WORLD_LIMIT = 10;
			static int s_I__WorldCanvas_WorldCanvas_Lighting2D_selectedLightIndex = 0;
			const char* c_CPTR_WorldCanvas_WorldCanvas_Lighting2D_lightingOptions[] = {
				"WorldEnvironmentLight", "SurrealAmbientLight",
				"SurrealPointLight", "SurrealSpotLight", "SurrealAreaLight",
				"SurrealEmissiveLight"
			};
			static bool s_B__WorldCanvas_WorldCanvas_Lighting2D_openMaxLightsReachedPerWorld_SS2DERROR_DialogBox = true;

			if (ImGui::CollapsingHeader("Lighting"))
			{
				if (ImGui::BeginCombo("World Canvas - Camera Options", c_CPTR_WorldCanvas_WorldCanvas_Lighting2D_lightingOptions[s_I__WorldCanvas_WorldCanvas_Lighting2D_selectedLightIndex]))
				{
					for (int n = 0; n < IM_ARRAYSIZE(c_CPTR_WorldCanvas_WorldCanvas_Lighting2D_lightingOptions); n++)
					{
						bool b_WorldCanvas_WorldCanvas_Lighting2D_isLightTypeSelected = (s_I__WorldCanvas_WorldCanvas_Lighting2D_selectedLightIndex == n);
						if (ImGui::Selectable(c_CPTR_WorldCanvas_WorldCanvas_Lighting2D_lightingOptions[n], b_WorldCanvas_WorldCanvas_Lighting2D_isLightTypeSelected))
							s_I__WorldCanvas_WorldCanvas_Lighting2D_selectedLightIndex = n;

						if (b_WorldCanvas_WorldCanvas_Lighting2D_isLightTypeSelected == true)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}

				if (
					m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS.size() > s_CE_uI__WorldCanvas_WorldCanvas_Lighting2D_MAX_LIGHTS_REACHED_PER_WORLD_LIMIT &&
					s_B__WorldCanvas_WorldCanvas_Lighting2D_openMaxLightsReachedPerWorld_SS2DERROR_DialogBox == true
					)
				{
					ImGui::OpenPopup("Surreal Studio (2D) Error - [WORLD CANVAS] Max amount of Light (Object) reached per World");
					s_B__WorldCanvas_WorldCanvas_Lighting2D_openMaxLightsReachedPerWorld_SS2DERROR_DialogBox = false;
				}

				if (ImGui::BeginPopupModal("Surreal Studio (2D) Error - [WORLD CANVAS] Max amount of Light (Object) reached per World", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text(
						"[WORLD CANVAS] Max amount of Light (Objects) per World is %d got %d.",
						s_CE_uI__WorldCanvas_WorldCanvas_Lighting2D_MAX_LIGHTS_REACHED_PER_WORLD_LIMIT,
						static_cast<int>(m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS.size())
					);

					if (ImGui::Button("OK")) {
						ImGui::CloseCurrentPopup();
						m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS.resize(s_CE_uI__WorldCanvas_WorldCanvas_Lighting2D_MAX_LIGHTS_REACHED_PER_WORLD_LIMIT); // Clamp
						s_B__WorldCanvas_WorldCanvas_Lighting2D_openMaxLightsReachedPerWorld_SS2DERROR_DialogBox = true; // Reset
					}
					ImGui::EndPopup();
				}

				if (s_I__WorldCanvas_WorldCanvas_Lighting2D_selectedLightIndex == 0)
				{
					m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS[0]->STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightingType_DETAILS =
						WorldCanvas::WorldCanvas_Lighting2D::WorldCanvas_WorldCanvas_Lighting2D_LightingType::WorldEnvironmentLight;
					DrawWorldCanvas_LightProperties(c_CPTR_WorldCanvas_WorldCanvas_Lighting2D_lightingOptions, s_I__WorldCanvas_WorldCanvas_Lighting2D_selectedLightIndex);
				}
				else if (s_I__WorldCanvas_WorldCanvas_Lighting2D_selectedLightIndex == 1)
				{
					m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS[0]->STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightingType_DETAILS =
						WorldCanvas::WorldCanvas_Lighting2D::WorldCanvas_WorldCanvas_Lighting2D_LightingType::SurrealAmbientLight;
					DrawWorldCanvas_LightProperties(c_CPTR_WorldCanvas_WorldCanvas_Lighting2D_lightingOptions, s_I__WorldCanvas_WorldCanvas_Lighting2D_selectedLightIndex);
				}
				else if (s_I__WorldCanvas_WorldCanvas_Lighting2D_selectedLightIndex == 2)
				{
					m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS[0]->STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightingType_DETAILS =
						WorldCanvas::WorldCanvas_Lighting2D::WorldCanvas_WorldCanvas_Lighting2D_LightingType::SurrealPointLight;
					DrawWorldCanvas_LightProperties(c_CPTR_WorldCanvas_WorldCanvas_Lighting2D_lightingOptions, s_I__WorldCanvas_WorldCanvas_Lighting2D_selectedLightIndex);
				}
				else if (s_I__WorldCanvas_WorldCanvas_Lighting2D_selectedLightIndex == 3)
				{
					m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS[0]->STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightingType_DETAILS =
						WorldCanvas::WorldCanvas_Lighting2D::WorldCanvas_WorldCanvas_Lighting2D_LightingType::SurrealSpotLight;
					DrawWorldCanvas_LightProperties(c_CPTR_WorldCanvas_WorldCanvas_Lighting2D_lightingOptions, s_I__WorldCanvas_WorldCanvas_Lighting2D_selectedLightIndex);
				}
				else if (s_I__WorldCanvas_WorldCanvas_Lighting2D_selectedLightIndex == 4)
				{
					m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS[0]->STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightingType_DETAILS =
						WorldCanvas::WorldCanvas_Lighting2D::WorldCanvas_WorldCanvas_Lighting2D_LightingType::SurrealAreaLight;
					DrawWorldCanvas_LightProperties(c_CPTR_WorldCanvas_WorldCanvas_Lighting2D_lightingOptions, s_I__WorldCanvas_WorldCanvas_Lighting2D_selectedLightIndex);
				}
				else if (s_I__WorldCanvas_WorldCanvas_Lighting2D_selectedLightIndex == 5)
				{
					m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS[0]->STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightingType_DETAILS =
						WorldCanvas::WorldCanvas_Lighting2D::WorldCanvas_WorldCanvas_Lighting2D_LightingType::SurrealEmissiveLight;
					DrawWorldCanvas_LightProperties(c_CPTR_WorldCanvas_WorldCanvas_Lighting2D_lightingOptions, s_I__WorldCanvas_WorldCanvas_Lighting2D_selectedLightIndex);
				}
			}
			return true;
		}

#pragma endregion

		bool SS2DWorldCanvasPanel::DrawWorldCanvas_LightProperties(const char* WorldCanvas_lightingOptions[], int index)
		{
			if (m_SS2DWorldCanvas_DETAILS.empty())
				m_SS2DWorldCanvas_DETAILS.push_back(std::make_unique<WorldCanvas>());

			if (m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS.empty())
				m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS.push_back(std::make_unique<WorldCanvas::WorldCanvas_Particle2D>());

			if (!WorldCanvas_lightingOptions || index < 0 || index >= static_cast<int>(m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS.size()))
				return false;

			WorldCanvas::WorldCanvas_Lighting2D* STRUCT_INSTANCE_PTR__WorldCanvas_LightProperties_Lighting2D_light = m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS[index].get();
			if (!STRUCT_INSTANCE_PTR__WorldCanvas_LightProperties_Lighting2D_light)
				return false;

			ImGui::Text("%s Properties", WorldCanvas_lightingOptions[index]);

			ImGui::DragFloat2("Position", &STRUCT_INSTANCE_PTR__WorldCanvas_LightProperties_Lighting2D_light->position[0], 0.1f);
			ImGui::DragFloat2("Direction", &STRUCT_INSTANCE_PTR__WorldCanvas_LightProperties_Lighting2D_light->direction[0], 0.1f);
			ImGui::DragFloat("Intensity", &STRUCT_INSTANCE_PTR__WorldCanvas_LightProperties_Lighting2D_light->intensity, 0.1f);
			ImGui::ColorEdit4("Color", &STRUCT_INSTANCE_PTR__WorldCanvas_LightProperties_Lighting2D_light->color[0]);
			ImGui::DragFloat("Radius", &STRUCT_INSTANCE_PTR__WorldCanvas_LightProperties_Lighting2D_light->radius, 1.0f);
			ImGui::DragFloat("Angle", &STRUCT_INSTANCE_PTR__WorldCanvas_LightProperties_Lighting2D_light->angle, 1.0f);
			ImGui::Checkbox("Casts Shadows", &STRUCT_INSTANCE_PTR__WorldCanvas_LightProperties_Lighting2D_light->castsShadows);

			return true;
		}

		bool SS2DWorldCanvasPanel::DrawWorldCanvas_2DParticleCreation()
		{
			if (m_SS2DWorldCanvas_DETAILS.empty())
				m_SS2DWorldCanvas_DETAILS.push_back(std::make_unique<WorldCanvas>());

			if (m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS.empty())
				m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS.push_back(std::make_unique<WorldCanvas::WorldCanvas_Particle2D>());

			static constexpr unsigned int s_CE_uI__WorldCanvas_WorldCanvas_Particle2D_MAX_PARTICLES_REACHED_PER_WORLD_LIMIT = 10000;
			static int s_I__WorldCanvas_WorldCanvas_Particle2D_selectedParticleIndex = 0;
			const char* c_CPTR__WorldCanvas_WorldCanvas_Particle2D_ParticleOptions[] = {
				"Bright Particle", "Dark Particle", "Fire Particle",
				"Smoke Particle", "Custom Particle"
			};
			static bool s_B__WorldCanvas_WorldCanvas_Particle2D_openMaxParticlesReachedPerWorldLimit_SS2DERROR_DialogBox = true;

			if (ImGui::CollapsingHeader("Particles"))
			{
				if (ImGui::BeginCombo("Particle Types", c_CPTR__WorldCanvas_WorldCanvas_Particle2D_ParticleOptions[s_I__WorldCanvas_WorldCanvas_Particle2D_selectedParticleIndex]))
				{
					for (int n = 0; n < IM_ARRAYSIZE(c_CPTR__WorldCanvas_WorldCanvas_Particle2D_ParticleOptions); n++)
					{
						bool b_WorldCanvas_WorldCanvas_Particle2D_isParticleSelected = (s_I__WorldCanvas_WorldCanvas_Particle2D_selectedParticleIndex == n);
						if (ImGui::Selectable(c_CPTR__WorldCanvas_WorldCanvas_Particle2D_ParticleOptions[n], b_WorldCanvas_WorldCanvas_Particle2D_isParticleSelected))
							s_I__WorldCanvas_WorldCanvas_Particle2D_selectedParticleIndex = n;

						if (b_WorldCanvas_WorldCanvas_Particle2D_isParticleSelected == true)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}

				if (
					m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS.size() > s_CE_uI__WorldCanvas_WorldCanvas_Particle2D_MAX_PARTICLES_REACHED_PER_WORLD_LIMIT &&
					s_B__WorldCanvas_WorldCanvas_Particle2D_openMaxParticlesReachedPerWorldLimit_SS2DERROR_DialogBox == true
					)
				{
					ImGui::OpenPopup("Surreal Studio (2D) Error - [WORLD CANVAS] Max amount of Particles Objects reached per World");
					s_B__WorldCanvas_WorldCanvas_Particle2D_openMaxParticlesReachedPerWorldLimit_SS2DERROR_DialogBox = false;
				}

				if (ImGui::BeginPopupModal("Surreal Studio (2D) Error - [WORLD CANVAS] Max amount of particles reached per World", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text(
						"[WORLD CANVAS] Max amount of Particle Objects per World is %d got %d.",
						s_CE_uI__WorldCanvas_WorldCanvas_Particle2D_MAX_PARTICLES_REACHED_PER_WORLD_LIMIT,
						static_cast<int>(m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS.size())
					);

					if (ImGui::Button("OK")) {
						ImGui::CloseCurrentPopup();
						m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS.resize(s_CE_uI__WorldCanvas_WorldCanvas_Particle2D_MAX_PARTICLES_REACHED_PER_WORLD_LIMIT); // Clamp
						s_B__WorldCanvas_WorldCanvas_Particle2D_openMaxParticlesReachedPerWorldLimit_SS2DERROR_DialogBox = true; // Reset
					}
					ImGui::EndPopup();
				}

				if (ImGui::Button("Create New Particle"))
				{
					if (m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS.size() < s_CE_uI__WorldCanvas_WorldCanvas_Particle2D_MAX_PARTICLES_REACHED_PER_WORLD_LIMIT)
					{
						auto a_WorldCanvas_WorldCanvas_Particle2D_newParticle2D = std::make_unique<WorldCanvas::WorldCanvas_Particle2D>();

						// Set particle based on selection
						a_WorldCanvas_WorldCanvas_Particle2D_newParticle2D->ENUMCLASS_INSTANCE__WorldCanvas_Particle2D_ParticleType_DETAILS =
							static_cast<WorldCanvas::WorldCanvas_Particle2D::WorldCanvas_Particle2D_ParticleType>(s_I__WorldCanvas_WorldCanvas_Particle2D_selectedParticleIndex + 1);

						m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS.push_back(std::move(a_WorldCanvas_WorldCanvas_Particle2D_newParticle2D));
						DrawWorldCanvas_2DParticleProperties(c_CPTR__WorldCanvas_WorldCanvas_Particle2D_ParticleOptions, s_I__WorldCanvas_WorldCanvas_Particle2D_selectedParticleIndex);
					}
				}

				if (ImGui::Button("Particle Editor"))
				{
					DrawWorldCanvas_2DParticleEditor_Properties(c_CPTR__WorldCanvas_WorldCanvas_Particle2D_ParticleOptions, s_I__WorldCanvas_WorldCanvas_Particle2D_selectedParticleIndex);
				}
			}
			return true;
		}

		bool SS2DWorldCanvasPanel::DrawWorldCanvas_2DParticleProperties(const char* WorldCanvas_2DparticleOptions[], int index)
		{
			if (m_SS2DWorldCanvas_DETAILS.empty())
				m_SS2DWorldCanvas_DETAILS.push_back(std::make_unique<WorldCanvas>());

			if (m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS.empty())
				m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS.push_back(std::make_unique<WorldCanvas::WorldCanvas_Particle2D>());

			if (!WorldCanvas_2DparticleOptions || index < 0 || index >= static_cast<int>(m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS.size()))
				return false;

			WorldCanvas::WorldCanvas_Particle2D* STRUCT_INSTANCE_PTR_WorldCanvas_WorldCanvas_Particle2D_particle2D = m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS[index].get();
			if (!STRUCT_INSTANCE_PTR_WorldCanvas_WorldCanvas_Particle2D_particle2D)
				return false;

			ImGui::Text("%s Properties", WorldCanvas_2DparticleOptions[index]);

			// Particle Transform
			ImGui::Text("Particle Transform");
			ImGui::DragFloat2("Particle Position", &STRUCT_INSTANCE_PTR_WorldCanvas_WorldCanvas_Particle2D_particle2D->GLMVEC2_particlePosition[0], 0.1f);
			ImGui::DragFloat("Particle Rotation", &STRUCT_INSTANCE_PTR_WorldCanvas_WorldCanvas_Particle2D_particle2D->f_particleRotation, 0.1f);
			ImGui::DragFloat2("Particle Scale", &STRUCT_INSTANCE_PTR_WorldCanvas_WorldCanvas_Particle2D_particle2D->GLMVEC2_particleScale[0], 0.1f);

			ImGui::Spacing();
			
			ImGui::Text("Particle Motion");
			ImGui::DragFloat2("Particle Velocity", &STRUCT_INSTANCE_PTR_WorldCanvas_WorldCanvas_Particle2D_particle2D->GLMVEC2_particleVelocity[0], 0.1f);
			ImGui::DragFloat("Particle Angular Velocity", &STRUCT_INSTANCE_PTR_WorldCanvas_WorldCanvas_Particle2D_particle2D->f_particleAngularVelocity, 0.1f);
			ImGui::DragFloat2("Particle Scale Velocity", &STRUCT_INSTANCE_PTR_WorldCanvas_WorldCanvas_Particle2D_particle2D->GLMVEC2_particleScaleVelocity[0], 0.1f);

			ImGui::Spacing();
			ImGui::Text("Particle Apperance");

			ImGui::ColorEdit4("Particle Color", &STRUCT_INSTANCE_PTR_WorldCanvas_WorldCanvas_Particle2D_particle2D->GLMVEC4_particleColor[0]);
			ImGui::DragInt("Particle Texture ID", &STRUCT_INSTANCE_PTR_WorldCanvas_WorldCanvas_Particle2D_particle2D->i_particleTextureID);
			ImGui::Checkbox("Particle Fade Out", &STRUCT_INSTANCE_PTR_WorldCanvas_WorldCanvas_Particle2D_particle2D->b_ParticleFadeOut);

			ImGui::Spacing();
			ImGui::Text("Particle Physics");

			ImGui::DragFloat("Particle Drag", &STRUCT_INSTANCE_PTR_WorldCanvas_WorldCanvas_Particle2D_particle2D->f_particleDrag);
			ImGui::DragFloat("Particle Gravity Effect", &STRUCT_INSTANCE_PTR_WorldCanvas_WorldCanvas_Particle2D_particle2D->f_particleGravityEffect);
			ImGui::Checkbox("Set Particle As Active", &STRUCT_INSTANCE_PTR_WorldCanvas_WorldCanvas_Particle2D_particle2D->b_isParticleActive);

			ImGui::Spacing();
			ImGui::Text("Particle Lifetime");

			ImGui::DragFloat("Particle Lifetime", &STRUCT_INSTANCE_PTR_WorldCanvas_WorldCanvas_Particle2D_particle2D->f_particleLifetime);
			ImGui::DragFloat("Particle Age", &STRUCT_INSTANCE_PTR_WorldCanvas_WorldCanvas_Particle2D_particle2D->f_particleAge);

			ImGui::Text("Advanced");

			static constexpr unsigned int s_CE_uI__WorldCanvas_WorldCanvas_Particle2D_MAX_MATERIALS_REACHED_FOR_PARTICLE_AS_PARTICLE_COLOR_PER_WORLD_LIMIT = 5;
			static bool s_B__WorldCanvas_WorldCanvas_Particle2D_openMaxMaterialReachedForParticleAsParticleColorPerWorldLimit_SS2DERROR_DialogBox = true;

			if (ImGui::Button("Add material to Particle Object as color")) {
				OpenFileDialogPNG();

				if (m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS[index]->STRUCT_INSTANCE_VEC_UNIQUEPTR_WorldCanvas_Particle2D_Material_DETAILS.empty())
				{
					m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS[index]->STRUCT_INSTANCE_VEC_UNIQUEPTR_WorldCanvas_Particle2D_Material_DETAILS.push_back(
						std::make_unique<WorldCanvas::WorldCanvas_Particle2D::WorldCanvas_Particle2D_Material>()
					);
				}
			}

			if (
				m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS[0]->STRUCT_INSTANCE_VEC_UNIQUEPTR_WorldCanvas_Particle2D_Material_DETAILS.size() >
				s_CE_uI__WorldCanvas_WorldCanvas_Particle2D_MAX_MATERIALS_REACHED_FOR_PARTICLE_AS_PARTICLE_COLOR_PER_WORLD_LIMIT &&
				s_B__WorldCanvas_WorldCanvas_Particle2D_openMaxMaterialReachedForParticleAsParticleColorPerWorldLimit_SS2DERROR_DialogBox == true
				)
			{
				ImGui::OpenPopup("Surreal Studio (2D) Error - [WORLD CANVAS] Max materials reached for Particle Object as color");
				s_B__WorldCanvas_WorldCanvas_Particle2D_openMaxMaterialReachedForParticleAsParticleColorPerWorldLimit_SS2DERROR_DialogBox = false;
			}

			if (ImGui::BeginPopupModal("Surreal Studio (2D) Error - [WORLD CANVAS] Max materials reached for Particle Object as color", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Text(
					"[WORLD CANVAS] Max materials for Particle Object as color is %d got %d.",
					s_CE_uI__WorldCanvas_WorldCanvas_Particle2D_MAX_MATERIALS_REACHED_FOR_PARTICLE_AS_PARTICLE_COLOR_PER_WORLD_LIMIT,
					static_cast<int>(m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS[index]->STRUCT_INSTANCE_VEC_UNIQUEPTR_WorldCanvas_Particle2D_Material_DETAILS.size())
				);

				if (ImGui::Button("OK")) {
					ImGui::CloseCurrentPopup();
					m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS[index]->STRUCT_INSTANCE_VEC_UNIQUEPTR_WorldCanvas_Particle2D_Material_DETAILS.resize(
						s_CE_uI__WorldCanvas_WorldCanvas_Particle2D_MAX_MATERIALS_REACHED_FOR_PARTICLE_AS_PARTICLE_COLOR_PER_WORLD_LIMIT
					); // Clamp

					s_B__WorldCanvas_WorldCanvas_Particle2D_openMaxMaterialReachedForParticleAsParticleColorPerWorldLimit_SS2DERROR_DialogBox = true; // Reset
				}
				ImGui::EndPopup();
			}

			return true;
		}

		bool SS2DWorldCanvasPanel::DrawWorldCanvas_2DParticleEditor_Properties(const char* WorldCanvas_2DparticleOptions[], int index)
		{
			if (m_SS2DWorldCanvas_DETAILS.empty())
			{
				m_SS2DWorldCanvas_DETAILS.push_back(std::make_unique<WorldCanvas>());
			}

			auto& particles = m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS;

			// Ensure the vector can hold the requested index
			if (index < 0)
			{
				return false;
			}

			if (index >= static_cast<int>(particles.size()))
			{
				particles.resize(index + 1);

				for (int i = 0; i <= index; i++)
				{
					if (!particles[i])
					{
						particles[i] = std::make_unique<WorldCanvas::WorldCanvas_Particle2D>();
					}
				}
			}

			auto& particle = particles[index];

			if (!particle)
			{
				return false;
			}

			// Ensure the particle emitter vector is not empty
			auto& particleEmitters = particle->WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter_DETAILS;

			if (particleEmitters.empty())
			{
				particleEmitters.push_back(
					std::make_unique<WorldCanvas::WorldCanvas_Particle2D::WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter>()
				);
			}

			WorldCanvas::WorldCanvas_Particle2D::WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter* WorldCanvas_WorldCanvas_Particle2D_WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter = nullptr;

			auto& WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter_VEC =
				m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter_DETAILS;

			if (index < 0 || index >= static_cast<int>(WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter_VEC.size()))
				return false; // Out of bounds
			
			WorldCanvas_WorldCanvas_Particle2D_WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter =
				WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter_VEC[0].get();

			if (!WorldCanvas_WorldCanvas_Particle2D_WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter)
				return false;

			static bool s_B__WorldCanvas_WorldCanvas_Particle2D_WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter_openMaxParticlesReachedPerWorldLimit_SS2DERROR_DialogBox = true;

			if (ImGui::Button("Particle Editor")) ImGui::OpenPopup("World Canvas - Particle Editor");

			if (ImGui::BeginPopupModal("World Canvas - Particle Editor", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				static int s_I__WorldCanvas_ParticleEditor_ParticleEmitterTypeSelectedIndex = 0;
				const char* c_CPTR__WorldCanvas_ParticleEditor_ParticleEmitterTypeOptions[] = {
					"Point", "Circle", "Box", "Cone"
				};

				if (ImGui::CollapsingHeader("Particle Emitter", ImGuiTreeNodeFlags_DefaultOpen))
				{
					if (ImGui::BeginCombo("Particle Emitter Type", c_CPTR__WorldCanvas_ParticleEditor_ParticleEmitterTypeOptions[s_I__WorldCanvas_ParticleEditor_ParticleEmitterTypeSelectedIndex]))
					{
						for (int n = 0; n < IM_ARRAYSIZE(c_CPTR__WorldCanvas_ParticleEditor_ParticleEmitterTypeOptions); n++)
						{
							bool b_WorldCanvas_ParticleEditor_isParticleEmitterTypeSelected = (s_I__WorldCanvas_ParticleEditor_ParticleEmitterTypeSelectedIndex = n);
							if (ImGui::Selectable(c_CPTR__WorldCanvas_ParticleEditor_ParticleEmitterTypeOptions[n], b_WorldCanvas_ParticleEditor_isParticleEmitterTypeSelected))
								s_I__WorldCanvas_ParticleEditor_ParticleEmitterTypeSelectedIndex = n;

							if (b_WorldCanvas_ParticleEditor_isParticleEmitterTypeSelected == true)
								ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					switch (s_I__WorldCanvas_ParticleEditor_ParticleEmitterTypeSelectedIndex)
					{
						case 0:
						{
							m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS[index]->WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter_DETAILS[0]
								->ENUMCLASS_INSTANCE_WorldCanvas_Particle2D_ParticleEmitterType_DETAILS =
								WorldCanvas::WorldCanvas_Particle2D::WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter::WorldCanvas_Particle2D_ParticleEmitter_ParticleEmitterType::Point;
							break;
						}
						case 1:
						{
							m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS[index]->WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter_DETAILS[0]
								->ENUMCLASS_INSTANCE_WorldCanvas_Particle2D_ParticleEmitterType_DETAILS =
								WorldCanvas::WorldCanvas_Particle2D::WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter::WorldCanvas_Particle2D_ParticleEmitter_ParticleEmitterType::Circle;
							break;
						}
						case 2:
						{
							m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS[index]->WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter_DETAILS[0]
								->ENUMCLASS_INSTANCE_WorldCanvas_Particle2D_ParticleEmitterType_DETAILS =
								WorldCanvas::WorldCanvas_Particle2D::WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter::WorldCanvas_Particle2D_ParticleEmitter_ParticleEmitterType::Box;
							break;
						}
						case 3:
						{
							m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS[index]->WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter_DETAILS[0]
								->ENUMCLASS_INSTANCE_WorldCanvas_Particle2D_ParticleEmitterType_DETAILS =
								WorldCanvas::WorldCanvas_Particle2D::WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter::WorldCanvas_Particle2D_ParticleEmitter_ParticleEmitterType::Cone;
							break;
						}
						default: { std::cout << "This Particle Emitter does not exist, please try again." << std::endl; break; }
					}

					if (ImGui::CollapsingHeader("Particle Emitter Timing"))
					{
						ImGui::DragFloat("Particle Spawn Rate", &WorldCanvas_WorldCanvas_Particle2D_WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter->f_SpawnRate, 0.1f);
						ImGui::DragFloat("Particle Start Delay", &WorldCanvas_WorldCanvas_Particle2D_WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter->f_StartDelay, 0.1f);
						ImGui::DragFloat("Particle Duration", &WorldCanvas_WorldCanvas_Particle2D_WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter->f_Duration, 0.1f);
					}
					ImGui::Separator();

					ImGui::Checkbox("Particle Looping", &WorldCanvas_WorldCanvas_Particle2D_WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter->b_Looping);
					ImGui::Spacing();
					ImGui::Separator();

					if (ImGui::CollapsingHeader("Particle Emitter Size and Direction"))
					{
						ImGui::DragFloat2("Particle Size", &WorldCanvas_WorldCanvas_Particle2D_WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter->GLMVEC2_Size[0], 0.1f);
						ImGui::DragFloat2("Particle Direction", &WorldCanvas_WorldCanvas_Particle2D_WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter->GLMVEC2_Direction[0], 0.1f);
					}
					ImGui::Separator();

					if (ImGui::CollapsingHeader("Particle Emitter Randomization"))
					{
						ImGui::DragFloat("Particle Angle Variance", &WorldCanvas_WorldCanvas_Particle2D_WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter->f_AngleVariance, 0.1f);
						ImGui::DragFloat("Particle Speed Maximum", &WorldCanvas_WorldCanvas_Particle2D_WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter->f_SpeedMax, 0.1f);
						ImGui::DragFloat("Particle Speed Minimum", &WorldCanvas_WorldCanvas_Particle2D_WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter->f_SpeedMin, 0.1f);
					}
					ImGui::Separator();

					ImGui::DragInt("Set Maximum Particles", &WorldCanvas_WorldCanvas_Particle2D_WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter->i_MaxParticles, 0.1f);
					if (WorldCanvas_WorldCanvas_Particle2D_WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter->i_MaxParticles > m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS.size())
					{
						ImGui::OpenPopup("Surreal Studio (2D) Error - [WORLD CANVAS - PARTICLE EDITOR] Max amount of Particles (Objects) reached per World");
						s_B__WorldCanvas_WorldCanvas_Particle2D_WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter_openMaxParticlesReachedPerWorldLimit_SS2DERROR_DialogBox = false;
					}

					if (ImGui::BeginPopupModal("Surreal Studio (2D) Error - [WORLD CANVAS - PARTICLE EDITOR] Max amount of Particles (Objects) reached per World", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text(
							"[WORLD CANVAS - PARTICLE EDITOR] Max amount of Particle Objects per World is %d got %d.",
							WorldCanvas_WorldCanvas_Particle2D_WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter->i_MaxParticles,
							static_cast<int>(m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS.size())
						);

						if (ImGui::Button("OK")) {
							ImGui::CloseCurrentPopup();
							m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS.resize(WorldCanvas_WorldCanvas_Particle2D_WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter->i_MaxParticles); // Clamp
							s_B__WorldCanvas_WorldCanvas_Particle2D_WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter_openMaxParticlesReachedPerWorldLimit_SS2DERROR_DialogBox = true; // Reset
						}
						ImGui::EndPopup();	
					}

					ImGui::Separator();
					ImGui::Spacing();
					ImGui::Text("Particle Physics");
					ImGui::Checkbox("Use Gravity for Particle", &WorldCanvas_WorldCanvas_Particle2D_WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter->b_UseGravity);
					ImGui::DragFloat("Particle Gravity Scale", &WorldCanvas_WorldCanvas_Particle2D_WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter->f_GravityScale, 0.1f);
				}

				ImGui::Spacing();
				if (ImGui::Button("Apply")) {
					// Save all the data?
					m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter_DETAILS.push_back(
						std::make_unique<WorldCanvas::WorldCanvas_Particle2D::WorldCanvas_WorldCanvas_Particle2D_ParticleEmitter>()
					);
					m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Particle2D_DETAILS.push_back(std::make_unique<WorldCanvas::WorldCanvas_Particle2D>());
					ImGui::CloseCurrentPopup();
				}

				ImGui::SameLine();
				if (ImGui::Button("Cancel")) {
					// Dont save the changes?
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}

			return true;
		}

		bool SS2DWorldCanvasPanel::DrawWorldCanvas_2DLightEditor_Properties()
		{
			if (m_SS2DWorldCanvas_DETAILS.empty())
				m_SS2DWorldCanvas_DETAILS.push_back(std::make_unique<WorldCanvas>());

			if (m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS.empty())
				m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS.push_back(std::make_unique<WorldCanvas::WorldCanvas_Lighting2D>());

			// ///////////////////////////////////////////////////////////////////////////////////
			// Variables for DrawWorldCanvas_2DLightEditor_Properties function
			// /////////////////////////////////////////////////////////////////////////////////

			WorldCanvas::WorldCanvas_Lighting2D* STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting = nullptr;
			STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting = m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS[0].get();

			if (STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting == nullptr)
				return false;

			static constexpr unsigned int s_CE_uI__WorldCanvas_Lighting2D_WorldCanvas_2DLightEditor_Properties_MAX_LIGHTS_PER_WORLD_LIMIT = 10;
			static int s_I__WorldCanvas_WorldCanvas_2DLightEditor_Properties_selectedLightIndex = 0;
			const char* c_CPTR__WorldCanvas_WorldCanvas_2DLightEditorProperties_LightingOptions[] = {
				"WorldEnvironmentLight", "SurrealAmbientLight",
				"SurrealPointLight", "SurrealSpotLight", "SurrealAreaLight",
				"SurrealEmissiveLight"
			};
			static bool s_B__WorldCanvas_WorldCanvas_2DLightEditorProperties_openMaxLightsReachedPerWorldLimit_SS2DERROR_DialogBox = true;

			if (ImGui::Button("Light Editor")) ImGui::OpenPopup("World Canvas - Light Editor (2D)");

			if (ImGui::BeginPopupModal("World Canvas - Light Editor (2D)", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				if (ImGui::CollapsingHeader("Lighting Creation", ImGuiTreeNodeFlags_DefaultOpen))
				{
					if (ImGui::BeginCombo("Lighting Options", c_CPTR__WorldCanvas_WorldCanvas_2DLightEditorProperties_LightingOptions[s_I__WorldCanvas_WorldCanvas_2DLightEditor_Properties_selectedLightIndex]))
					{
						for (int n = 0; n < IM_ARRAYSIZE(c_CPTR__WorldCanvas_WorldCanvas_2DLightEditorProperties_LightingOptions); n++)
						{
							bool b_WorldCanvas_WorldCanvas_2DLightEditorProperties_isLightingOptionSelected = (s_I__WorldCanvas_WorldCanvas_2DLightEditor_Properties_selectedLightIndex == n);
							if (ImGui::Selectable(c_CPTR__WorldCanvas_WorldCanvas_2DLightEditorProperties_LightingOptions[n], b_WorldCanvas_WorldCanvas_2DLightEditorProperties_isLightingOptionSelected))
								s_I__WorldCanvas_WorldCanvas_2DLightEditor_Properties_selectedLightIndex = n;
							 
							if (b_WorldCanvas_WorldCanvas_2DLightEditorProperties_isLightingOptionSelected == true)
								ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					if (
						m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS.size() > s_CE_uI__WorldCanvas_Lighting2D_WorldCanvas_2DLightEditor_Properties_MAX_LIGHTS_PER_WORLD_LIMIT &&
						s_B__WorldCanvas_WorldCanvas_2DLightEditorProperties_openMaxLightsReachedPerWorldLimit_SS2DERROR_DialogBox == true
						)
					{
						ImGui::OpenPopup("Surreal Studio (2D) Error - [WORLD CANVAS - LIGHTING EDITOR] Max amount of Light Objects reached per World");
						s_B__WorldCanvas_WorldCanvas_2DLightEditorProperties_openMaxLightsReachedPerWorldLimit_SS2DERROR_DialogBox = false;
					}

					if (ImGui::Button("Create Lighting Object"))
					{
						if (
							!m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS.empty() && m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS.size() >
							s_CE_uI__WorldCanvas_Lighting2D_WorldCanvas_2DLightEditor_Properties_MAX_LIGHTS_PER_WORLD_LIMIT &&
							s_B__WorldCanvas_WorldCanvas_2DLightEditorProperties_openMaxLightsReachedPerWorldLimit_SS2DERROR_DialogBox == false
							)
						{
							m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS.push_back(std::make_unique<WorldCanvas::WorldCanvas_Lighting2D>());
						}
						else if (
							m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS.size() > s_CE_uI__WorldCanvas_Lighting2D_WorldCanvas_2DLightEditor_Properties_MAX_LIGHTS_PER_WORLD_LIMIT &&
							s_B__WorldCanvas_WorldCanvas_2DLightEditorProperties_openMaxLightsReachedPerWorldLimit_SS2DERROR_DialogBox == true
							)
						{
							ImGui::OpenPopup("Surreal Studio (2D) Error - [WORLD CANVAS - LIGHTING EDITOR] Max amount of Light Objects reached per World");
							s_B__WorldCanvas_WorldCanvas_2DLightEditorProperties_openMaxLightsReachedPerWorldLimit_SS2DERROR_DialogBox = false;
						}
					}

					if (ImGui::BeginPopupModal("Surreal Studio (2D) Error - [WORLD CANVAS - LIGHTING EDITOR] Max amount of Light Objects reached per World", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text(
							"[WORLD CANVAS - LIGHITNG EDITOR] Max amount of Light Objects per World is %d got %d.",
							s_CE_uI__WorldCanvas_Lighting2D_WorldCanvas_2DLightEditor_Properties_MAX_LIGHTS_PER_WORLD_LIMIT,
							static_cast<int>(m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS.size())
						);

						if (ImGui::Button("OK")) {
							ImGui::CloseCurrentPopup();
							m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS.resize(s_CE_uI__WorldCanvas_Lighting2D_WorldCanvas_2DLightEditor_Properties_MAX_LIGHTS_PER_WORLD_LIMIT); // Clamp
							s_B__WorldCanvas_WorldCanvas_2DLightEditorProperties_openMaxLightsReachedPerWorldLimit_SS2DERROR_DialogBox = true; // Reset
						}
						ImGui::EndPopup();
					}
				}

				if (s_I__WorldCanvas_WorldCanvas_2DLightEditor_Properties_selectedLightIndex == 0)
				{
					m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS[0]->STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightingType_DETAILS =
						WorldCanvas::WorldCanvas_Lighting2D::WorldCanvas_WorldCanvas_Lighting2D_LightingType::WorldEnvironmentLight;
					DrawWorldCanvas_LightProperties(c_CPTR__WorldCanvas_WorldCanvas_2DLightEditorProperties_LightingOptions, s_I__WorldCanvas_WorldCanvas_2DLightEditor_Properties_selectedLightIndex);
				}
				else if (s_I__WorldCanvas_WorldCanvas_2DLightEditor_Properties_selectedLightIndex == 1)
				{
					m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS[0]->STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightingType_DETAILS =
						WorldCanvas::WorldCanvas_Lighting2D::WorldCanvas_WorldCanvas_Lighting2D_LightingType::SurrealAmbientLight;
					DrawWorldCanvas_LightProperties(c_CPTR__WorldCanvas_WorldCanvas_2DLightEditorProperties_LightingOptions, s_I__WorldCanvas_WorldCanvas_2DLightEditor_Properties_selectedLightIndex);
				}
				else if (s_I__WorldCanvas_WorldCanvas_2DLightEditor_Properties_selectedLightIndex == 2)
				{
					m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS[0]->STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightingType_DETAILS =
						WorldCanvas::WorldCanvas_Lighting2D::WorldCanvas_WorldCanvas_Lighting2D_LightingType::SurrealPointLight;
					DrawWorldCanvas_LightProperties(c_CPTR__WorldCanvas_WorldCanvas_2DLightEditorProperties_LightingOptions, s_I__WorldCanvas_WorldCanvas_2DLightEditor_Properties_selectedLightIndex);
				}
				else if (s_I__WorldCanvas_WorldCanvas_2DLightEditor_Properties_selectedLightIndex == 3)
				{
					m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS[0]->STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightingType_DETAILS =
						WorldCanvas::WorldCanvas_Lighting2D::WorldCanvas_WorldCanvas_Lighting2D_LightingType::SurrealSpotLight;
					DrawWorldCanvas_LightProperties(c_CPTR__WorldCanvas_WorldCanvas_2DLightEditorProperties_LightingOptions, s_I__WorldCanvas_WorldCanvas_2DLightEditor_Properties_selectedLightIndex);
				}
				else if (s_I__WorldCanvas_WorldCanvas_2DLightEditor_Properties_selectedLightIndex == 4)
				{
					m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS[0]->STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightingType_DETAILS =
						WorldCanvas::WorldCanvas_Lighting2D::WorldCanvas_WorldCanvas_Lighting2D_LightingType::SurrealAreaLight;
					DrawWorldCanvas_LightProperties(c_CPTR__WorldCanvas_WorldCanvas_2DLightEditorProperties_LightingOptions, s_I__WorldCanvas_WorldCanvas_2DLightEditor_Properties_selectedLightIndex);
				}
				else if (s_I__WorldCanvas_WorldCanvas_2DLightEditor_Properties_selectedLightIndex == 5)
				{
					m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS[0]->STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightingType_DETAILS =
						WorldCanvas::WorldCanvas_Lighting2D::WorldCanvas_WorldCanvas_Lighting2D_LightingType::SurrealEmissiveLight;
					DrawWorldCanvas_LightProperties(c_CPTR__WorldCanvas_WorldCanvas_2DLightEditorProperties_LightingOptions, s_I__WorldCanvas_WorldCanvas_2DLightEditor_Properties_selectedLightIndex);
				}
				
				// LOL
				std::string horribleCodeText = "AS LONG AS IT WORKS, THATS WHAT MATTERS";
				std::cout << horribleCodeText << " (at line) " << __LINE__ << " (file) " << __FILE__ << " (function) " << __FUNCTION__ <<  ".\n" << std::endl;
				if (ImGui::CollapsingHeader("Lighting Properties", ImGuiTreeNodeFlags_DefaultOpen))
				{
					ImGui::Text("%s Lighting Properties", c_CPTR__WorldCanvas_WorldCanvas_2DLightEditorProperties_LightingOptions[s_I__WorldCanvas_WorldCanvas_2DLightEditor_Properties_selectedLightIndex]);

					// Position/Direction
					ImGui::Text("Light Position/Direction");
					ImGui::DragFloat2("Light Position", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->position[0], 0.1f);
					ImGui::DragFloat2("Light Direction", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->direction[0], 0.1f);
					ImGui::Spacing();

					ImGui::Text("Light Appearance");
					ImGui::DragFloat("Light Intensity", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->intensity, 0.1f);
					ImGui::ColorEdit4("Light Color (RGBA)", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->color[0]);
					ImGui::Spacing();

					ImGui::Text("(SPOT LIGHT/POINT LIGHT SPECIFC) Radius/Angle");
					ImGui::DragFloat("Light Radius", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->radius, 0.1f);
					ImGui::DragFloat("Light Angle", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->angle, 0.1f);
					ImGui::Spacing();

					if (ImGui::CollapsingHeader("Advanced"))
					{
						ImGui::Spacing();
						ImGui::Text("Light Falloff / Attenuation");
						ImGui::DragFloat("Constant", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightAttenuation_DETAILS.constant, 0.1f);
						ImGui::DragFloat("Linear", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightAttenuation_DETAILS.linear, 0.1f);
						ImGui::DragFloat("Quadratic", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightAttenuation_DETAILS.quadratic, 0.1f);
						ImGui::Spacing();

						ImGui::Text("Light Shadow Mapping");
						ImGui::Checkbox("Casts Shadows", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->castsShadows);
						ImGui::DragFloat("Shadow Softness", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->shadowSoftness, 0.1f);
						ImGui::DragFloat("Shadow Bias", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->shadowBias, 0.1f);
						ImGui::Spacing();

						ImGui::Text("Light Spread");
						ImGui::DragFloat("Light Cone Angle (Spot Light specific",
							&STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightShape_DETAILS.coneAngle, 0.1f
						);
						ImGui::DragFloat("Light Width (Area Light Specific)",
							&STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightShape_DETAILS.width, 0.1f
						);
						ImGui::DragFloat("Light Height (Area Light Specific)",
							&STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_LightShape_DETAILS.height, 0.1f
						);
						ImGui::Spacing();

						ImGui::Text("Light Flickering");
						ImGui::DragFloat("Light Flickering Intensity Maximum", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->flickerIntensityMaximum, 0.1f);
						ImGui::DragFloat("Light Flickering Intensity Minimum", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->flickerIntensityMinimum, 0.1f);
						ImGui::DragFloat("Light Flickering Speed", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->flickerSpeed, 0.1f);
						ImGui::Spacing();

						ImGui::Text("Light Gradient");
						ImGui::ColorEdit4("Color Start", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->GLMVEC4_colorStart[0]);
						ImGui::ColorEdit4("Color End", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->GLMVEC4_colorEnd[0]);
						ImGui::DragFloat("Gradient Radius", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->gradientRadius, 0.1f);
						ImGui::DragFloat("Light Gradient Temperature", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->tempature, 0.1f);
						ImGui::Spacing();

						ImGui::Text("Light Animation / Motion");
						ImGui::DragFloat2("Movement Vector", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->GLMVEC2_movementVector[0], 0.1f);
						ImGui::DragFloat("Pulse Amplitude", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->pulseAmplitude, 0.1f);
						ImGui::DragFloat("Pulse Frequency", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->pulseFrequency, 0.1f);
						ImGui::Spacing();

						ImGui::Text("Light Layering / Blendering");
						ImGui::DragInt("Layer Mask", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->layerMask, 0.1f);
						ImGui::DragFloat("Intensity Blend", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->intensityBlend, 0.1f);
						ImGui::Spacing();

						ImGui::Text("Light Glow");
						ImGui::DragFloat("Glow Radius", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->glowRadius, 0.1f);
						ImGui::DragFloat("Glow Intensity", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->glowIntensity, 0.1f);
						ImGui::ColorEdit4("Glow Color", &STRUCT_INSTANCE__WorldCanvas_WorldCanvas_Lighting2D_lighting->GLMVEC4_glowColor[0]);
						ImGui::Spacing();
					}
				}

				ImGui::Spacing();
				if (ImGui::Button("Apply")) {
					// Save all the data?
					m_SS2DWorldCanvas_DETAILS[0]->WorldCanvas_WorldCanvas_Lighting2D_DETAILS.push_back(std::make_unique<WorldCanvas::WorldCanvas_Lighting2D>());
					ImGui::CloseCurrentPopup();
				}

				ImGui::SameLine();
				if (ImGui::Button("Cancel")) {
					// Dont save all the data/changes made?
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}
			return true;
		}

		bool SS2DWorldCanvasPanel::DrawSS2DWorldCanvasPanel()
		{
			// Only open popup once when requested
			if (b_WorldCanvas_isWindowOpen)
			{
				ImGui::OpenPopup("World Canvas");
			}

			// Draw the popup if it is open
			if (ImGui::BeginPopupModal("World Canvas", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				try { DrawWorldGroundSettings(); }
				catch (const std::exception& e) { SS2DERROR(e.what()); return false; }
				catch (...) { SS2DERROR("Unknown exception occurred!"); return false; }

				try { DrawWorldMiddleGroundSettings(); }
				catch (const std::exception& e) { SS2DERROR(e.what()); return false; }
				catch (...) { SS2DERROR("Unknown exception occurred!"); return false; }

				try { DrawWorldSkySettings(); }
				catch (const std::exception& e) { SS2DERROR(e.what()); return false; }
				catch (...) { SS2DERROR("Unknown exception occurred!"); return false; }

				try { DrawWorldCanvas_CameraCreation(); }
				catch (const std::exception& e) { SS2DERROR(e.what()); return false; }
				catch (...) { SS2DERROR("Unknown exception occurred!"); return false; }

				try { DrawWorldCanvas_LightCreation(); }
				catch (const std::exception& e) { SS2DERROR(e.what()); return false; }
				catch (...) { SS2DERROR("Unknown exception occurred!"); return false; }

				try { DrawWorldCanvas_2DParticleCreation(); }
				catch (const std::exception& e) { SS2DERROR(e.what()); return false; }
				catch (...) { SS2DERROR("Unknown exception occurred!"); return false; }

				try
				{
					if (ImGui::Button("Light Editor"))
					{
						DrawWorldCanvas_2DLightEditor_Properties();
					}
				}
				catch (const std::exception& e) { SS2DERROR(e.what()); return false; }
				catch (...) { SS2DERROR("Unknown exception occurred!"); return false; }

				ImGui::Spacing();

				// Apply button
				if (ImGui::Button("Apply"))
				{
					m_SS2DWorldCanvas_DETAILS.push_back(std::make_unique<WorldCanvas>());
					ImGui::CloseCurrentPopup();
					b_WorldCanvas_isWindowOpen = false;  // Close the panel
				}

				ImGui::SameLine();

				// Cancel button
				if (ImGui::Button("Cancel"))
				{
					ImGui::CloseCurrentPopup();
					b_WorldCanvas_isWindowOpen = false;  // Close the panel
				}

				ImGui::EndPopup();
			}

			return true;
		}

	}
}