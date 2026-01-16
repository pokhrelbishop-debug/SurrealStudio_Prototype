#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>

/* Main .h file for the UHRSRP feature (Ultra High Realistic Surreal Render Pipelien) */
namespace SurrealStudio {

	namespace SurrealRenderer {

		class UHRSRP2D
		{
		public:

			bool UHRSRP2DCreateWindow(int UHRSRPWindowWidth, int UHRSRPWindowHeight, const char* UHRSRPWindowTitle);
			bool UHRSRP2DInitiailze();
			bool UHSRP2DRenderFrame();
			bool UHRSRP2DShutdown();

		private:

			GLFWwindow* m_UHRSRP2DBaseWindow_SurrealRendererUHRSRPWINDOW = nullptr;
		};
	}
}