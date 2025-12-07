#pragma once

#include "hierarchy.h"
#include "transform.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

class HierarchyState
{
public:
	Hierarchy* mHierarchy;
	std::vector<Transform> local; //node relative to parent
	std::vector<Transform> invLocal; //parent relative to node
	std::vector<Transform> global; //node relative to root parent
	std::vector<Transform> invGlobal; //root parent relative to node

	HierarchyState(Hierarchy* hierarchy);
	void updateLocalInverse(HierarchyState* state);
	void updateWorldInverse(HierarchyState* state);
};