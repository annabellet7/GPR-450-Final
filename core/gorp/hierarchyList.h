#pragma once

#include "hierarchy.h"
#include "transform.h"

class HierarchyList
{
public:
	Hierarchy* hierarchy; //how each node relates to each other
	NodeTransformsList* nodePoseList; //contains the transforms for each node for each keyframe

	HierarchyList();
	~HierarchyList();
};