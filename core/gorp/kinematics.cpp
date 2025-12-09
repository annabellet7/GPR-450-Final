#include "kinematics.h"

void poseConcat(HierarchyList* list)
{
	for (int i = 0; i < list->hierarchy->nodeList.size(); i++)
	{
		list->nodePoseList->currentPose[i].local = list->nodePoseList->currentPose[i].local + list->nodePoseList->basePose[i].local;
	}
}

void poseCovert(HierarchyList* list)
{
	for (int i = 0; i < list->hierarchy->nodeList.size(); i++)
	{
		glm::mat4 Rx = glm::mat4(0), Ry = glm::mat4(0), Rz = glm::mat4(0), R = glm::mat4(0);
		float c = glm::cos(list->nodePoseList->currentPose[i].local.rotate.x);
		float s = glm::sin(list->nodePoseList->currentPose[i].local.rotate.x);
		Rx[0][0] = Rx[3][3] = 1;
		Rx[1][1] = Rx[2][2] = c;
		Rx[1][2] = -s;
		Rx[2][1] = s;

		c = glm::cos(list->nodePoseList->currentPose[i].local.rotate.y);
		s = glm::sin(list->nodePoseList->currentPose[i].local.rotate.y);
		Ry[1][1] = Ry[3][3] = 1;
		Ry[0][0] = Ry[2][2] = c;
		Ry[2][0] = -s;
		Ry[0][2] = s;

		c = glm::cos(list->nodePoseList->currentPose[i].local.rotate.z);
		s = glm::sin(list->nodePoseList->currentPose[i].local.rotate.z);
		Rz[2][2] = Rz[3][3] = 1;
		Rz[0][0] = Rz[1][1] = c;
		Rz[0][1] = -s;
		Rz[1][0] = s;

		//zyx
		R = Rz * Ry;
		list->nodePoseList->currentPose[i].local.transformMat = R * Rx;

		list->nodePoseList->currentPose[i].local.transformMat[3] = list->nodePoseList->currentPose[i].local.translate;
	}
}

void basePoseCovert(HierarchyList* list)
{
	for (int i = 0; i < list->hierarchy->nodeList.size(); i++)
	{
		glm::mat4 Rx = glm::mat4(0), Ry = glm::mat4(0), Rz = glm::mat4(0), R = glm::mat4(0);
		float c = glm::cos(list->nodePoseList->basePose[i].local.rotate.x);
		float s = glm::sin(list->nodePoseList->basePose[i].local.rotate.x);
		Rx[0][0] = Rx[3][3] = 1;
		Rx[1][1] = Rx[2][2] = c;
		Rx[1][2] = -s;
		Rx[2][1] = s;

		c = glm::cos(list->nodePoseList->basePose[i].local.rotate.y);
		s = glm::sin(list->nodePoseList->basePose[i].local.rotate.y);
		Ry[1][1] = Ry[3][3] = 1;
		Ry[0][0] = Ry[2][2] = c;
		Ry[2][0] = -s;
		Ry[0][2] = s;

		c = glm::cos(list->nodePoseList->basePose[i].local.rotate.z);
		s = glm::sin(list->nodePoseList->basePose[i].local.rotate.z);
		Rz[2][2] = Rz[3][3] = 1;
		Rz[0][0] = Rz[1][1] = c;
		Rz[0][1] = -s;
		Rz[1][0] = s;

		//zyx
		R = Rz * Ry;
		list->nodePoseList->basePose[i].local.transformMat = R * Rx;

		list->nodePoseList->basePose[i].local.transformMat[3] = list->nodePoseList->basePose[i].local.translate;
	}
}

void solveFKSingle (HierarchyList* list, int index)
{
	int parent = list->hierarchy->nodeList[index].parentIndex;
	list->nodePoseList->currentPose[index].global.transformMat = list->nodePoseList->currentPose[parent].global.transformMat * list->nodePoseList->currentPose[index].local.transformMat;
}

void baseSolveFKSingle(HierarchyList* list, int index)
{
	int parent = list->hierarchy->nodeList[index].parentIndex;
	list->nodePoseList->basePose[index].global.transformMat = list->nodePoseList->basePose[parent].global.transformMat * list->nodePoseList->basePose[index].local.transformMat;
}

void solveFK(HierarchyList* list)
{
	for (int i = 0; i < list->hierarchy->nodeList.size(); i++)
	{
		if (list->hierarchy->nodeList[i].parentIndex >= 0)
		{
			solveFKSingle(list, i);
		}
		else
		{
			list->nodePoseList->currentPose[i].global.transformMat = list->nodePoseList->currentPose[i].local.transformMat;
		}
	}
}

void baseSolveFK(HierarchyList* list)
{
	for (int i = 0; i < list->hierarchy->nodeList.size(); i++)
	{
		if (list->hierarchy->nodeList[i].parentIndex >= 0)
		{
			baseSolveFKSingle(list, i);
		}
		else
		{
			list->nodePoseList->basePose[i].global.transformMat = list->nodePoseList->basePose[i].local.transformMat;
		}
	}
}

void poseRestore(NodeTransform* node)
{
}

void resolvePostIK(HierarchyList* list, int index, glm::mat4 object)
{
	list->nodePoseList->currentPose[index].global = object;
	list->nodePoseList->currentPose[index].invGlobal = glm::inverse(object);

	solveIKSingle(list, index, list->hierarchy->nodeList[index].parentIndex);
	
	poseRestore(list->nodePoseList->currentPose[index]);
	poseDeconcat(list->nodePoseList->currentPose[index].local,
		list->nodePoseList->currentPose[index].local,
		list->nodePoseList->basePose[index].local);
}

void updateLimbIK(HierarchyList* list, int const baseIndex, int const hingeIndex, int const endIndex, int const constraintIndex, glm::vec3 targetPosition)
{
	glm::mat4 baseObject = list->nodePoseList->currentPose[baseIndex].global.transformMat;
	glm::mat4 hingeObject = list->nodePoseList->currentPose[hingeIndex].global.transformMat;
	glm::mat4 endObject = list->nodePoseList->currentPose[endIndex].global.transformMat;

	//Solve IK
	{

	}

	//Resolve IK
	{
		resolvePostIK(list, baseIndex, baseObject.m);
		resolvePostIK(list, hingeIndex, hingeObject.m);
		resolvePostIK(list, endIndex, endObject.m);
	}
}


