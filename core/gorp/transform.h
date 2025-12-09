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

	friend Transform operator+(const Transform& lhs, const Transform& rhs);
};

class NodeTransform
{
public:
	int nodeIndex;
	int keyframeIndex;
	Transform local; //node relative to parent
	Transform invLocal; //parent relative to node
	Transform global; //node relative to root parent
	Transform invGlobal; //root parent relative to node

	NodeTransform();
	friend NodeTransform operator+(const NodeTransform& lhs, const NodeTransform& rhs);
};

class NodeTransformsList
{
public:
	std::vector<NodeTransform> transformsList;
	std::vector<NodeTransform> currentPose;
	std::vector<NodeTransform> basePose;
	std::vector<NodeTransform> objectSpaceBindToCurrent;

	NodeTransformsList();
	int getTransformAtNodeIndex(int index);
	int getTransformAtKeyframeIndex(int index);
};

void calcTransformMat(Transform &t);

