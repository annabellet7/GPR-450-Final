#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "hierarchyNode.h"

class Transform
{
public:
	glm::vec4 translate;
	glm::vec4 rotate;
	glm::vec4 scale;
	glm::mat4 transformMat;
};

class NodeTransforms
{
public:
	int nodeIndex;
	int keyframeIndex;
	Transform local; //node relative to parent
	Transform invLocal; //parent relative to node
	Transform global; //node relative to root parent
	Transform invGlobal; //root parent relative to node

	NodeTransforms();
};

class NodeTransformsList
{
public:
	std::vector<NodeTransforms> transformsList;
	std::vector<NodeTransforms> currentPose;
	std::vector<NodeTransforms> basePose;

	NodeTransformsList();
};

void calcTransformMat(Transform* t);

static void FKSingle(std::vector<NodeTransforms>& t, std::vector<HierarchyNode>& nodes, int index)
{
	int parent = nodes[index].parentIndex;
	t[index].global.transformMat = t[parent].global.transformMat * t[index].local.transformMat;
}
static void FKSolver(std::vector<NodeTransforms>& t, std::vector<HierarchyNode> nodes)
{
	for (int i = 0; i < t.size(); i++)
	{
		int parent = nodes[i].parentIndex;
		if (parent == -1)
		{
			t[i].global.transformMat = t[i].local.transformMat;
			continue;
		}

		t[i].global.transformMat = t[parent].global.transformMat * t[i].local.transformMat;
	}
}