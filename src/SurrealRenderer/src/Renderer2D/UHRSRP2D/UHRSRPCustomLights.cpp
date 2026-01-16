#include "UHRSRPCustomLights.h"
#include "UHRSRP2D.h"

#include <stdexcept>
#include <iostream>
#include <memory>

namespace SurrealStudio {

	namespace SurrealRenderer {

        bool UHRSRPCustomLights::UHSRPCreateCustomLights()
        {
            try
            {
                m_UHRSRP2D_Class_UHRSRPBaseClass = std::make_unique<UHRSRP2D>();

                m_UHRSRP2D_Class_UHRSRPBaseClass->UHRSRP2DInitiailze();

                return true;
            }
            catch (const std::exception& e)
            {
                std::cerr << "[ERROR] [FROM UHRSRP, FUNCTION UHSRPCreateCustomLights, IN FILE UHRSRPCustomLights.cpp] (ERROR REASON) -> "
                    << e.what() << std::endl;
                return false;
            }
            catch (...)
            {
                std::cerr << "[ERROR] [FROM UHRSRP, FUNCTION UHSRPCreateCustomLights, IN FILE UHRSRPCustomLights.cpp] (ERROR REASON) -> Some unknown exception occurred."
                    << std::endl;
                return false;
            }
        }

        bool UHRSRPCustomLights::UHRSRPDeleteCustomLights()
        {
            try
            {
                return true;
            }
            catch (const std::exception& e)
            {
                std::cerr << "[ERROR] [FROM UHRSRP, FUNCTION UHRSRPDeleteCustomLights, IN FILE UHRSRPCustomLights.cpp] (ERROR REASON) -> "
                    << e.what() << std::endl;
                return false;
            }
            catch (...)
            {
                std::cerr << "[ERROR] [FROM UHRSRP, FUNCTION UHRSRPDeleteCustomLights, IN FILE UHRSRPCustomLights.cpp] (ERROR REASON) -> Some unknown exception occurred."
                    << std::endl;
                return false;
            }
        }
	}
}