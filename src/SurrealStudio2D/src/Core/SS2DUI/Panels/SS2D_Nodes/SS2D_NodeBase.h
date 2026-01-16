#pragma once

#include <string>

namespace SurrealStudio {

	namespace SurrealStudio2D {

		class SS2D_NodeBase
		{
		public:

			SS2D_NodeBase(const std::string& name) : nodeName(name) {}
			virtual ~SS2D_NodeBase() = default;

			virtual void NodeEvaluate(float deltaTime) = 0;
			virtual void DrawUI() = 0;

			std::string nodeName;
		};
	}
}

