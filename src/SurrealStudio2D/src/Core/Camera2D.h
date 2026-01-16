#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace SurrealStudio {

    namespace SurrealStudio2D {

        class Camera2D
        {
        public:
            enum class CameraType { None = 0, Normal, Orthographic };

            // Position
            bool SetPosition(float x, float y);
            glm::vec2 GetPosition() const;

            // Rotation
            bool SetRotation(float degrees);
            float GetRotation() const;

            // Zoom
            bool SetZoom(float nweZoom);
            float GetZoom() const;

            // Movement / rotation / zoom
            bool Move(float dx, float dy);
            bool Rotate(float dDegrees);
            bool Zoom(float dZoom);

            // Velocity
            bool SetVelocity(float vx, float vy);
            glm::vec2 GetVelocity() const;

            bool SetRotationSpeed(float degreesPerSecond);
            float GetRotationSpeed() const;

            bool SetZoomSpeed(float zoomPerSecond);
            float GetZoomSpeed() const;

            // Matrices
            glm::mat4 GetViewMatrix() const;
            glm::mat4 GetProjectionMatrix() const;

            // Orthographic bounds
            bool SetOrthographicBounds(float left, float right, float top, float bottom);

            // Optional boundaries
            bool SetMinBounds(float x, float y);
            bool SetMaxBounds(float x, float y);
            bool ClampToBounds();

            // Camera type
            bool SetCameraType(CameraType type);
            CameraType GetCameraType() const;

            // Update (deltaTime in seconds)
            bool Update(float deltaTime);

            CameraType cameraType{ CameraType::Normal };

        private:
            glm::vec2 position{ 0.0f, 0.0f };
            float rotation{ 0.0f };
            float zoom{ 1.0f };

            glm::vec2 velocity{ 0.0f, 0.0f };
            float rotationSpeed{ 0.0f };
            float zoomSpeed{ 0.0f };

            glm::vec2 minBounds{ -1000.0f, -1000.0f };
            glm::vec2 maxBounds{ 1000.0f, 1000.0f };

            float orthoLeft{ 0.0f }, orthoRight{ 0.0f }, orthoTop{ 0.0f }, orthoBottom{ 0.0f };
        };

    } // namespace SurrealStudio2D
} // namespace SurrealStudio
