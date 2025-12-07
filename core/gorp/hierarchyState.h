#pragma once

#include "hierarchy.h"
#include "transform.h"
#include <vector>

class HierarchyState
{
public:
	gorp::Hierarchy* mHierarchy;
	std::vector<Transform> local; //node relative to parent
	std::vector<Transform> invLocal; //parent relative to node
	std::vector<Transform> global; //node relative to root parent
	std::vector<Transform> invGlobal; //root parent relative to node
};