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

		void setHierarchyPosBasedOnLocal();
		HierarchyNode* GetNode(std::string nodeName);
	};
}
