#pragma once

#include "../src/SurrealStudio2D/src/Core/SS2D_Nodes/SS2D_NodeBase.h"

#include <imgui.h>

#include <string>

namespace SurrealStudio {

	namespace SurrealStudio2D {

		class AnimationNodesBase : public SS2D_NodeBase
		{
		public:

			AnimationNodesBase(const std::string& name) : SS2D_NodeBase(name) {}
			virtual ~AnimationNodesBase() = default;

			int targetObjectID = -1;

			void NodeEvaluate(float deltaTime) override
			{
				
			}
		};
	}
}