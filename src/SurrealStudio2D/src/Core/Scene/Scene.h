#pragma once

#include <vector>
#include <memory>

namespace SurrealStudio {

    namespace SurrealStudio2D {

        class Subscene; // Forward declaration

        class Scene
        {
        public:
            Scene();
            virtual ~Scene();

            void AddSubscene(Subscene* subscene);
            void RemoveSubscene(Subscene* subscene);
            void UpdateScene();
            void RenderScene();

            // Access
            Subscene* AccessSubscene(int index) const;
            std::vector<Subscene*> GetAllSubscenes() const;

        private:
            std::vector<std::unique_ptr<Subscene>> m_Subscenes;
        };
    }
}