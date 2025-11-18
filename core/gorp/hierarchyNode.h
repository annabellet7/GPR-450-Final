#pragma once

#include <string>
#include <vector>
#include <stack>
#include "Transform.h"

namespace gorp
{
	class HierarchyNode
	{
	public:
		std::string name;
		HierarchyNode* parent;
		std::vector <HierarchyNode*> children;
		Transform m;

		void setGlobal(glm::mat4 local, glm::vec3 pos, glm::quat rotation, glm::vec3 scale);
		void setLocalInverse();
		void setGlobalInverse();
		void setLocalBasedOnGlobal();
		void setHierarchyBasedOnLocal();
		HierarchyNode* GetNode(std::string nodeName);
	};
}
