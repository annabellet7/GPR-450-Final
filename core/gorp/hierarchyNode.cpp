#include "hierarchyNode.h"

namespace gorp
{
	void HierarchyNode::setHierarchyPosBasedOnLocal()
	{
		HierarchyNode* cur;
		for (cur = this; cur->parent != nullptr; cur = cur->parent);

		std::stack<HierarchyNode*> transformStack;
		transformStack.push(cur);

		while (!transformStack.empty())
		{
			cur = transformStack.top();
			transformStack.pop();

			for (HierarchyNode* child : cur->children)
			{
				transformStack.push(child);
			}

			cur->m.transformGlobal = cur->parent->m.transformGlobal * cur->m.transformLocal;
		}
	}

	HierarchyNode* HierarchyNode::GetNode(std::string nodeName)
	{
		HierarchyNode* cur;

		for (cur = this; cur->parent != nullptr; cur = cur->parent);

		std::stack<HierarchyNode*> transformStack;
		transformStack.push(cur);

		while (!transformStack.empty())
		{
			cur = transformStack.top();
			transformStack.pop();

			for (HierarchyNode* child : cur->children)
			{
				transformStack.push(child);
			}

			if (cur->name == nodeName)
				return cur;
		}

		return nullptr;
	}
}