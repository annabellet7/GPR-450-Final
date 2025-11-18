#include "hierarchyNode.h"

namespace gorp
{
	void HierarchyNode::setGlobal(glm::mat4 local, glm::vec3 pos, glm::quat rotation, glm::vec3 scale)
	{
		local = glm::mat4(1.0f);
		local = glm::translate(local, pos);
		local *= glm::mat4_cast(rotation);
		local = glm::scale(local, scale);
	}

	void HierarchyNode::setLocalInverse()
	{
		transformLocalInv = glm::inverse(transformLocal);
	}

	void HierarchyNode::setGlobalInverse()
	{
		transformGlobalInv = glm::inverse(transformGlobal);
	}

	void HierarchyNode::setLocalBasedOnGlobal()
	{
		transformLocal = parent->transformGlobalInv * transformGlobal;
	}

	void HierarchyNode::setHierarchyBasedOnLocal()
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

			cur->transformGlobal = cur->parent->transformGlobal * cur->transformLocal;
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