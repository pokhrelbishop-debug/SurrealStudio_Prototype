#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

namespace SurrealStudio {

	namespace SurrealStudio3D {

		class SS3DMainEngineWindow
		{
		public:

			bool SS3DMainEngineWindow_Init();  // Handles GLFW intialization, and setup (glfwWindowHint)
			bool SS3DMainEngineWindow_CreateSS3DEngineWindow(int width, int height, const char* engineWindowTitle);
			bool SS3DMainEngineWindow_EngineWindowMainLoop();
			bool SS3DMainEngineWindow_DestroyEngineWindow();

		private:

			GLFWwindow* m_SS3DMaineEngineWindow_WINDOW = nullptr;
		};
	}
}
