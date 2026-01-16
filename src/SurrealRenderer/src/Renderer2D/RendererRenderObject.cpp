#include "RendererRenderObject.h"

#define GLFW_INCLUDE_NONE

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

namespace SurrealStudio {

	namespace SurrealRenderer {

        RendererRenderObject::RendererRenderObject()
        {
            InitTriangleResources();
        }

        RendererRenderObject::~RendererRenderObject()
        {
            if (m_VBO) glDeleteBuffers(1, &m_VBO);
            if (m_VAO) glDeleteVertexArrays(1, &m_VAO);
            if (m_shaderProgram) glDeleteProgram(m_shaderProgram);
        }

        void RendererRenderObject::InitTriangleResources()
        {
            // --- Vertex Array & Buffer ---
            glGenVertexArrays(1, &m_VAO);
            glGenBuffers(1, &m_VBO);

            glBindVertexArray(m_VAO);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), nullptr, GL_DYNAMIC_DRAW); // dynamic buffer

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            // --- Shader sources ---
            const char* vertexShaderSource = R"(
                #version 330 core
                layout(location = 0) in vec2 aPos;
                uniform vec4 uColor;
                out vec4 vertexColor;
                void main() {
                    gl_Position = vec4(aPos, 0.0, 1.0);
                    vertexColor = uColor;
                }
            )";

             const char* fragmentShaderSource = R"(
                #version 330 core
                in vec4 vertexColor;
                out vec4 FragColor;
                void main() {
                    FragColor = vertexColor;
                }
            )";

            GLuint vertexShader = CompileShader(vertexShaderSource, GL_VERTEX_SHADER);
            GLuint fragmentShader = CompileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

            // --- Link shader program ---
            m_shaderProgram = glCreateProgram();
            glAttachShader(m_shaderProgram, vertexShader);
            glAttachShader(m_shaderProgram, fragmentShader);
            glLinkProgram(m_shaderProgram);
            
            GLint success;
            glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
            if (!success) {
                char infoLog[512];
                glGetProgramInfoLog(m_shaderProgram, 512, nullptr, infoLog);
                std::cerr << "[Renderer] Shader linkage failed:\n" << infoLog << std::endl;
            }

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            glBindVertexArray(0);
        }

        GLuint RendererRenderObject::CompileShader(const char* source, GLenum type)
        {
            GLuint shader = glCreateShader(type);
            glShaderSource(shader, 1, &source, nullptr);
            glCompileShader(shader);

            GLint success;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                char infoLog[512];
                glGetShaderInfoLog(shader, 512, nullptr, infoLog);
                std::cerr << "[Renderer] Shader compilation failed:\n" << infoLog << std::endl;
            }

            return shader;
        }

        bool RendererRenderObject::DrawTriangle(glm::vec2 vertices[3], const glm::vec4& color)
        {
            glBindVertexArray(m_VAO);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, 6 * sizeof(float), vertices); // upload vertex data

            glUseProgram(m_shaderProgram);

            GLint colorLoc = glGetUniformLocation(m_shaderProgram, "uColor");
            glUniform4f(colorLoc, color.r, color.g, color.b, color.a);

            glDrawArrays(GL_TRIANGLES, 0, 3);

            glBindVertexArray(0);
            return true;
        }

	}
}
