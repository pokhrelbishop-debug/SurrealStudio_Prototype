#include "SS3DInputSystem.h"

#include <string>
#include <unordered_map>
#include <functional>
#include <vector>
#include <stdexcept>
#include <iostream>

#include <GLFW/glfw3.h>

#define GLFW_INCLUDE_NONE

namespace SurrealStudio {

	namespace SurrealStudio3D {

		bool SS3DInputSystem::InitializeSystem() noexcept
		{
			try
			{
				callbacks.clear();
				
				// GLFW init
				if (!glfwInit())
				{
					std::cout << "Failed to initalize GLFW.\n";
					glfwTerminate();
					return false;
				}

				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

				return true;  // Init success
			}
			catch (const std::exception& e) {
				std::cout << "Caught error " << e.what() << " at line "
					<< __LINE__ << " in file " << __FILE__ << ".\n" << std::endl;
				return false;
			}
			catch (...) { std::cout << "Unknown exception, in line " << __LINE__ << " in file " << __FILE__ << ".\n" << std::endl; return false; }
		}

		bool SS3DInputSystem::RegisterCallback(InputSystemType inputType, InputCallback callback, std::vector<InputSystemType> typevec) noexcept
		{
			try
			{
				if (callbacks.size() > 1) return false;

				if (callbacks.contains(inputType))
				{
					callbacks.emplace(callback);
				}
				else
				{
					callbacks.emplace(typevec);
				}

				return true;
			}
			catch (const std::exception& e) {
				std::cout << "Caught error " << e.what() << " at line "
					<< __LINE__ << " in file " << __FILE__ << ".\n" << std::endl;

				return false;
			}
			catch (...) { std::cout << "Unknown exception, in line " << __LINE__ << " in file " << __FILE__ << ".\n" << std::endl; return false; }
		}

		bool SS3DInputSystem::UnregisterCallback(InputSystemType inputType, InputCallback callback, std::vector<InputSystemType> typevec) noexcept
		{
			try
			{
				if (callbacks.contains(inputType))
				{
					for (auto it = callbacks.begin(); it != callbacks.end(); it++)\
					{
						// FINISH THIS
					}
				}

				return true;
			}
			catch (const std::exception& e) {
				std::cout << "Caught error " << e.what() << " at line "
					<< __LINE__ << " in file " << __FILE__ << ".\n" << std::endl;

				return false;
			}
			catch (...) { std::cout << "Unknown exception, in line " << __LINE__ << " in file " << __FILE__ << ".\n" << std::endl; return false; }
		}

		bool SS3DInputSystem::DetectInputEvents() noexcept
		{
			try
			{
				return true;
			}
			catch (const std::exception& e) {
				std::cout << "Caught error " << e.what() << " at line "
					<< __LINE__ << " in file " << __FILE__ << ".\n" << std::endl;

				return false;
			}
			catch (...) { std::cout << "Unknown exception, in line " << __LINE__ << " in file " << __FILE__ << ".\n" << std::endl; return false; }
		}

		bool SS3DInputSystem::ProcessInputEvents() noexcept
		{
			try
			{
				return true;
			}
			catch (const std::exception& e) {
				std::cout << "Caught error " << e.what() << " at line "
					<< __LINE__ << " in file " << __FILE__ << ".\n" << std::endl;

				return false;
			}
			catch (...) { std::cout << "Unknown exception, in line " << __LINE__ << " in file " << __FILE__ << ".\n" << std::endl; return false; }
		}

		bool SS3DInputSystem::ClearAllCallbacks() noexcept
		{
			try
			{
				return true;
			}
			catch (const std::exception& e) {
				std::cout << "Caught error " << e.what() << " at line "
					<< __LINE__ << " in file " << __FILE__ << ".\n" << std::endl;

				return false;
			}
			catch (...) { std::cout << "Unknown exception, in line " << __LINE__ << " in file " << __FILE__ << ".\n" << std::endl; return false; }
		}
	}
}