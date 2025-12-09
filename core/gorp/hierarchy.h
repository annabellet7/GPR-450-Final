#pragma once

#include "hierarchyNode.h"
#include <string>

//data structure for holding the relationship between the nodes
class Hierarchy
{
public:
	std::vector<HierarchyNode> nodeList;

	int getNode(std::string name);
	void addNode(HierarchyNode node);
};
