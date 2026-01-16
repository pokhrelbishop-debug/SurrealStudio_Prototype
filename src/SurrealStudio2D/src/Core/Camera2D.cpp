#include "Camera2D.h"

#include <glm/glm.hpp>

namespace SurrealStudio {

    namespace SurrealStudio2D {

        bool Camera2D::SetPosition(float x, float y)
        {
            position.x = x;
            position.y = y;
            return true;
        }

        glm::vec2 Camera2D::GetPosition() const
        {
            return position;
        }

        bool Camera2D::SetRotation(float degrees)
        {
            rotation = degrees;
            return true;
        }

        float Camera2D::GetRotation() const
        {
            return rotation;
        }

        bool Camera2D::SetZoom(float newZoom)
        {
            zoom = newZoom;
            return true;
        }

        float Camera2D::GetZoom() const
        {
            return zoom;
        }

        bool Camera2D::Move(float dx, float dy)
        {
            position.x += dx;
            position.y += dy;
            return true;
        }

        bool Camera2D::Rotate(float dDegrees)
        {
            rotation += dDegrees;
            return true;
        }

        bool Camera2D::Zoom(float dZoom)
        {
            zoom += dZoom;
            return true;
        }

        bool Camera2D::SetVelocity(float vx, float vy)
        {
            velocity.x = vx;
            velocity.y = vy;
            return true;
        }

        glm::vec2 Camera2D::GetVelocity() const
        {
            return velocity;
        }

        bool Camera2D::SetRotationSpeed(float degreesPerSecond)
        {
            rotationSpeed = degreesPerSecond;
            return true;
        }

        float Camera2D::GetRotationSpeed() const
        {
            return rotationSpeed;
        }

        bool Camera2D::SetZoomSpeed(float zoomPerSecond)
        {
            zoomSpeed = zoomPerSecond;
            return true;
        }

        float Camera2D::GetZoomSpeed() const
        {
            return zoomSpeed;
        }

        glm::mat4 Camera2D::GetViewMatrix() const
        {
            glm::mat4 view = glm::mat4(1.0f); // identity
            view = glm::translate(view, glm::vec3(-position, 0.0f));
            view = glm::rotate(view, glm::radians(-rotation), glm::vec3(0.0f, 0.0f, 1.0f));
            view = glm::scale(view, glm::vec3(zoom, zoom, 1.0f));
            return view;
        }

        glm::mat4 Camera2D::GetProjectionMatrix() const
        {
            if (cameraType == CameraType::Orthographic)
                return glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, -1.0f, 1.0f);
            else
                return glm::mat4(1.0f);
        }

        bool Camera2D::SetOrthographicBounds(float left, float right, float top, float bottom)
        {
            orthoLeft = left;
            orthoRight = right;
            orthoTop = top;
            orthoBottom = bottom;
            return true;
        }

        bool Camera2D::SetMinBounds(float x, float y)
        {
            minBounds.x = x;
            minBounds.y = y;
            return true;
        }

        bool Camera2D::SetMaxBounds(float x, float y)
        {
            maxBounds.x = x;
            maxBounds.y = y;
            return true;
        }

        bool Camera2D::ClampToBounds()
        {
            if (position.x < minBounds.x) position.x = minBounds.x;
            if (position.x > maxBounds.x) position.x = maxBounds.x;
            if (position.y < minBounds.y) position.y = minBounds.y;
            if (position.y > maxBounds.y) position.y = maxBounds.y;
            return true;
        }

        bool Camera2D::SetCameraType(CameraType type)
        {
            cameraType = type;
            return true;
        }

        Camera2D::CameraType Camera2D::GetCameraType() const
        {
            return cameraType;
        }

        bool Camera2D::Update(float deltaTime)
        {
            position += velocity * deltaTime;
            rotation += rotationSpeed * deltaTime;
            zoom += zoomSpeed * deltaTime;
            ClampToBounds();
            return true;
        }

    } // namespace SurrealStudio2D
} // namespace SurrealStudio
