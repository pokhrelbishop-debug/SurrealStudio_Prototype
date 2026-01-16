#include "Scene3D.h"
#include "Subscene3D.h"

#include <string>
#include <memory>
#include <vector>

namespace SurrealStudio {

	namespace SurrealStudio3D {

		namespace SceneSystem3D {

			Scene::Scene() noexcept = default;

			bool Scene::AddScene() noexcept
			{
				if (!m_Scene.empty()) // Only one scene
					return false;

				auto newScene = std::make_unique<SceneData>();
				newScene->sceneName = "Main Scene";

				m_Scene.push_back(std::move(newScene));
				return true;
			}

			bool Scene::DeleteScene(SceneData* data) noexcept
			{
				if (m_Scene.empty())
					return false;

				m_Scene.clear();

				return true;
			}
		}
	}
}