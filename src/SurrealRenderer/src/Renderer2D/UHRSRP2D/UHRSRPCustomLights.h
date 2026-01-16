#pragma once

#include "UHRSRP2D.h"

#include <memory>

namespace SurrealStudio {

	namespace SurrealRenderer {

		class UHRSRPCustomLights
		{
		public:

			bool UHSRPCreateCustomLights();
			bool UHRSRPDeleteCustomLights();

		private:

			std::unique_ptr<UHRSRP2D> m_UHRSRP2D_Class_UHRSRPBaseClass;
		};
	}
}