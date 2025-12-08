#include "transform.h"

NodeTransforms::NodeTransforms()
{
	nodeIndex = -1;
	keyframeIndex = -1;

	local.translate = glm::vec4(0.0);
	local.rotate = glm::vec4(0.0);
	local.scale = glm::vec4(1.0);
	local.transformMat = glm::mat4(0.0);

	invLocal.translate = glm::vec4(0.0);
	invLocal.rotate = glm::vec4(0.0);
	invLocal.scale = glm::vec4(1.0);
	invLocal.transformMat = glm::mat4(0.0);

	global .translate = glm::vec4(0.0);
	global.rotate = glm::vec4(0.0);
	global.scale = glm::vec4(1.0);
	global.transformMat = glm::mat4(0.0);

	invGlobal.translate = glm::vec4(0.0);
	invGlobal.rotate = glm::vec4(0.0);
	invGlobal.scale = glm::vec4(1.0);
	invGlobal.transformMat = glm::mat4(0.0);
}

NodeTransformsList::NodeTransformsList()
{
	
}

void calcTransformMat(Transform* t)
{
	glm::mat4 Rx = glm::mat4(0), Ry = glm::mat4(0), Rz = glm::mat4(0), R = glm::mat4(0);
	float c = glm::cos(t->rotate.x);
	float s = glm::sin(t->rotate.x);
	Rx[0][0] = Rx[3][3] = 1;
	Rx[1][1] = Rx[2][2] = c;
	Rx[1][2] = -s;
	Rx[2][1] = s;

	c = glm::cos(t->rotate.y);
	s = glm::sin(t->rotate.y);
	Ry[1][1] = Ry[3][3] = 1;
	Ry[0][0] = Ry[2][2] = c;
	Ry[2][0] = -s;
	Ry[0][2] = s;

	c = glm::cos(t->rotate.z);
	s = glm::sin(t->rotate.z);
	Rz[2][2] = Rz[3][3] = 1;
	Rz[0][0] = Rz[1][1] = c;
	Rz[0][1] = -s;
	Rz[1][0] = s;

	//zyx
	R = Rz * Ry;
	t->transformMat = R * Rx;


	t->transformMat[3] = t->translate;
}