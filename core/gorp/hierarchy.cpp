#include "hierarchy.h"

namespace gorp
{
	//Hierarchy::Hierarchy(Hierarchy* hierarchy, int size)
	//{
	//	mSize = size;
	//	//hierarchy->mNode = (HierarchyNode*)malloc(size * sizeof(HierarchyNode));
	//}

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


}