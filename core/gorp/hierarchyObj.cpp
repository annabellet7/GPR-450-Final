#include "hierarchyObj.h"

void HierarchyObj::setGlobal(glm::mat4 local, glm::vec3 pos, glm::quat rotation, glm::vec3 scale)
{
	local = glm::mat4(1.0f);
	local = glm::translate(local, pos);
	local *= glm::mat4_cast(rotation);
	local = glm::scale(local, scale);
}

void HierarchyObj::setLocalInverse()
{
	transformLocalInv = glm::inverse(transformLocal);
}

void HierarchyObj::setGlobalInverse()
{
	transformGlobalInv = glm::inverse(transformGlobal);
}

void HierarchyObj::setLocalBasedOnGlobal()
{
	HierarchyObj* cur;
	std::stack<HierarchyObj*> transformStack;
	
	transformLocal = parent->transformGlobalInv * transformGlobal;
}

void HierarchyObj::setHierarchyBasedOnLocal()
{
	HierarchyObj* cur;
	for (cur = this; cur->parent != nullptr; cur = cur->parent);

	std::stack<HierarchyObj*> transformStack;
	transformStack.push(cur);
	while (!transformStack.empty())
	{
		cur = transformStack.top();
		transformStack.pop();

		for (HierarchyObj* child : cur->children)
		{
			transformStack.push(child);
		}

		cur->transformGlobal = cur->parent->transformGlobal * cur->transformLocal;
	}
}
