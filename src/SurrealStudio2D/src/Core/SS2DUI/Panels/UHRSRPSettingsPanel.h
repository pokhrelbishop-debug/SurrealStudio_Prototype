#pragma once

#include "../src/SurrealStudio2D/src/Core/SS2DEngineDefines.h"

#include <memory>
#include <vector>

namespace SurrealStudio {

	namespace SurrealStudio2D {

		struct UHRSRPCustomLights
		{
			int iUHRSRPCustomLightsID;

			enum class UHRSRPCustomLightsType
			{
				None = 0,
				UHRSRPSurrealPointLight,
				UHRSRPSurrealSpotLight,
				UHRSRPSurrealAreaLight,
				UHRSRPSurrealEmissiveLight
			};

			UHRSRPCustomLightsType UHRSRPcustomLightsType;
		};

		struct UHRSRPSurrealIllumination
		{
			SSInteger iUHSRPSurrealIlluminationGI_ID;

			enum class UHRSRPSurrealIlluminationGI_TYPE {UHRSRPSurrealIlluminationNone = 0, UHRSRPSurrealIllumination_};

			UHRSRPSurrealIlluminationGI_TYPE UHRSRPSurrealIllumination_GI_type_;
		};

		// UHRSRP = Ultra High Realistic Surreal Render Pipeline
		class UHRSRPSettingsPanel
		{
		public:

			// ---Lighting [UHRSRP] ---
			bool DrawUHRSRPLightCreation();
			bool DrawUHRSRPLightProperties(SSConstantCharPtr UHRSRPlightingOptions[], SSInteger index);
			bool DrawUHRSRP_SurrealIlluminationLightCreation();

			bool DrawUHRSRPSettingsPanel();

		private:

			std::vector<std::unique_ptr<UHRSRPCustomLights>> m_UHRSRPCustomLights;
			std::vector<std::unique_ptr<UHRSRPSurrealIllumination>> m_UHRSRPSurrealIllumination_GI;

			UHRSRPSurrealIllumination::UHRSRPSurrealIlluminationGI_TYPE m_UHSRPSurrealIllumination_GI_TYPE;
			UHRSRPCustomLights::UHRSRPCustomLightsType m_UHRSRPCustomLights_UHRSRPCustomLightsType;
		};
	}
}