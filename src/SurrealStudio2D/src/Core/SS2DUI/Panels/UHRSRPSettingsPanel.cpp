#include "UHRSRPSettingsPanel.h"

#include "../src/SurrealStudio2D/src/Core/SS2DEngineDefines.h"

#include <stdexcept>
#include <memory>
#include <imgui.h>

namespace SurrealStudio {

	namespace SurrealStudio2D {

		bool UHRSRPSettingsPanel::DrawUHRSRPLightCreation()
		{
			try
			{
				static constexpr SSPositiveInteger MAX_UHRSRP_CUSTOM_UHRSRP_LIGHTS = 25;
				static SSInteger iselectedUHRSRPCustomLightIndex = 0;
				SSConstantCharPtr UHRSRPCustomLightOptions[] = {
					"UHRSRPSurrealPointLight", "UHRSRPSurrealSpotLight", "UHRSRPSurrealAreaLight",
					"UHRSRPSurrealEmissiveLight"
				};
				static SSBoolean bOpenMax_UHRSRP_CustomLightsReached_SS2DERROR_DialogBox = true;

				ImGui::Text("UHRSRP Lights");
				if (ImGui::BeginCombo("UHRSRP Lighting Options", UHRSRPCustomLightOptions[iselectedUHRSRPCustomLightIndex]))
				{
					for (int n = 0; n < IM_ARRAYSIZE(UHRSRPCustomLightOptions); n++)
					{
						SSBoolean bIsUHRSRPCustomLightsSelected = (iselectedUHRSRPCustomLightIndex == n);
						if (ImGui::Selectable(UHRSRPCustomLightOptions[n], bIsUHRSRPCustomLightsSelected))
							iselectedUHRSRPCustomLightIndex = n;

						if (bIsUHRSRPCustomLightsSelected == true)	
							ImGui::SetItemDefaultFocus();
					}

					if (m_UHRSRPCustomLights.size() > MAX_UHRSRP_CUSTOM_UHRSRP_LIGHTS && bOpenMax_UHRSRP_CustomLightsReached_SS2DERROR_DialogBox == true)
					{
						ImGui::OpenPopup("Surreal Studio (2D) Error - [UHRSRP-ERROR] Max Custom Lights reached");
						bOpenMax_UHRSRP_CustomLightsReached_SS2DERROR_DialogBox = false;
					}

					if (ImGui::BeginPopupModal("Surreal Studio (2D) Error - [UHRSRP-ERROR] Max Custom Lights reached", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text("[UHRSRP-ERROR] Max amount of Custom Lights per world is %d got %d", MAX_UHRSRP_CUSTOM_UHRSRP_LIGHTS, static_cast<int>(m_UHRSRPCustomLights.size()));
						m_UHRSRPCustomLights.resize(MAX_UHRSRP_CUSTOM_UHRSRP_LIGHTS); // Clamp to max value
						bOpenMax_UHRSRP_CustomLightsReached_SS2DERROR_DialogBox = true; // Reset
					}

					ImGui::EndCombo();
				}

				SSConstant<SSBoolean> c_B_IsUHRSRPCustomLightsUnderMaxLimit = m_UHRSRPCustomLights.size() < MAX_UHRSRP_CUSTOM_UHRSRP_LIGHTS;
				SSConstant<SSBoolean> c_B_IsUHRSRPselectedIndexUnderMaxLimit = iselectedUHRSRPCustomLightIndex < MAX_UHRSRP_CUSTOM_UHRSRP_LIGHTS;
				if (c_B_IsUHRSRPCustomLightsUnderMaxLimit && c_B_IsUHRSRPselectedIndexUnderMaxLimit && !bOpenMax_UHRSRP_CustomLightsReached_SS2DERROR_DialogBox == true)
				{
					m_UHRSRPCustomLights.push_back(std::make_unique<UHRSRPCustomLights>());
					SS2DINFO("UHRSRP Light Custom added successfully!");
					DrawUHRSRPLightProperties(UHRSRPCustomLightOptions, iselectedUHRSRPCustomLightIndex);
				}

				return true;
			}
			catch (const std::exception& e) {
				SS2DERROR(e.what());
				return false;
			}
			catch (...) {
				SS2DERROR("Some unknown exception occurred!");
				return false;
			}
		}

		bool UHRSRPSettingsPanel::DrawUHRSRPLightProperties(SSConstantCharPtr UHRSRPlightingOptions[], SSInteger index)
		{
			try
			{
				if (!UHRSRPlightingOptions || index < 0 || index >= static_cast<SSInteger>(m_UHRSRPCustomLights.size()))
					return false;

				SSPtr<UHRSRPCustomLights> UHRSRPcustomLights = m_UHRSRPCustomLights[index].get();
				if (!UHRSRPcustomLights)
					return false;

				// TODO: Fill this
				ImGui::Text("UHRSRP Properties");
				ImGui::Text("%s UHRSRP Properties", UHRSRPlightingOptions[index]);


				return true;
			}
			catch (const std::exception& e) {
				SS2DERROR(e.what()); 
				return false;
			}
			catch (...) {
				SS2DERROR("Some unknown exception occurred!");
				return false;
			}
		}

		bool UHRSRPSettingsPanel::DrawUHRSRP_SurrealIlluminationLightCreation()
		{
			try
			{
				static constexpr SSPositiveInteger UHRSRP_MAX_SURREALILLUMINATION = 1; // Limit to only having 1 SI per world
				static SSBoolean s_B_openUHRSRP_MaxSurrealIllumination_Object__GICreated__SS2DERROR_ErrorDialogBox = true;  // Flag for if user clicks on Create Surreal Illuminatio button and it has already been created

				if (m_UHRSRPSurrealIllumination_GI.size() > UHRSRP_MAX_SURREALILLUMINATION && s_B_openUHRSRP_MaxSurrealIllumination_Object__GICreated__SS2DERROR_ErrorDialogBox == true)
				{
					ImGui::OpenPopup("Surreal Studio (2D) Error - [UHRSRP] Max Surreal Illumination Object Created");
					s_B_openUHRSRP_MaxSurrealIllumination_Object__GICreated__SS2DERROR_ErrorDialogBox = false;
				}

				try {
					if (m_UHRSRPSurrealIllumination_GI.size() < UHRSRP_MAX_SURREALILLUMINATION && !s_B_openUHRSRP_MaxSurrealIllumination_Object__GICreated__SS2DERROR_ErrorDialogBox == true)
					{
						m_UHRSRPSurrealIllumination_GI.push_back(std::make_unique<UHRSRPSurrealIllumination>());
					}
				}
				catch (const std::exception& e) {
					SS2DERROR(e.what());
					return false;
				}
				catch (...) {
					SS2DERROR("[ERROR] [FROM UHRSRP] FAILED TO CREATE SURREAL ILLUMINATION OBJECT DUE TO UNKNOWN EXCEPTION.");
					return false;
				}

				if (ImGui::BeginPopupModal("Surreal Studio (2D) Error - [UHRSRP] Max Surreal Illumination Object Created", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text("[UHRSRP] A Surreal Illumination Object has already been created. You cannot create another one.");
					if (ImGui::Button("OK")) {
						ImGui::CloseCurrentPopup();
						m_UHRSRPSurrealIllumination_GI.resize(UHRSRP_MAX_SURREALILLUMINATION); // Clamp 
						s_B_openUHRSRP_MaxSurrealIllumination_Object__GICreated__SS2DERROR_ErrorDialogBox = true;  // reset so if it happens again, this can be trigged again
					}
				}
				
				ImGui::Text("UHRSRP - Surreal Illumination (Global Illumination)");
				return true;
			}
			catch (const std::exception& e) {
				SS2DERROR(e.what());
				return false;
			}
			catch (...) {
				SS2DERROR("Some unknown exception occurred!");
				return false;
			}
		}

		bool UHRSRPSettingsPanel::DrawUHRSRPSettingsPanel()
		{
			try
			{
				try { DrawUHRSRPLightCreation(); }
				catch (const std::exception& e) {
					SS2DERROR(e.what()); return false;
				}
				catch (...) { SS2DERROR("Some unknown exception occurred!"); return false; }

				try { DrawUHRSRP_SurrealIlluminationLightCreation(); }
				catch (const std::exception& e) {
					SS2DERROR(e.what()); return false;
				}
				catch (...) { SS2DERROR("Some unknown exception occurred!"); return false; }

				return true;
			}
			catch (const std::exception& e) {
				SS2DERROR(e.what());
				return false;
			}
			catch (...) {
				SS2DERROR("Some unknown exception occurred!");
				return false;
			}
		}
	}
}