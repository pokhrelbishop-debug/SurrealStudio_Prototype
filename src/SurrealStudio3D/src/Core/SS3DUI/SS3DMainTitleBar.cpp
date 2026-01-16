#include "SS3DMainTitleBar.h"
#include "../src/SurrealStudio3D//src/SS3DEngineDefines.h"

#define GLFW_INCLUDE_NONE

#include <exception>
#include <imgui.h>
#include <GLFW/glfw3.h>

#include <Windows.h>

namespace SurrealStudio {

	namespace SurrealStudio3D {

#pragma region Uitlity Functions

		std::wstring OpenFileDialogSSProj(HWND owner = nullptr)
		{
			wchar_t szFile[MAX_PATH] = {}; // buffer for file name

			OPENFILENAMEW ofn{};
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = owner;
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = MAX_PATH;

			// Filter for .ssproj files only (double null terminator required)
			ofn.lpstrFilter = L"SSPROJ Files (*.ssproj)\0*.ssproj\0\0";
			ofn.nFilterIndex = 1;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

			if (GetOpenFileNameW(&ofn))
			{
				return szFile; // file selected
			}

			return {}; // empty string if canceled
		}

		std::wstring SaveAsFileDialogSSProj(HWND owner = nullptr)
		{
			wchar_t szFile[MAX_PATH] = {}; // buffer for file name

			OPENFILENAMEW ofn{};
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = owner;
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = MAX_PATH;

			// Filter for .ssproj files only (double null terminator required)
			ofn.lpstrFilter = L"SSPROJ Files (*.ssproj)\0*.ssproj\0\0";
			ofn.nFilterIndex = 1;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
			ofn.lpstrDefExt = L"ssproj"; // default extension

			if (GetSaveFileNameW(&ofn))
			{
				return szFile; // user selected a file path
			}

			return {}; // empty string if canceled
		}
#pragma endregion

		bool SS3DMainTitleBar::SS3DMainTitleBar_DrawFileTab()
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New Project..."))
				{
					// TODO: Add new project stuff
				}

				if (ImGui::MenuItem("Open Project..."))
				{
					OpenFileDialogSSProj();
				}

				if (ImGui::MenuItem("Save Project..."))
				{
					// Pretend to save project
					// TODO: Actually save the project
				}

				if (ImGui::MenuItem("Save As..."))
				{
					SaveAsFileDialogSSProj();
				}

				ImGui::EndMenu();
			}

			ImGui::SameLine();
			return true;
		}

		bool SS3DMainTitleBar::SS3DMainTitleBar_DrawSettingsTab()
		{
			if (m_OpenSettingsDialog == true)
			{
				ImGui::OpenPopup("Engine & Editor Settings");
				m_OpenSettingsDialog = false;
			}

			if (ImGui::BeginPopupModal("Engine & Editor Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				if (ImGui::CollapsingHeader("Engine Settings"))
				{
					ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Note: This affects how the game or engine works.");
					if (ImGui::CollapsingHeader("Rendering/Graphics"))
					{
						if (ImGui::Checkbox("Enable VSync", &m_EnableVSync))
						{
							glfwSwapInterval(1);  // Enable VSync
						}

						static int s_I__SS3DMainTitleBar_Settings_ShadowQualityIndex = 0;
						const char* c_CPTR__SS3DMainTitleBar_Settings_ShadwoQualityOptions[] = {
							"None", "Low", "Medium", "High"
						};

						if (ImGui::BeginCombo("Shadow Quality", c_CPTR__SS3DMainTitleBar_Settings_ShadwoQualityOptions[s_I__SS3DMainTitleBar_Settings_ShadowQualityIndex]))
						{
							for (int n = 0; n < IM_ARRAYSIZE(c_CPTR__SS3DMainTitleBar_Settings_ShadwoQualityOptions); n++)
							{
								bool b_SS3DMainTitleBar_Settings_ShadowQuality_isShadowQualityTypeSelected = (s_I__SS3DMainTitleBar_Settings_ShadowQualityIndex == n);
								if (ImGui::Selectable(c_CPTR__SS3DMainTitleBar_Settings_ShadwoQualityOptions[n], b_SS3DMainTitleBar_Settings_ShadowQuality_isShadowQualityTypeSelected))
									s_I__SS3DMainTitleBar_Settings_ShadowQualityIndex = n;

								if (b_SS3DMainTitleBar_Settings_ShadowQuality_isShadowQualityTypeSelected == true)
									ImGui::SetItemDefaultFocus();
							}
							ImGui::EndCombo();
						}

						ImGui::Checkbox("Enable High Graphics Resolution", &m_EnableHighGraphicsResolution);
						// TODO: Add more
					}

					if (ImGui::CollapsingHeader("Physics/Simulation"))
					{
						ImGui::DragFloat("Phyics Update Rate", &m_PhyicsUpdateRate, 0.1f);
						ImGui::DragFloat("Gravity", &m_GravityValue, 0.1f);
					}
				}

				if (ImGui::CollapsingHeader("Editor Preferences"))
				{
					ImGui::Checkbox("Show Scene Hierarchy Panel", &m_ShowSceneHierarchyPanel);
				}
			}

			ImGui::SameLine();
			return true;
		}

		bool SS3DMainTitleBar::SS3DMainTitleBar_DrawSGSIDETab()
		{
			// TODO: Show the SGSIDE Window
			ImGui::SameLine();
			return true;
		}

		bool SS3DMainTitleBar::SS3DMainTitleBar_DrawSpritemakerTab()
		{
			// TODO: Show the SGSIDE window
			ImGui::SameLine();
			return true;
		}

		bool SS3DMainTitleBar::SS3DMainTitleBar_DrawImportTab()
		{
			if (m_OpenImportDialog == true)
			{
				ImGui::OpenPopup("Import");
				m_OpenImportDialog = false;
			}

			if (ImGui::BeginPopupModal("Import", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				// TODO: Show the import settings
			}

			ImGui::SameLine();
			return true;
		}

		bool SS3DMainTitleBar::SS3DMainTitleBar_DrawExportTab()
		{
			if (m_OpenExportDialog == true)
			{
				ImGui::OpenPopup("Export");
				m_OpenExportDialog = false;
			}

			if (ImGui::BeginPopupModal("Export", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				// TODO: Show the export settings
			}

			ImGui::SameLine();
			return true;
		}

		bool SS3DMainTitleBar::SS3DMainTitleBar_DrawMainTitleBar()
		{
			ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, 30));

			if (ImGui::Begin("Title Bar", nullptr, flags))
			{
				try { SS3DMainTitleBar_DrawFileTab(); }
				catch (const std::exception& e) { SS3D_ERROR(e.what()); }
				catch (...) { SS3D_ERROR("Unknown error in DrawFileTab"); }
				try { SS3DMainTitleBar_DrawSettingsTab(); }
				catch (const std::exception& e) { SS3D_ERROR(e.what()); }
				catch (...) { SS3D_ERROR("Unknown error in DrawSettingsTab"); }
				try { SS3DMainTitleBar_DrawSGSIDETab(); }
				catch (const std::exception& e) { SS3D_ERROR(e.what()); }
				catch (...) { SS3D_ERROR("Unknown error in DrawSGSIDETab"); }
				try { SS3DMainTitleBar_DrawSpritemakerTab(); }
				catch (const std::exception& e) { SS3D_ERROR(e.what()); }
				catch (...) { SS3D_ERROR("Unknown error in DrawSpritemakerTab"); }
				try { SS3DMainTitleBar_DrawImportTab(); }
				catch (const std::exception& e) { SS3D_ERROR(e.what()); }
				catch (...) { SS3D_ERROR("Unknown error in DrawImportTab"); }
				try { SS3DMainTitleBar_DrawExportTab(); }
				catch (const std::exception& e) { SS3D_ERROR(e.what()); }
				catch (...) { SS3D_ERROR("Unknown error in DrawExportTab"); }
			}
			ImGui::End();

			return true;
		}

	}
}
