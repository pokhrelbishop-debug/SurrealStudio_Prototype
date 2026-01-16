#include "Renderer2D.h"

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

namespace SurrealStudio {

	namespace SurrealRenderer {

		bool Renderer2D::Renderer2DInit()
		{
			if (!glfwInit())
			{
				std::cerr << "Failed to intialize GLFW.\n";
				glfwTerminate();
				return false;
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			return true;
		}

		bool Renderer2D::Renderer2DCreateWindow(int width, int height, const char* windowTitle)
		{
			m_SurrealRendererWindow = glfwCreateWindow(width, height, windowTitle, nullptr, nullptr);
			if (!m_SurrealRendererWindow)
			{
				std::cerr << "Failed to create GLFW window.\n";
				glfwTerminate();
				return false;
			}

			glfwMakeContextCurrent(m_SurrealRendererWindow);

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cerr << "Failed to intialize GLAD.\n";
				glfwTerminate();
				return false;
			}

			while (!glfwWindowShouldClose(m_SurrealRendererWindow))
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glfwSwapBuffers(m_SurrealRendererWindow);
				glfwPollEvents();
			}

			return true;
		}

		bool Renderer2D::Renderer2DShutdown()
		{
			if (!m_SurrealRendererWindow) return false;

			glfwDestroyWindow(m_SurrealRendererWindow);
			glfwTerminate();
			return true;
		}
	}
};
