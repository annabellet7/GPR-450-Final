#pragma once

#include "hierarchyNode.h"
#include <string>

	class Hierarchy
	{
	public:
		std::vector<HierarchyNode> nodeList;
	
		int getNode(std::string name);
		int getNode(int index);
		void addNode(HierarchyNode node);

		Hierarchy();
	};
