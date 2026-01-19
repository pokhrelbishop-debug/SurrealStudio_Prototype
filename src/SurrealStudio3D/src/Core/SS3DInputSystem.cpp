#include "SS3DInputSystem.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>

namespace SurrealStudio {

    namespace SurrealStudio3D {

        bool SS3DInputSystem::InitializeSystem() noexcept
        {
            callbacks.clear();

            if (!glfwInit())
            {
                std::cout << "[SS3DInputSystem] Failed to initialize GLFW.\n";
                return false;
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            return true;
        }

        bool SS3DInputSystem::RegisterCallback(
            InputSystemType inputType,
            InputCallback callback
        ) noexcept
        {
            callbacks[inputType].push_back(std::move(callback));
            return true;
        }

        bool SS3DInputSystem::UnregisterCallback(
            InputSystemType inputType,
            InputCallback callback
        ) noexcept
        {
            auto it = callbacks.find(inputType);
            if (it == callbacks.end())
                return false;

            auto& vec = it->second;

            vec.erase(
                std::remove_if(vec.begin(), vec.end(),
                    [&](const InputCallback& cb)
                    {
                        // std::function has no operator==,
                        // so we compare target addresses
                        return cb.target_type() == callback.target_type();
                    }),
                vec.end()
            );

            return true;
        }

        bool SS3DInputSystem::DetectInputEvents() noexcept
        {
            // GLFW input polling
            glfwPollEvents();
            return true;
        }

        bool SS3DInputSystem::ProcessInputEvents() noexcept
        {
            

            return true;
        }

        bool SS3DInputSystem::ClearAllCallbacks() noexcept
        {
            callbacks.clear();
            return true;
        }

    } // namespace SurrealStudio3D
} // namespace SurrealStudio
