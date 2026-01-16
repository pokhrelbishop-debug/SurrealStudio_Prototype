#pragma once

#define GLFW_INCLUDE_NONE

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace SurrealStudio {

	namespace SurrealRenderer {

        class RendererRenderObject
        {
        public:
            RendererRenderObject();
            ~RendererRenderObject();

            bool DrawTriangle(glm::vec2 vertices[3], const glm::vec4& color);

        private:
            GLuint m_shaderProgram = 0;   // Compiled shader program
            GLuint m_VAO = 0;
            GLuint m_VBO = 0;

            void InitTriangleResources();
            GLuint CompileShader(const char* source, GLenum type);
        };
	}
}