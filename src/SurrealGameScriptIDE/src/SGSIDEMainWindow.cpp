#include "SGSIDEMainWindow.h"

#define GLFW_INCLUDE_NONE

#include <iostream>
#include <stdexcept>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace SurrealStudio {

    namespace SGSIDE {

        // ==========================
        // Helper logging functions
        // ==========================
        inline void LogSGSIDEError(const std::exception& e, const char* function, const char* file, int line)
        {
            std::cerr << "[ERROR] [FROM SGSIDE] IN FUNCTION " << function
                << " IN FILE " << file
                << " AT LINE " << line
                << " -> " << e.what() << "\n";
        }

        inline void LogSGSIDEUnknownError(const char* function, const char* file, int line)
        {
            std::cerr << "[ERROR] [FROM SGSIDE] Unknown exception in function "
                << function << " in file " << file << " at line " << line << "\n";
        }

        // ==========================
        // SGSIDEMainWindow methods
        // ==========================
        bool SGSIDEMainWindow::SGSIDEInitializeIDEApplication()
        {
            try 
            {
                if (!glfwInit())
                {
                    std::cerr << "Failed to intiailze GLFW.\n";
                    glfwTerminate();
                    return false;
                }

                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

                m_SGSIDEMainApplication_Window__SGSIDE = glfwCreateWindow(800, 600, "Surreal Game Script Integrated Development Environment", nullptr, nullptr);
                glfwMakeContextCurrent(m_SGSIDEMainApplication_Window__SGSIDE);

                if (!m_SGSIDEMainApplication_Window__SGSIDE)
                {
                    std::cerr << "[ERROR] FAILED TO CREATE GLFW WINDOW, FUNCTION RETURNING FALSE.\n";
                    glfwTerminate();
                    return false;
                }

                if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
                {
                    std::cerr << "Failed to intialize GLAD.\n";
                    glfwTerminate();
                    return false;
                }

                IMGUI_CHECKVERSION();
                
                ImGui::CreateContext();
                ImGuiIO& io = ImGui::GetIO(); (void)io;

                ImGui::StyleColorsDark();

                ImGui_ImplGlfw_InitForOpenGL(m_SGSIDEMainApplication_Window__SGSIDE, true);
                ImGui_ImplOpenGL3_Init("#version 330");

                return true;
            }
            catch (const std::exception& e) {
                LogSGSIDEError(e, __FUNCTION__, __FILE__, __LINE__);
                return false;
            }
            catch (...) {
                LogSGSIDEUnknownError(__FUNCTION__, __FILE__, __LINE__);
                return false;
            }
        }

        bool SGSIDEMainWindow::SGSIDERunIDEApplication()
        {
            try
            {
                while (!glfwWindowShouldClose(m_SGSIDEMainApplication_Window__SGSIDE))
                {
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    glfwPollEvents();

                    // Start Dear ImGui new frame
                    ImGui_ImplOpenGL3_NewFrame();
                    ImGui_ImplGlfw_NewFrame();

                    ImGui::Begin("Surreal Game Script Integrated Development Environment");
                    ImGui::Text("No file currently selected. Please open the SGSIDE Script Explorer Panel and create a new file.");
                    ImGui::End();

                    ImGui::Render();
                    
                    int iSGSIDE_display_w, iSGSIDE_display_h;
                    glfwGetFramebufferSize(m_SGSIDEMainApplication_Window__SGSIDE, &iSGSIDE_display_w, &iSGSIDE_display_h);
                    glViewport(0, 0, iSGSIDE_display_w, iSGSIDE_display_h);
                    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
                    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

                    glfwSwapBuffers(m_SGSIDEMainApplication_Window__SGSIDE);
                }
                return true;
            }
            catch (const std::exception& e) {
                LogSGSIDEError(e, __FUNCTION__, __FILE__, __LINE__);
                return false;
            }
            catch (...) {
                LogSGSIDEUnknownError(__FUNCTION__, __FILE__, __LINE__);
                return false;
            }
        }

        bool SGSIDEMainWindow::SGSIDEShutdownIDEApplication()
        {
            try
            {
                ImGui_ImplOpenGL3_Shutdown();
                ImGui_ImplGlfw_Shutdown();
                ImGui::DestroyContext();

                if (m_SGSIDEMainApplication_Window__SGSIDE)
                {
                    glfwDestroyWindow(m_SGSIDEMainApplication_Window__SGSIDE);
                }

                glfwTerminate();

                return true;
            }
            catch (const std::exception& e) {
                LogSGSIDEError(e, __FUNCTION__, __FILE__, __LINE__);
                return false;
            }
            catch (...) {
                LogSGSIDEUnknownError(__FUNCTION__, __FILE__, __LINE__);
                return false;
            }
        }

    } // namespace SGSIDE
} // namespace SurrealStudio
