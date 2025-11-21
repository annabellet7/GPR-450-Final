#pragma once

#include "hierarchyNode.h"

namespace gorp
{
	class Hierarchy
	{
	public:
		HierarchyNode* mNode;
		int mSize;

		Hierarchy(Hierarchy* hierarchy, int size);
		/*addNode(Hierarchy* hierarchy, )*/
	};
}