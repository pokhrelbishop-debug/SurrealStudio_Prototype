#include "SS3DMainEngineWindow.h"
#include "../src/SurrealStudio3D/src/SS3DEngineDefines.h"

#define GLFW_INCLUDE_NONE

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>

namespace SurrealStudio {

	namespace SurrealStudio3D {

		bool SS3DMainEngineWindow::SS3DMainEngineWindow_Init()
		{
			if (!glfwInit())
			{
				SS3D_ERROR("Failed to initialize GLFW.\n");
				glfwTerminate();
				return false;
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			
			return true;
		}

		bool SS3DMainEngineWindow::SS3DMainEngineWindow_CreateSS3DEngineWindow(int width, int height, const char* engineWindowTitle)
		{
			m_SS3DMaineEngineWindow_WINDOW = glfwCreateWindow(width, height, engineWindowTitle, nullptr, nullptr);
			if (!m_SS3DMaineEngineWindow_WINDOW)
			{
				SS3D_ERROR("Failed to create GLFW window.\n");
				glfwTerminate();
				return false;
			}

			glfwMakeContextCurrent(m_SS3DMaineEngineWindow_WINDOW);
			glfwSwapInterval(1); // Enable VSync

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				SS3D_ERROR("Failed to intiailize GLAD.\n");
				glfwTerminate();
				return false;
			}

			// ---------------------------------Setup Dear ImGui context--------------------------------------------------- //
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;

			// Setup ImGui style
			ImGui::StyleColorsDark();

			// Setup ImGui renderer/windowing backends 
			ImGui_ImplGlfw_InitForOpenGL(m_SS3DMaineEngineWindow_WINDOW, true);
			ImGui_ImplOpenGL3_Init("#version 330");

			return true;
		}

		bool SS3DMainEngineWindow::SS3DMainEngineWindow_EngineWindowMainLoop()
		{
			while (!glfwWindowShouldClose(m_SS3DMaineEngineWindow_WINDOW))
			{
				glfwPollEvents();
				
				// Start ImGui new frame
				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();

				// -------------------------------- Surreal Studio 3D; Surreal Editor Window Creation ------------------------------------------------- //
				ImGui::Begin("Surreal Studio 3D");
				bool b_DoesMainSceneExist = false;
				if (!b_DoesMainSceneExist)
				{
					ImGui::Text("No main scene currently created.");
				}

				if (ImGui::Button("Create new Scene"))
				{
					b_DoesMainSceneExist = true;
					ImGui::Text("Main scene created!");
				}

				ImGui::End();

				// Rendering
				ImGui::Render();
				int display_w, display_h;
				glfwGetFramebufferSize(m_SS3DMaineEngineWindow_WINDOW, &display_w, &display_h);
				glViewport(0, 0, display_w, display_h);
				glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glEnable(GL_DEPTH_TEST);
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

				glfwSwapBuffers(m_SS3DMaineEngineWindow_WINDOW);
			}

			return true;
		}

		bool SS3DMainEngineWindow::SS3DMainEngineWindow_DestroyEngineWindow()
		{
			if (!m_SS3DMaineEngineWindow_WINDOW) return false;

			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
			glfwDestroyWindow(m_SS3DMaineEngineWindow_WINDOW);
			glfwTerminate();

			return true;
		}
	}
}