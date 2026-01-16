#include "Scene.h"
#include "Subscene.h" // Needed for unique_ptr<Subscene>
#include <algorithm>
#include <iostream>

namespace SurrealStudio {

    namespace SurrealStudio2D {

        Scene::Scene() = default;

        Scene::~Scene() = default;

        void Scene::AddSubscene(Subscene* subscene)
        {
            m_Subscenes.push_back(std::unique_ptr<Subscene>(subscene));
        }

        void Scene::RemoveSubscene(Subscene* subscene)
        {
            auto it = std::remove_if(
                m_Subscenes.begin(),
                m_Subscenes.end(),
                [subscene](const std::unique_ptr<Subscene>& ptr) { return ptr.get() == subscene; }
            );

            if (it != m_Subscenes.end())
                m_Subscenes.erase(it, m_Subscenes.end());
            else
                std::cerr << "Subscene " << subscene << " could not be found." << std::endl;
        }

        void Scene::UpdateScene()
        {
            for (auto& sub : m_Subscenes)
                sub->Update();
        }

        void Scene::RenderScene()
        {
            for (auto& sub : m_Subscenes)
                sub->Render();
        }

        Subscene* Scene::AccessSubscene(int index) const
        {
            if (index >= 0 && index < static_cast<int>(m_Subscenes.size()))
                return m_Subscenes[index].get();

            std::cerr << "Failed to access subscene at index " << index << std::endl;
            return nullptr;
        }

        std::vector<Subscene*> Scene::GetAllSubscenes() const
        {
            std::vector<Subscene*> rawPointers;
            for (const auto& sub : m_Subscenes)
                rawPointers.push_back(sub.get());

            return rawPointers;
        }
    }
}
