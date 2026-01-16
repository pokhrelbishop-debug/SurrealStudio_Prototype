#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace SurrealStudio {

    class SSSurrealStudioMainWindow
    {
    public:
        bool Initialize();      // FIXED typo here
        void MainLoop();        // Make this void since you don't return a bool in loop
        void DestroySSApp();

    private:
        GLFWwindow* m_Window = nullptr; // THIS IS FINE
    };
}
