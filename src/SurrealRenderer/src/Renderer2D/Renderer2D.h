#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

namespace SurrealStudio {

	namespace SurrealRenderer {

		class Renderer2D
		{
		public:

			bool Renderer2DInit();
			bool Renderer2DCreateWindow(int width, int height, const char* windowTitle);
			bool Renderer2DShutdown();

		private:

			GLFWwindow* m_SurrealRendererWindow = nullptr;
		};
	}
}