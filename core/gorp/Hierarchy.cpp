#include "Hierarchy.h"

namespace gorp
{
	Hierarchy::Hierarchy(Hierarchy* hierarchy, int size)
	{
		mSize = size;
		hierarchy->mNode = (HierarchyNode*)malloc(size * sizeof(HierarchyNode));
	}


}

