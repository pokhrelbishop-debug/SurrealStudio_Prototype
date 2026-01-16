#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

namespace SurrealStudio {

	namespace SGSIDE {

		class SGSIDEMainWindow
		{
		public:

			bool SGSIDEInitializeIDEApplication();
			bool SGSIDERunIDEApplication();
			bool SGSIDEShutdownIDEApplication();

		private:

			GLFWwindow* m_SGSIDEMainApplication_Window__SGSIDE = nullptr;
		};
	}
}