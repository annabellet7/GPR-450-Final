#include "hierarchyNode.h"

namespace gorp
{
	HierarchyNode::HierarchyNode()
	{
		name = "";
		parent = nullptr;
		children[0] = nullptr;
		m.transformLocal = glm::mat4(0);
		m.transformGlobal = glm::mat4(0);
		m.transformLocalInv = glm::mat4(0);
		m.transformGlobalInv = glm::mat4(0);
	}

	HierarchyNode::HierarchyNode(std::string nodeName, HierarchyNode* nodeParent, std::vector<HierarchyNode*> nodeChildren, Transform nodeTransform)
	{
		name = nodeName;
		parent = nodeParent;
		for (int i = 0; i < sizeof(nodeChildren); i++)
		{
			children[i] = nodeChildren[i];
		}
		m = nodeTransform;
	}

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