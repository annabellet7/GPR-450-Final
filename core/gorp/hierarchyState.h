#pragma once

#include "hierarchy.h"
#include "transform.h"
#include <vector>

typedef std::vector<Transform> FramePose;
typedef std::vector<FramePose> BoneList;
typedef std::vector<BoneList> ClipPoses;
//How to access
//local[ClipIndex][BoneIndex][Frame]

class HierarchyState
{
public:
	gorp::Hierarchy* mHierarchy;
	ClipPoses local; //node relative to parent
	ClipPoses invLocal; //parent relative to node
	ClipPoses global; //node relative to root parent
	ClipPoses invGlobal; //root parent relative to node
};