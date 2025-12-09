#include "hierarchy.h"

//get node given node name
int Hierarchy::getNode(std::string name)
{
	for (int i = 0; i < nodeList.size(); i++)
	{
		if (nodeList[i].name == name) return nodeList[i].selfIndex;
	}

	return -1;
}

void Hierarchy::addNode(HierarchyNode node)
{
	nodeList.push_back(node);
}
