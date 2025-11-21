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

		HierarchyNode();
		HierarchyNode(std::string nodeName, HierarchyNode* nodeParent, std::vector <HierarchyNode*> nodeChildren, Transform nodeTransform);
		void setHierarchyPosBasedOnLocal();
		HierarchyNode* GetNode(std::string nodeName);
	};
}
