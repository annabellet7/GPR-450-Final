#pragma once

#include "hierarchyNode.h"
#include <string>

	class Hierarchy
	{
	public:
		std::vector<HierarchyNode> nodeList;
		//int mSize;

		//Hierarchy(Hierarchy* hierarchy, int size);
		int getNode(std::string name);
		int getNode(int index);
		void addNode(HierarchyNode node);
		/*addNode(Hierarchy* hierarchy, )*/
	};
