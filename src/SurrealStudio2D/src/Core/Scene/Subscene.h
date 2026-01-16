#pragma once

#include "Scene.h"
#include <string>
#include <vector>

namespace SurrealStudio {

    namespace SurrealStudio2D {

        struct SubsceneData
        {
            std::string subsceneName;
            int subsceneID;
        };

        class Subscene : public Scene
        {
        public:
            Subscene();
            virtual ~Subscene() = default;

            void Load();
            void Unload();
            void Update();
            void Render();

            bool IsLoaded() const;
            bool SetVisible(bool visible);
            bool IsVisible() const;

        private:
            std::vector<SubsceneData> m_SubsceneData;
            int m_NumberOfSubscenes;
            bool m_Loaded;
            bool m_IsVisible;
        };
    }
}
