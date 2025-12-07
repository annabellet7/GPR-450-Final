#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Transform
{
public:
	glm::vec4 translate;
	glm::vec4 rotate;
	glm::vec4 scale;
	glm::mat4 transformMat;
};

class nodeTransforms
{
public:
	Transform local; //node relative to parent
	Transform invLocal; //parent relative to node
	Transform global; //node relative to root parent
	Transform invGlobal; //root parent relative to node
};