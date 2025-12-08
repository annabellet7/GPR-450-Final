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
	void poseLerp(int keyframeIndex0, int keyframeIndex1, int numNodes, float t);
	void updateLocalInverse(HierarchyList* list);
	void updateGlobalInverse(HierarchyList* list);
};