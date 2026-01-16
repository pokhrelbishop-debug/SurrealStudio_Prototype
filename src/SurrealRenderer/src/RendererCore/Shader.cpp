#include "Shader.h"

#define GLFW_INCLUDE_NONE

#include <string>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

namespace SurrealStudio {

	namespace SurrealRenderer {

		GLuint Shader::CompileAndLinkShaderViaGLSLShaderFiles(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) noexcept
		{
			GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

			const char* vertexShaderSrc = vertexShaderSource.c_str();
			glShaderSource(vertexShaderID, 1, &vertexShaderSrc, nullptr);

			const char* fragmentShaderSrc = fragmentShaderSource.c_str();
			glShaderSource(fragmentShaderID, 1, &fragmentShaderSrc, nullptr);

			glCompileShader(vertexShaderID);
			glCompileShader(fragmentShaderID);

			GLint success = 0;
			glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				char infoLog[512];
				glGetProgramInfoLog(vertexShaderID, 512, nullptr, infoLog);
				std::cout << "[SURREAL RENDERER] Shader linkage failed!\n" << infoLog << std::endl;
				glDeleteShader(vertexShaderID);
				glDeleteShader(fragmentShaderID);
				return 0;
			}

			glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				char infoLog[512];
				glGetProgramInfoLog(fragmentShaderID, 512, nullptr, infoLog);
				std::cout << "[SURREAL RENDERER] Shader linkage failed!\n" << infoLog << std::endl;
				glDeleteShader(vertexShaderID);
				glDeleteShader(fragmentShaderID);
				return 0;
			}

			GLuint programID = glCreateProgram();
			glAttachShader(programID, vertexShaderID);
			glAttachShader(programID, fragmentShaderID);
			glLinkProgram(programID);

			glGetProgramiv(programID, GL_LINK_STATUS, &success);
			
			if (!success)
			{
				char infoLog[512];
				glGetProgramInfoLog(programID, 512, nullptr, infoLog);
				std::cout << "[SURREAL RENDERER] Shader linkage failed!\n" << infoLog << std::endl;
				glDeleteShader(vertexShaderID);
				glDeleteShader(fragmentShaderID);
				glDeleteProgram(programID);
				return 0;
			}

			if (!success)
			{
				char infoLog[512];
				glGetProgramInfoLog(fragmentShaderID, 512, nullptr, infoLog);
				std::cout << "[SURREAL RENDERER] Shader linkage failed!\n" << infoLog << std::endl;
				glDeleteShader(vertexShaderID);
				glDeleteShader(fragmentShaderID);
				return 0;
			}
			
			glDetachShader(programID, vertexShaderID);
			glDetachShader(programID, fragmentShaderID);

			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);

			return programID;
		}

		GLuint Shader::CompileAndLinkShaderViaShaderVariables(const VertexShader& vertexShader, const FragmentShader& fragmentShader) noexcept
		{
			if (vertexShader.vertexShaderSource.empty())
			{
				std::cout << "[SURREAL RENDERER] Vertex Shader source is empty!" << "\n"; 
				return 0;
			}

			if (fragmentShader.fragmentShaderSource.empty())
			{
				std::cout << "[SURREAL RENDERER] Fragment Shader source is empty!" << "\n"; 
				return 0;
			}

			return CompileAndLinkShaderViaGLSLShaderFiles(vertexShader.vertexShaderSource, fragmentShader.fragmentShaderSource);
		}
	}
}