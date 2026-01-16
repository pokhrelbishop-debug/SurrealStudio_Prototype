#pragma once

#include <string>
#include <memory>
#include <vector>

namespace SurrealStudio {

	namespace SurrealStudio3D {

		namespace SceneSystem3D {

			class Subscene;

			struct SceneData
			{
				std::string sceneName;
				std::vector<std::unique_ptr<Subscene>> subscenes;
			};

			class Scene
			{
			public:

				Scene() noexcept;
				~Scene() = default;

				bool AddScene() noexcept;
				bool DeleteScene(SceneData* data) noexcept;

			private:

				SceneData sceneData;
				std::vector<std::unique_ptr<SceneData>> m_Scene;  // NOTE: THERE WILL BE ONLY ONE SCENE IN A PROJECT
			};
		}
	}
}