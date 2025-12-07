#pragma once

#include "hierarchyNode.h"
#include <string>

namespace gorp
{
	class Hierarchy
	{
	public:
		std::vector<HierarchyNode> nodeList;
		//int mSize;

		//Hierarchy(Hierarchy* hierarchy, int size);
		int getNode(std::string name);
		void addNode(HierarchyNode node);
		/*addNode(Hierarchy* hierarchy, )*/
	};
}