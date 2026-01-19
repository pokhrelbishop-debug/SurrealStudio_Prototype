#pragma once

#include <unordered_map>
#include <functional>
#include <vector>

namespace SurrealStudio {

    namespace SurrealStudio3D {

        class SS3DInputSystem
        {
        public:
            SS3DInputSystem() noexcept = default;
            ~SS3DInputSystem() noexcept = default;

            enum class InputSystemType
            {
                None = 0,
                OnClick,
                OnMouseScroll,
                OnKeyboardKeyPressed,
                OnKeyboardKeyReleased,
                OnWindowClosed,
                OnWindowMinimized,
                OnWindowMaximized,
                OnOtherInputDone
            };

            struct InputEvent
            {
                InputSystemType inputSystemType;
                int keyCode = -1;
                int mouseButton = -1;
                float scrollDelta = 0.0f;
            };

            using InputCallback = std::function<void(const InputEvent&)>;

            bool InitializeSystem() noexcept;
            bool RegisterCallback(InputSystemType inputType, InputCallback callback) noexcept;
            bool UnregisterCallback(InputSystemType inputType, InputCallback callback) noexcept;
            bool DetectInputEvents() noexcept;
            bool ProcessInputEvents() noexcept;
            bool ClearAllCallbacks() noexcept;

        private:
            std::unordered_map<InputSystemType, std::vector<InputCallback>> callbacks;
        };

    } // SurrealStudio3D
} // SurrealStudio
