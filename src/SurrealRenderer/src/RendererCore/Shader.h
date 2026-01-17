#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <string>

namespace SurrealStudio {
	
	namespace SurrealRenderer {

		struct VertexShader
		{
			std::string vertexShaderSource;
		};

		struct FragmentShader
		{
			std::string fragmentShaderSource;
		};

		class Shader
		{
		public:

			// Upload and linking shaders to the GPU via two different methods
			GLuint CompileAndLinkShaderViaGLSLShaderFiles(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) noexcept;
			GLuint CompileAndLinkShaderViaShaderVariables(const VertexShader& vertexShader, const FragmentShader& fragmentShader) noexcept;
		};
	}
}