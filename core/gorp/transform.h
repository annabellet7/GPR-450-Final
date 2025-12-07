#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
public:
	glm::vec4 translate;
	glm::vec4 rotate;
	glm::vec4 scale;
	glm::mat4 transformMat;
};