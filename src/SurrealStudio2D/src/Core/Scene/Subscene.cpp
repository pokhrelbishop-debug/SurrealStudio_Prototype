
#include "Subscene.h"
#include "World.h" // For WorldData
#include <iostream>
#include <algorithm>

namespace SurrealStudio {
    namespace SurrealStudio2D {
        Subscene::Subscene()
            : m_NumberOfSubscenes(0),
            m_Loaded(false),
            m_IsVisible(false)
        {
        }

        void Subscene::Load()
        {
            if (m_Loaded)
                return;

            WorldData* defaultWorld = new WorldData();
            defaultWorld->worldName = "World1";
            defaultWorld->worldID = 0;

            std::cout << "[Subscene] Created default world: " << defaultWorld->worldName << "\n";

            m_Loaded = true;
            m_NumberOfSubscenes++;

            delete defaultWorld;
        }

        void Subscene::Unload()
        {
            if (!m_Loaded)
                return;

            std::cout << "[Subscene] Unloading all world data and components.\n";
            m_SubsceneData.clear();

            m_Loaded = false;
            m_NumberOfSubscenes = 0;
        }

        void Subscene::Update()
        {
            if (!m_Loaded)
                return;

            std::cout << "[Subscene] Updating active subscene...\n";
            for (auto& subData : m_SubsceneData)
                std::cout << " - Updating subscene: " << subData.subsceneName << std::endl;
        }

        void Subscene::Render()
        {
            if (!m_Loaded)
                return;

            std::cout << "[Subscene] Rendering visible worlds and objects...\n";
            for (auto& subData : m_SubsceneData)
                std::cout << " - Rendering subscene: " << subData.subsceneName << std::endl;
        }

        bool Subscene::SetVisible(bool visible)
        {
            m_IsVisible = visible;
            std::cout << "[Subscene] Visibility set to: " << (m_IsVisible ? "true" : "false") << std::endl;
            return m_IsVisible;
        }

        bool Subscene::IsLoaded() const
        {
            return m_Loaded;
        }

        bool Subscene::IsVisible() const
        {
            return m_IsVisible;
        }
    }
}
