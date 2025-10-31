#include "hierarchyObj.h"

void HierachyObj::setGlobal(glm::mat4 local, glm::vec3 pos, glm::quat rotation, glm::vec3 scale)
{
	local = glm::mat4(1.0f);
	local = glm::translate(local, pos);
	local *= glm::mat4_cast(rotation);
	local = glm::scale(local, scale);
}

void HierachyObj::setLocalBasedOnGlobal()
{
	HierachyObj* cur;
	std::stack<HierachyObj*> transformStack;
	
	tranformLocal = parent->tranformGlobalInv * tranformGlobal;
}

void HierachyObj::setHierarchyBasedOnLocal()
{
	HierachyObj* cur;
	for (cur = this; cur->parent != nullptr; cur = cur->parent);

	std::stack<HierachyObj*> transformStack;
	transformStack.push(cur);
	while (!transformStack.empty())
	{
		cur = transformStack.top();
		transformStack.pop();

		for (HierachyObj* child : cur->children)
		{
			transformStack.push(child);
		}

		cur->tranformGlobal = cur->parent->tranformGlobal * cur->tranformLocal;
	}
}
