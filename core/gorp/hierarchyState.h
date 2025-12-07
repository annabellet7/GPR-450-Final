#pragma once

#include "hierarchy.h"
#include "transform.h"
#include "anims.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

class HierarchyState
{
public:
	Hierarchy* mHierarchy;
	std::vector<Anim> animList; //node relative to parent
	
	HierarchyState(Hierarchy* hierarchy);
	void updateLocalInverse(HierarchyState* state);
	void updateWorldInverse(HierarchyState* state);
};