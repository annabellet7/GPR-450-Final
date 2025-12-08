#include "transform.h"

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