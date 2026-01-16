#include "SceneManagerPanel3D.h"
#include "../src/SurrealStudio3D/src/SS3DEngineDefines.h"

#include <imgui.h>
#include <stdexcept>
#include <iostream>
#include <memory>

namespace SurrealStudio {

	namespace SurrealStudio3D {

		bool SceneManagerPanel3D::SceneManagerPanel3D_DrawLighting3DProperties(const char* lighting3D_options[], int index)
		{
			if (!lighting3D_options || index < 0 || index >= static_cast<int>(m_SceneManagerPanel3D_Lighting3D_DETAILS.size()))
				return false;

			Lighting3D* STRUCT_INSTANCE__Lighting3D_lighting3D = m_SceneManagerPanel3D_Lighting3D_DETAILS[index].get();
			if (!STRUCT_INSTANCE__Lighting3D_lighting3D)
				return false;

			ImGui::Text("%s Properties", lighting3D_options[index]);

			ImGui::DragFloat3("Position", &STRUCT_INSTANCE__Lighting3D_lighting3D->lightPosition[0], 0.1f);
			ImGui::DragFloat3("Direction", &STRUCT_INSTANCE__Lighting3D_lighting3D->lightDirection[0], 0.1f);
			
			ImGui::ColorEdit4("Light Color", &STRUCT_INSTANCE__Lighting3D_lighting3D->lightColor[0], 0.1f);
			
			ImGui::DragFloat("Intensity", &STRUCT_INSTANCE__Lighting3D_lighting3D->intensity, 0.1f);
			ImGui::DragFloat("Radius", &STRUCT_INSTANCE__Lighting3D_lighting3D->radius, 0.1f);
			ImGui::DragFloat("Angle", &STRUCT_INSTANCE__Lighting3D_lighting3D->angle, 0.1f);

			ImGui::Checkbox("Casts Shadows", &STRUCT_INSTANCE__Lighting3D_lighting3D->castsShadows);

			if (index == 0) STRUCT_INSTANCE__Lighting3D_lighting3D->Lighting3D_LightingType_DETAILS = Lighting3D::LightingType::WorldEnvironmentLight;
			if (index == 1) STRUCT_INSTANCE__Lighting3D_lighting3D->Lighting3D_LightingType_DETAILS = Lighting3D::LightingType::SurrealAmbientLight;
			if (index == 2) STRUCT_INSTANCE__Lighting3D_lighting3D->Lighting3D_LightingType_DETAILS = Lighting3D::LightingType::SurrealPointLight;
			if (index == 3) STRUCT_INSTANCE__Lighting3D_lighting3D->Lighting3D_LightingType_DETAILS = Lighting3D::LightingType::SurrealSpotLight;
			if (index == 4) STRUCT_INSTANCE__Lighting3D_lighting3D->Lighting3D_LightingType_DETAILS = Lighting3D::LightingType::SurrealAreaLight;
			if (index == 5) STRUCT_INSTANCE__Lighting3D_lighting3D->Lighting3D_LightingType_DETAILS = Lighting3D::LightingType::SurrealEmissiveLight;

			return true;
		}

		bool SceneManagerPanel3D::SceneManagerPanel3D_DrawCamera3DProperties(const char* camera3D_options[], int index)
		{
			if (!camera3D_options || index < 0 || index >= static_cast<int>(m_SceneManagerPanel3D_Camera3D_DETAILS.size()))
				return false;

			Camera3D* STRUCT_INSTANCE__Camera3D_camera3D = m_SceneManagerPanel3D_Camera3D_DETAILS[index].get();
			if (!STRUCT_INSTANCE__Camera3D_camera3D)
				return false;

			ImGui::Text("%s Properties", camera3D_options[index]);

			ImGui::DragFloat3("Position", &STRUCT_INSTANCE__Camera3D_camera3D->cameraPosition[0], 0.1f);
			ImGui::DragFloat3("Viewport Size", &STRUCT_INSTANCE__Camera3D_camera3D->viewportSize[0], 0.1f);
			ImGui::DragFloat3("Camera Target", &STRUCT_INSTANCE__Camera3D_camera3D->cameraTarget[0], 0.1f);

			ImGui::DragFloat("Rotation", &STRUCT_INSTANCE__Camera3D_camera3D->rotation, 0.1f);
			ImGui::DragFloat("Camera Zoom", &STRUCT_INSTANCE__Camera3D_camera3D->zoom, 0.1f);

			ImGui::DragFloat3("Camera Minimum Bounds", &STRUCT_INSTANCE__Camera3D_camera3D->cameraMinimumBounds[0], 0.1f);
			ImGui::DragFloat3("Camera Maximum Bounds", &STRUCT_INSTANCE__Camera3D_camera3D->cameraMaximumBounds[0], 0.1f);

			ImGui::DragFloat("Near Clip", &STRUCT_INSTANCE__Camera3D_camera3D->nearClip, 0.1f);
			ImGui::DragFloat("Far Clip", &STRUCT_INSTANCE__Camera3D_camera3D->farClip, 0.1f);

			ImGui::Spacing();
			ImGui::Text("Orthographic Bounds (Orthographic Camera Specific)");

			ImGui::DragFloat("Left", &STRUCT_INSTANCE__Camera3D_camera3D->orthographicBoundsLeft, 0.1f);
			ImGui::DragFloat("Right", &STRUCT_INSTANCE__Camera3D_camera3D->orthographicBoundsRight, 0.1f);
			ImGui::DragFloat("Bottom", &STRUCT_INSTANCE__Camera3D_camera3D->orthographicBoundsBottom, 0.1f);
			ImGui::DragFloat("Top", &STRUCT_INSTANCE__Camera3D_camera3D->orthographicBoundsTop, 0.1f);

			if (index == 0) m_SceneManagerPanel3D_Camera3D_DETAILS[0]->Camera3D_CameraType_DETAILS = Camera3D::CameraType::Normal;
			if (index == 1) m_SceneManagerPanel3D_Camera3D_DETAILS[0]->Camera3D_CameraType_DETAILS = Camera3D::CameraType::Orthographic;

			return true;
		}

		bool SceneManagerPanel3D::SceneManagerPanel3D_DrawSceneCreation()
		{
			if (ImGui::Button("Create new main Scene"))
			{
				SS3D_INFO("New scene created!");
			}

			if (ImGui::Button("Create new main Subscene"))
			{
				SS3D_INFO("New main subscene created!");
			}

			if (ImGui::Button("Create new World"))
			{
				SS3D_INFO("New World created!");
			}
			return true;
		}

		bool SceneManagerPanel3D::SceneManagerPanel3D_DrawLighting3DCreation()
		{
			if (m_SceneManagerPanel3D_Camera3D_DETAILS.empty())
				m_SceneManagerPanel3D_Lighting3D_DETAILS.push_back(std::make_unique<Lighting3D>());

			static constexpr unsigned int s_CE_uI__Lighting3D_MAX_LIGHTS_PER_WORLD_LIMIT = 10;
			static int s_I__Lighting3D_selectedLight3DIndex = 0;
			const char* c_CPTR__Lighting3D_lightingOptions[] = {
				"World Environment Light", "Surreal Ambient Light", "Surreal Point Light",
				"Surreal Spot Light", "Surreal Area Light", "Surreal Emissive Light"
			};
			static bool s_B__Lighting3D_openMaxLightsReachedPerWorldLimit_SS3DERROR_DialogBox = true;

			if (ImGui::CollapsingHeader("Lighting"))
			{
				if (ImGui::BeginCombo("Lighting Options", c_CPTR__Lighting3D_lightingOptions[s_I__Lighting3D_selectedLight3DIndex]))
				{
					for (int n = 0; n < IM_ARRAYSIZE(c_CPTR__Lighting3D_lightingOptions); n++)
					{
						bool b_Lighting3D_isLightSelected = (s_I__Lighting3D_selectedLight3DIndex == n);
						if (ImGui::Selectable(c_CPTR__Lighting3D_lightingOptions[n], b_Lighting3D_isLightSelected))
							s_I__Lighting3D_selectedLight3DIndex = n;

						if (b_Lighting3D_isLightSelected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

				if (m_SceneManagerPanel3D_Lighting3D_DETAILS.size() > s_CE_uI__Lighting3D_MAX_LIGHTS_PER_WORLD_LIMIT && s_B__Lighting3D_openMaxLightsReachedPerWorldLimit_SS3DERROR_DialogBox == true)
				{
					ImGui::OpenPopup("Surreal Studio (3D) Error [SCENE MANAGER PANEL (LIGHTING)] - Max Lights Per World Reached");
					s_B__Lighting3D_openMaxLightsReachedPerWorldLimit_SS3DERROR_DialogBox = false;
				}

				if (ImGui::BeginPopupModal("Surreal Studio (3D) Error - Max Lights Per World Reached", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text(
						"[SCENE MANAGER PANEL (LIGHTING)] Max amount of Lighting Objects per world is %d, got %d.", s_CE_uI__Lighting3D_MAX_LIGHTS_PER_WORLD_LIMIT,
						static_cast<int>(m_SceneManagerPanel3D_Lighting3D_DETAILS.size())
					);

					if (ImGui::Button("OK")) {
						ImGui::CloseCurrentPopup();
						m_SceneManagerPanel3D_Lighting3D_DETAILS.resize(s_CE_uI__Lighting3D_MAX_LIGHTS_PER_WORLD_LIMIT);  // Clamp
						s_B__Lighting3D_openMaxLightsReachedPerWorldLimit_SS3DERROR_DialogBox = true;  // Reset
					}
					ImGui::EndPopup();
				}

				if (m_SceneManagerPanel3D_Lighting3D_DETAILS.size() < s_CE_uI__Lighting3D_MAX_LIGHTS_PER_WORLD_LIMIT && !s_B__Lighting3D_openMaxLightsReachedPerWorldLimit_SS3DERROR_DialogBox)
				{
					m_SceneManagerPanel3D_Lighting3D_DETAILS.push_back(std::make_unique<Lighting3D>());
					m_SceneManagerPanel3D_Lighting3D_DETAILS[0]->lightName = c_CPTR__Lighting3D_lightingOptions[s_I__Lighting3D_selectedLight3DIndex];
					m_SceneManagerPanel3D_Lighting3D_DETAILS[0]->lightIndex = s_I__Lighting3D_selectedLight3DIndex;
				}

				ImGui::Spacing();
				SceneManagerPanel3D_DrawLighting3DProperties(c_CPTR__Lighting3D_lightingOptions, s_I__Lighting3D_selectedLight3DIndex);
			}
			
			return true;
		}

		bool SceneManagerPanel3D::SceneManagerPanel3D_DrawCamera3DCreation()
		{
			if (m_SceneManagerPanel3D_Camera3D_DETAILS.empty())
				m_SceneManagerPanel3D_Camera3D_DETAILS.push_back(std::make_unique<Camera3D>());

			static constexpr unsigned int s_CE_uI__Camera3D_MAX_CAMERAS_REACHED_PER_WORLD_LIMIT = 3;
			static int s_I__Camera3D_selectedCamera3DIndex = 0;
			const char* c_CPTR__Camera3D_camera3DOptions[] = {
				"Normal", "Orthographic"
			};
			static bool s_B__Camera3D_openMaxCamerasReachedPerWorldLimit_SS3DERROR_DialogBox = true;

			if (ImGui::CollapsingHeader("Camera"))
			{
				if (ImGui::BeginCombo("Camera Options", c_CPTR__Camera3D_camera3DOptions[s_I__Camera3D_selectedCamera3DIndex]))
				{
					for (int n = 0; n < IM_ARRAYSIZE(c_CPTR__Camera3D_camera3DOptions); n++)
					{
						bool b_Camera3D_isCameraSelected = (s_I__Camera3D_selectedCamera3DIndex == n);
						if (ImGui::Selectable(c_CPTR__Camera3D_camera3DOptions[n], b_Camera3D_isCameraSelected))
							s_I__Camera3D_selectedCamera3DIndex = n;

						if (b_Camera3D_isCameraSelected == true)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

				if (m_SceneManagerPanel3D_Camera3D_DETAILS.size() < s_CE_uI__Camera3D_MAX_CAMERAS_REACHED_PER_WORLD_LIMIT && s_B__Camera3D_openMaxCamerasReachedPerWorldLimit_SS3DERROR_DialogBox == true)
				{
					ImGui::OpenPopup("Surreal Studio (3D) Error [SCENE MANAGER PANEL (LIGHTING)] - Max Cameras Per World Reached");
					s_B__Camera3D_openMaxCamerasReachedPerWorldLimit_SS3DERROR_DialogBox = false;
				}

				if (ImGui::BeginPopupModal("Surreal Studio (3D) Error - Max Cameras Per World Reached", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text(
						"[SCENE MANAGER PANEL (CAMERA)] Max amount of Camera Objects per World is %d, got %d.", s_CE_uI__Camera3D_MAX_CAMERAS_REACHED_PER_WORLD_LIMIT,
						static_cast<int>(m_SceneManagerPanel3D_Camera3D_DETAILS.size())
					);

					if (ImGui::Button("OK")) {
						ImGui::CloseCurrentPopup();
						m_SceneManagerPanel3D_Camera3D_DETAILS.resize(s_CE_uI__Camera3D_MAX_CAMERAS_REACHED_PER_WORLD_LIMIT);  // Clamp
						s_B__Camera3D_openMaxCamerasReachedPerWorldLimit_SS3DERROR_DialogBox = true; // Reset
					}
					ImGui::EndPopup();
				}

				if (m_SceneManagerPanel3D_Camera3D_DETAILS.size() < s_CE_uI__Camera3D_MAX_CAMERAS_REACHED_PER_WORLD_LIMIT && !s_B__Camera3D_openMaxCamerasReachedPerWorldLimit_SS3DERROR_DialogBox)
				{
					m_SceneManagerPanel3D_Camera3D_DETAILS.push_back(std::make_unique<Camera3D>());
					m_SceneManagerPanel3D_Camera3D_DETAILS[0]->cameraName = c_CPTR__Camera3D_camera3DOptions[s_I__Camera3D_selectedCamera3DIndex];
					m_SceneManagerPanel3D_Camera3D_DETAILS[0]->cameraIndex = s_I__Camera3D_selectedCamera3DIndex;
				}

				ImGui::Spacing();
				SceneManagerPanel3D_DrawCamera3DProperties(c_CPTR__Camera3D_camera3DOptions, s_I__Camera3D_selectedCamera3DIndex);
			}

			return true;
		}

		bool SceneManagerPanel3D::SceneManagerPanel3D_DrawSceneManagerPanel3D()
		{
			ImGui::Begin("Scene Manager Panel");

			try
			{
				if (!SceneManagerPanel3D_DrawSceneCreation())
				{
					ImGui::Text("No scene currently made.");
				}
			}
			catch (const std::exception& e) {
				SS3D_ERROR(e.what()); return false;
			}
			catch (...) { SS3D_ERROR("Some unknown exception ocurred!"); return false; }

			try { SceneManagerPanel3D_DrawLighting3DCreation(); }
			catch (const std::exception& e) {
				SS3D_ERROR(e.what()); return false;
			}
			catch (...) { SS3D_ERROR("Some unknown exception ocurred!"); return false; }

			try { SceneManagerPanel3D_DrawCamera3DCreation(); }
			catch (const std::exception& e) {
				SS3D_ERROR(e.what()); return false;
			}
			catch (...) { SS3D_ERROR("Some unknown exception ocurred!"); return false; }

			ImGui::End();
			return true;
		}
	}
}