#include "Renderer.h"
#include "../src/SurrealStudio3D/src/Core/Scene/World3D.h"

#include <iostream>

#define GLFW_INCLUDE_NONE

namespace SurrealStudio {

	namespace SurrealRenderer {

		//void Renderer::RenderAll(SurrealStudio3D::SceneSystem3D::World& world)
		//{
		//	auto objects = world.GetObjects();

		//	for (auto* obj : objects)
		//	{
		//		if (!obj) continue;

		//		auto& objectPosition = obj->objectTransformComponent.position;
		//		auto& objectRotation = obj->objectTransformComponent.rotation;
		//		auto& objectScale = obj->objectTransformComponent.scale;

		//		std::cout <<
		//			"Rendered object at position (" << objectPosition.x << ", " << objectPosition.y << ", " << objectPosition.z
		//			<< "), " << "Rotation (" << objectRotation.x << ", " << objectRotation.y << ", " << objectRotation.z << "), "
		//			<< "Scale (" << objectScale.x << ", " << objectScale.y << ", " << objectScale.z << ").\n" << std::endl;

		//		// TODO: Later replace this with GPU draw calls
 	//		}

		// Temporary fix for some errors, testing...
	}
}