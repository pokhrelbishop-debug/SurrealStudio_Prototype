#include "SceneManagerPanel.h"
#include "SS2DWorldCanvasPanel.h"

#include "../src/SurrealStudio2D/src/Core/SS2DEngineDefines.h"
#include "../src/SurrealStudio2D/src/Core/Scene/Scene.h"
#include "../src/SurrealStudio2D/src/Core/Scene/Subscene.h"
#include "../src/SurrealStudio2D/src/Core/Scene/World.h"

#define GLFW_INCLUDE_NONE

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <imgui.h>

namespace SurrealStudio {

    namespace SurrealStudio2D {

        bool SceneManagerPanel::DrawLightProperties(const char* lightingOptions[], int index)
        {
            try
            {
                if (!lightingOptions || index < 0 || index >= static_cast<int>(m_Lights.size()))
                    return false;

                Lighting2D* light = m_Lights[index].get();
                if (!light)
                    return false;

                ImGui::Text("%s Properties:", lightingOptions[index]);

                ImGui::DragFloat2("Position", &light->position[0], 0.1f);
                ImGui::DragFloat2("Direction", &light->direction[0], 0.1f);
                ImGui::DragFloat("Intensity", &light->intensity, 0.1f);
                ImGui::ColorEdit4("Color", &light->color[0]);
                ImGui::DragFloat("Radius", &light->radius, 1.0f);
                ImGui::DragFloat("Angle", &light->angle, 1.0f);
                ImGui::Checkbox("Casts Shadows", &light->castsShadows);

                ImGui::Separator();
                return true;
            }
            catch (const std::exception& e) {
                SS2DERROR(e.what());
                return false;
            }
            catch (...) {
                SS2DERROR("Some unknown exception occurred in DrawLightProperties!");
                return false;
            }
        }

        bool SceneManagerPanel::DrawCameraProperties(const char* cameraOptions[], int index)
        {
            try
            {
                if (!cameraOptions || index < 0 || index >= static_cast<int>(m_Cameras.size()))
                    return false;

                Camera2D* camera = m_Cameras[index].get();
                if (!camera)
                    return false;

                ImGui::Text("%s Properties", cameraOptions[index]);

                ImGui::DragFloat2("Camera Position ", &camera->position[0], 0.1f);
                ImGui::DragFloat("Camera Rotation/Direction ", &camera->rotation, 0.1f);
                ImGui::SliderFloat("Camera Zoom ", &camera->zoom, 1.0f, 10.0f);
                ImGui::DragFloat2("Viewport Size ", &camera->viewportSize[0], 0.1f);
                ImGui::DragFloat2("Target ", &camera->target[0], 0.1f);

                ImGui::Spacing();
                ImGui::Text("Orthographic Bounds");
                ImGui::DragFloat("Left: ", &camera->orthographicBoundsLeft, 0.1f);
                ImGui::DragFloat("Right: ", &camera->orthographicBoundsRight, 0.1f);
                ImGui::DragFloat("Top: ", &camera->orthographicBoundsTop, 0.1f);
                ImGui::DragFloat("Bottom: ", &camera->orthographicBoundsBottom, 0.1f);

                return true;
            }
            catch (const std::exception& e) {
                SS2DERROR(e.what());
                return false;
            }
            catch (...) {
                SS2DERROR("Some unknown exception occurred in DrawCameraProperties!");
                return false;
            }
        }

        bool SceneManagerPanel::DrawSceneCreation()
        {
            try
            {
                if (ImGui::Button("Create new Scene"))
                    m_Scenes.push_back(std::make_unique<Scene>());

                if (ImGui::Button("Create new Subscene"))
                    m_Subscenes.push_back(std::make_unique<Subscene>());

                if (ImGui::Button("Create new World"))
                    m_Worlds.push_back(std::make_unique<World>());

                return true;
            }
            catch (const std::exception& e) {
                SS2DERROR(e.what());
                return false;
            }
            catch (...) {
                SS2DERROR("Some unknown exception occurred in DrawSceneCreation!");
                return false;
            }
        }

        bool SceneManagerPanel::DrawLightingCreationAndProperties()
        {
            try
            {
                static int selectedLightIndex = 0;
                static constexpr unsigned int MAX_LIGHTS = 10;
                const char* lightingOptions[] = {
                    "WorldEnvironmentLight", "SurrealAmbientLight",
                    "SurrealPointLight", "SurrealSpotLight", "SurrealAreaLight",
                    "SurrealEmissiveLight"
                };
                static bool openMaxLightSelectedErrorDialogBox = true;

                if (ImGui::CollapsingHeader("Lighting"))
                {
                    if (ImGui::BeginCombo("Lighting Type", lightingOptions[selectedLightIndex]))
                    {
                        for (int n = 0; n < IM_ARRAYSIZE(lightingOptions); n++)
                        {
                            bool isLightSelected = (selectedLightIndex == n);
                            if (ImGui::Selectable(lightingOptions[n], isLightSelected))
                                selectedLightIndex = n;

                            if (isLightSelected)
                                ImGui::SetItemDefaultFocus();
                        }

                        ImGui::EndCombo();
                    }

                    if ((m_Lights.size() >= MAX_LIGHTS) && openMaxLightSelectedErrorDialogBox)
                    {
                        ImGui::OpenPopup("Surreal Studio (2D) Error");
                        openMaxLightSelectedErrorDialogBox = false;
                    }
                    else if (m_Lights.size() < MAX_LIGHTS)
                    {
                        if (selectedLightIndex >= static_cast<int>(m_Lights.size()))
                            m_Lights.push_back(std::make_unique<Lighting2D>());

                        DrawLightProperties(lightingOptions, selectedLightIndex);
                    }

                    if (ImGui::BeginPopupModal("Surreal Studio (2D) Error", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
                    {
                        ImGui::TextColored(ImVec4(1, 0, 0, 1), "Max amount of lights per world is %d", MAX_LIGHTS);
                        ImGui::Spacing();
                        if (ImGui::Button("OK"))
                        {
                            ImGui::CloseCurrentPopup();
                            m_Lights.resize(MAX_LIGHTS);
                            openMaxLightSelectedErrorDialogBox = true;
                        }
                        ImGui::EndPopup();
                    }

                }
                return true;
            }
            catch (const std::exception& e) {
                SS2DERROR(e.what());
                return false;
            }
            catch (...) {
                SS2DERROR("Some unknown exception occurred in DrawLightingCreationAndProperties!");
                return false;
            }
        }

        bool SceneManagerPanel::DrawCameraCreationAndProperties()
        {
            try
            {
                static int selectedCameraIndex = 0;
                static constexpr unsigned int MAX_CAMERAS = 3;
                const char* cameraOptions[] = {
                    "Normal", "Orthographic", "Target Camera"
                };
                static bool openMaxCamerasReachedErrorDialogBox = true;

                if (ImGui::CollapsingHeader("Camera"))
                {
                    if (ImGui::BeginCombo("Camera Type", cameraOptions[selectedCameraIndex]))
                    {
                        for (int n = 0; n < IM_ARRAYSIZE(cameraOptions); n++)
                        {
                            bool isCameraSelected = (selectedCameraIndex == n);
                            if (ImGui::Selectable(cameraOptions[n], isCameraSelected))
                                selectedCameraIndex = n;

                            if (isCameraSelected)
                                ImGui::SetItemDefaultFocus();
                        }
                        ImGui::EndCombo();
                    }

                    if ((m_Cameras.size() >= MAX_CAMERAS) && openMaxCamerasReachedErrorDialogBox == true)
                    {
                        ImGui::OpenPopup("Surreal Studio (2D) Error");
                        openMaxCamerasReachedErrorDialogBox = false;
                    }
                    else if (m_Cameras.size() < MAX_CAMERAS)
                    {
                        if (selectedCameraIndex >= static_cast<int>(m_Cameras.size()))
                            m_Cameras.push_back(std::make_unique<Camera2D>());

                        DrawCameraProperties(cameraOptions, selectedCameraIndex);
                    }

                    if (ImGui::BeginPopupModal("Surreal Studio (2D) Error", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
                    {
                        ImGui::TextColored(ImVec4(1, 0, 0, 1), "Max amount of cameras per world is %d", MAX_CAMERAS);
                        ImGui::Spacing();
                        if (ImGui::Button("OK"))
                        {
                            ImGui::CloseCurrentPopup();
                            selectedCameraIndex = MAX_CAMERAS - 1;
                            openMaxCamerasReachedErrorDialogBox = true;
                        }
                        ImGui::EndPopup();
                    }
                }
                return true;
            }
            catch (const std::exception& e) {
                SS2DERROR(e.what());
                return false;
            }
            catch (...) {
                SS2DERROR("Some unknown exception occurred in DrawCameraCreationAndProperties!");
                return false;
            }
        }

        bool SceneManagerPanel::DrawSceneManagerPanel()
        {
            try
            {
                ImGui::Begin("Scene Manager");

                try { DrawSceneCreation(); }
                catch (const std::exception& e) { SS2DERROR(e.what()); }
                catch (...) { SS2DERROR("Unknown exception in DrawSceneCreation!"); }

                try { DrawLightingCreationAndProperties(); }
                catch (const std::exception& e) { SS2DERROR(e.what()); }
                catch (...) { SS2DERROR("Unknown exception in DrawLightingCreationAndProperties!"); }

                try { DrawCameraCreationAndProperties(); }
                catch (const std::exception& e) { SS2DERROR(e.what()); }
                catch (...) { SS2DERROR("Unknown exception in DrawCameraCreationAndProperties!"); }

                if (ImGui::Button("Extra World Settings - World Canvas"))
                {
                    m_SS2DWorldCanvasPanel.DrawSS2DWorldCanvasPanel();
                }

                ImGui::End();
                return true;
            }
            catch (const std::exception& e) {
                SS2DERROR(e.what());
                return false;
            }
            catch (...) {
                SS2DERROR("Some unknown exception occurred in DrawSceneManagerPanel!");
                return false;
            }
        }
    }
}
