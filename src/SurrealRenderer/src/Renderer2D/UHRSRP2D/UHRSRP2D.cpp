#include "UHRSRP2D.h"

#define GLFW_INCLUDE_NONE

#include <stdexcept>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

// Helper macro for logging exceptions
#define UHRSRP_LOG_ERROR(e) \
    std::cerr << "[ERROR] [FROM UHRSRP, FUNCTION " << __FUNCTION__ << ", FILE " << __FILE__ << ", LINE " << __LINE__ << "] -> " << e << std::endl;

#define UHRSRP_LOG_UNKNOWN_ERROR() \
    std::cerr << "[ERROR] [FROM UHRSRP, FUNCTION " << __FUNCTION__ << ", FILE " << __FILE__ << ", LINE " << __LINE__ << "] -> Some unknown exception occurred!" << std::endl;

namespace SurrealStudio {

    namespace SurrealRenderer {

        bool UHRSRP2D::UHRSRP2DCreateWindow(int UHRSRPWindowWidth, int UHRSRPWindowHeight, const char* UHRSRPWindowTitle)
        {
            try
            {
                // First initialize UHRSRP2D
                if (!UHRSRP2DInitiailze())
                    return false;

                // Check if the window pointer is still nullptr after initialization
                if (m_UHRSRP2DBaseWindow_SurrealRendererUHRSRPWINDOW == nullptr)
                {
                    std::cerr << "[ERROR] [FROM UHRSRP, FUNCTION " << __FUNCTION__
                        << ", FILE " << __FILE__
                        << ", LINE " << __LINE__
                        << "] -> m_UHRSRP2DBaseWindow_SurrealRendererUHRSRPWINDOW is nullptr!"
                        << std::endl;
                    return false;
                }

                // Create the actual window
                m_UHRSRP2DBaseWindow_SurrealRendererUHRSRPWINDOW =
                    glfwCreateWindow(UHRSRPWindowWidth, UHRSRPWindowHeight, UHRSRPWindowTitle, nullptr, nullptr);
                glfwMakeContextCurrent(m_UHRSRP2DBaseWindow_SurrealRendererUHRSRPWINDOW);

                return true;
            }
            catch (const std::exception& e)
            {
                UHRSRP_LOG_ERROR(e.what());
                return false;
            }
            catch (...)
            {
                UHRSRP_LOG_UNKNOWN_ERROR();
                return false;
            }

        }

        bool UHRSRP2D::UHRSRP2DInitiailze()
        {
            try
            {
                if (!glfwInit())
                {
                    std::cerr << "Failed to initialize GLFW.\n";
                    glfwTerminate();
                    return false;
                }

                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

                // GLAD needs a valid OpenGL window, so create a very small one
                UHRSRP2DCreateWindow(0, 0, "");

                if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
                {
                    std::cerr << "Failed to initialize GLAD.\n";
                    glfwTerminate();
                    return false;
                }

                return true;
            }
            catch (const std::exception& e) { UHRSRP_LOG_ERROR(e.what()); return false; }
            catch (...) { UHRSRP_LOG_UNKNOWN_ERROR(); return false; }
        }

        bool UHRSRP2D::UHSRP2DRenderFrame()
        {
            try
            {
                std::cout << "UHRSRP started rendering frame!" << std::endl;
                return true;
            }
            catch (const std::exception& e) { UHRSRP_LOG_ERROR(e.what()); return false; }
            catch (...) { UHRSRP_LOG_UNKNOWN_ERROR(); return false; }
        }

        bool UHRSRP2D::UHRSRP2DShutdown()
        {
            try
            {
                std::cout << "UHRSRP termination!" << std::endl;
                glfwTerminate();
                return true;
            }
            catch (const std::exception& e) { UHRSRP_LOG_ERROR(e.what()); return false; }
            catch (...) { UHRSRP_LOG_UNKNOWN_ERROR(); return false; }
        }

    } // namespace SurrealRenderer

} // namespace SurrealStudio
