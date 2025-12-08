#include "hierarchyList.h"

HierarchyList::HierarchyList()
{
	hierarchy = new Hierarchy;
	nodePoseList = new NodeTransformsList;
}

HierarchyList::~HierarchyList()
{
	delete hierarchy;
	delete nodePoseList;
}
