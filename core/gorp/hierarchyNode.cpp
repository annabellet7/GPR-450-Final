#include "hierarchyNode.h"

HierarchyNode::HierarchyNode()
{
	name = "";
	parentIndex = -1;
	selfIndex = -1;
}

void HierarchyNode::setNode(std::string n, int parent, int self)
{
	name = n;
	parentIndex = parent;
	selfIndex;
}

int HierarchyNode::GetNode()
{
	return selfIndex;
}
