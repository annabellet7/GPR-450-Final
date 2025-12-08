#include "transform.h"
# include <assert.h>

Transform operator+(const Transform& lhs, const Transform& rhs)
{
	Transform t;
	t.translate = lhs.translate + rhs.translate;
	t.rotate = lhs.rotate + rhs.rotate;
	t.scale = lhs.scale * rhs.scale;
	//t.transformMat = lhs.transformMat + rhs.transformMat;
	return t;
}

NodeTransform::NodeTransform()
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

NodeTransform operator+(const NodeTransform& lhs, const NodeTransform& rhs)
{
	assert(lhs.nodeIndex == rhs.nodeIndex);
	assert(lhs.keyframeIndex == rhs.keyframeIndex);

	NodeTransform t;
	t.nodeIndex = lhs.nodeIndex;
	t.keyframeIndex = lhs.keyframeIndex;

	t.local.translate = lhs.local.translate + rhs.local.translate;
	t.local.rotate = lhs.local.rotate + rhs.local.rotate;
	t.local.scale = lhs.local.scale + rhs.local.scale;
	t.local.transformMat = lhs.local.transformMat + rhs.local.transformMat;

	t.invLocal.translate = lhs.invLocal.translate + rhs.invLocal.translate;
	t.invLocal.rotate = lhs.invLocal.rotate + rhs.invLocal.rotate;
	t.invLocal.scale = lhs.invLocal.scale + rhs.invLocal.scale;
	t.invLocal.transformMat = lhs.invLocal.transformMat + rhs.invLocal.transformMat;

	t.global.translate = lhs.global.translate + rhs.global.translate;
	t.global.rotate = lhs.global.rotate + rhs.global.rotate;
	t.global.scale = lhs.global.scale + rhs.global.scale;
	t.global.transformMat = lhs.global.transformMat + rhs.global.transformMat;

	t.invGlobal.translate = lhs.invGlobal.translate + rhs.invGlobal.translate;
	t.invGlobal.rotate = lhs.invGlobal.rotate + rhs.invGlobal.rotate;
	t.invGlobal.scale = lhs.invGlobal.scale + rhs.invGlobal.scale;
	t.invGlobal.transformMat = lhs.invGlobal.transformMat + rhs.invGlobal.transformMat;

	return t;
}

NodeTransformsList::NodeTransformsList()
{
	
}

void calcTransformMat(Transform &t)
{
	glm::mat4 Rx = glm::mat4(0), Ry = glm::mat4(0), Rz = glm::mat4(0), R = glm::mat4(0);
	float c = glm::cos(t.rotate.x);
	float s = glm::sin(t.rotate.x);
	Rx[0][0] = Rx[3][3] = 1;
	Rx[1][1] = Rx[2][2] = c;
	Rx[1][2] = -s;
	Rx[2][1] = s;

	c = glm::cos(t.rotate.y);
	s = glm::sin(t.rotate.y);
	Ry[1][1] = Ry[3][3] = 1;
	Ry[0][0] = Ry[2][2] = c;
	Ry[2][0] = -s;
	Ry[0][2] = s;

	c = glm::cos(t.rotate.z);
	s = glm::sin(t.rotate.z);
	Rz[2][2] = Rz[3][3] = 1;
	Rz[0][0] = Rz[1][1] = c;
	Rz[0][1] = -s;
	Rz[1][0] = s;

	//zyx
	R = Rz * Ry;
	t.transformMat = R * Rx;
	t.transformMat[3] = t.translate;
}