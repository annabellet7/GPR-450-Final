#include "hierarchyList.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

HierarchyList::HierarchyList()
{
	hierarchy = new Hierarchy;
	nodePoseList = new NodeTransformsList;
}

HierarchyList::~HierarchyList()
{
	delete hierarchy;
	delete nodePoseList;
}

void HierarchyList::poseLerp(int keyframeIndex0, int keyframeIndex1, int numNodes, float t)
{
	for (int i = 0; i < numNodes; i++)
	{
		nodePoseList->currentPose[i].local.rotate.x = (nodePoseList->transformsList[keyframeIndex1].local.rotate.x
													- nodePoseList->transformsList[keyframeIndex0].local.rotate.x) * t
													+ nodePoseList->transformsList[keyframeIndex0].local.rotate.x;

		nodePoseList->currentPose[i].local.rotate.y = (nodePoseList->transformsList[keyframeIndex1].local.rotate.y
													- nodePoseList->transformsList[keyframeIndex0].local.rotate.y) * t
													+ nodePoseList->transformsList[keyframeIndex0].local.rotate.y;

		nodePoseList->currentPose[i].local.rotate.z = (nodePoseList->transformsList[keyframeIndex1].local.rotate.z
													- nodePoseList->transformsList[keyframeIndex0].local.rotate.z) * t
													+ nodePoseList->transformsList[keyframeIndex0].local.rotate.z;


		nodePoseList->currentPose[i].local.translate.x = (nodePoseList->transformsList[keyframeIndex1].local.translate.x
														- nodePoseList->transformsList[keyframeIndex0].local.translate.x) * t
														+ nodePoseList->transformsList[keyframeIndex0].local.translate.x;

		nodePoseList->currentPose[i].local.translate.y = (nodePoseList->transformsList[keyframeIndex1].local.translate.y
														- nodePoseList->transformsList[keyframeIndex0].local.translate.y) * t
														+ nodePoseList->transformsList[keyframeIndex0].local.translate.y;

		nodePoseList->currentPose[i].local.translate.z = (nodePoseList->transformsList[keyframeIndex1].local.translate.z
														- nodePoseList->transformsList[keyframeIndex0].local.translate.z) * t
														+ nodePoseList->transformsList[keyframeIndex0].local.translate.z;
	}
}

void HierarchyList::updateLocalInverse(HierarchyList* list)
{
	for (int i = 0; i < list->hierarchy->nodeList.size(); i++)
	{
		glm::mat4 local = list->nodePoseList->currentPose[i].local.transformMat;
		glm::mat4 invLocal = list->nodePoseList->currentPose[i].invLocal.transformMat;

		const float sx2 = glm::dot(local[0], local[0]);
		const float sy2 = glm::dot(local[1], local[1]);
		const float sz2 = glm::dot(local[2], local[2]);

		invLocal[0][0] = local[0][0] * sx2;	invLocal[1][0] = local[0][1] * sx2;	invLocal[2][0] = local[0][2] * sx2;
		invLocal[0][1] = local[1][0] * sy2;	invLocal[1][1] = local[1][1] * sy2;	invLocal[2][1] = local[1][2] * sy2;
		invLocal[0][2] = local[2][0] * sz2;	invLocal[1][2] = local[2][1] * sz2;	invLocal[2][2] = local[2][2] * sz2;

		invLocal[3][0] = -(invLocal[0][0] * local[3][0] + invLocal[1][0] * local[3][1] + invLocal[2][0] * local[3][2]);
		invLocal[3][1] = -(invLocal[0][1] * local[3][0] + invLocal[1][1] * local[3][1] + invLocal[2][1] * local[3][2]);
		invLocal[3][2] = -(invLocal[0][2] * local[3][0] + invLocal[1][2] * local[3][1] + invLocal[2][2] * local[3][2]);

		invLocal[0][3] = invLocal[1][3] = invLocal[2][3] = 0.0;
		invLocal[3][3] = 1.0;

		list->nodePoseList->currentPose[i].invLocal.transformMat = invLocal;
	}
	
}

void HierarchyList::baseUpdateLocalInverse(HierarchyList* list)
{
	for (int i = 0; i < list->hierarchy->nodeList.size(); i++)
	{
		glm::mat4 local = list->nodePoseList->basePose[i].local.transformMat;
		glm::mat4 invLocal = list->nodePoseList->basePose[i].invLocal.transformMat;

		const float sx2 = glm::dot(local[0], local[0]);
		const float sy2 = glm::dot(local[1], local[1]);
		const float sz2 = glm::dot(local[2], local[2]);

		invLocal[0][0] = local[0][0] * sx2;	invLocal[1][0] = local[0][1] * sx2;	invLocal[2][0] = local[0][2] * sx2;
		invLocal[0][1] = local[1][0] * sy2;	invLocal[1][1] = local[1][1] * sy2;	invLocal[2][1] = local[1][2] * sy2;
		invLocal[0][2] = local[2][0] * sz2;	invLocal[1][2] = local[2][1] * sz2;	invLocal[2][2] = local[2][2] * sz2;

		invLocal[3][0] = -(invLocal[0][0] * local[3][0] + invLocal[1][0] * local[3][1] + invLocal[2][0] * local[3][2]);
		invLocal[3][1] = -(invLocal[0][1] * local[3][0] + invLocal[1][1] * local[3][1] + invLocal[2][1] * local[3][2]);
		invLocal[3][2] = -(invLocal[0][2] * local[3][0] + invLocal[1][2] * local[3][1] + invLocal[2][2] * local[3][2]);

		invLocal[0][3] = invLocal[1][3] = invLocal[2][3] = 0.0;
		invLocal[3][3] = 1.0;

		list->nodePoseList->basePose[i].invLocal.transformMat = invLocal;
	}

}

void HierarchyList::updateGlobalInverse(HierarchyList* list)
{
	for (int i = 0; i < list->hierarchy->nodeList.size(); i++)
	{
		glm::mat4 global = list->nodePoseList->currentPose[i].global.transformMat;
		glm::mat4 invGlobal = list->nodePoseList->currentPose[i].invGlobal.transformMat;

		const float sx2 = glm::dot(global[0], global[0]);
		const float sy2 = glm::dot(global[1], global[1]);
		const float sz2 = glm::dot(global[2], global[2]);

		invGlobal[0][0] = global[0][0] * sx2;	invGlobal[1][0] = global[0][1] * sx2;	invGlobal[2][0] = global[0][2] * sx2;
		invGlobal[0][1] = global[1][0] * sy2;	invGlobal[1][1] = global[1][1] * sy2;	invGlobal[2][1] = global[1][2] * sy2;
		invGlobal[0][2] = global[2][0] * sz2;	invGlobal[1][2] = global[2][1] * sz2;	invGlobal[2][2] = global[2][2] * sz2;

		invGlobal[3][0] = -(invGlobal[0][0] * global[3][0] + invGlobal[1][0] * global[3][1] + invGlobal[2][0] * global[3][2]);
		invGlobal[3][1] = -(invGlobal[0][1] * global[3][0] + invGlobal[1][1] * global[3][1] + invGlobal[2][1] * global[3][2]);
		invGlobal[3][2] = -(invGlobal[0][2] * global[3][0] + invGlobal[1][2] * global[3][1] + invGlobal[2][2] * global[3][2]);

		invGlobal[0][3] = invGlobal[1][3] = invGlobal[2][3] = 0.0;
		invGlobal[3][3] = 1.0;

		list->nodePoseList->currentPose[i].invGlobal .transformMat = invGlobal;
	}
}

void HierarchyList::baseUpdateGlobalInverse(HierarchyList* list)
{
	for (int i = 0; i < list->hierarchy->nodeList.size(); i++)
	{
		glm::mat4 global = list->nodePoseList->basePose[i].global.transformMat;
		glm::mat4 invGlobal = list->nodePoseList->basePose[i].invGlobal.transformMat;

		const float sx2 = glm::dot(global[0], global[0]);
		const float sy2 = glm::dot(global[1], global[1]);
		const float sz2 = glm::dot(global[2], global[2]);

		invGlobal[0][0] = global[0][0] * sx2;	invGlobal[1][0] = global[0][1] * sx2;	invGlobal[2][0] = global[0][2] * sx2;
		invGlobal[0][1] = global[1][0] * sy2;	invGlobal[1][1] = global[1][1] * sy2;	invGlobal[2][1] = global[1][2] * sy2;
		invGlobal[0][2] = global[2][0] * sz2;	invGlobal[1][2] = global[2][1] * sz2;	invGlobal[2][2] = global[2][2] * sz2;

		invGlobal[3][0] = -(invGlobal[0][0] * global[3][0] + invGlobal[1][0] * global[3][1] + invGlobal[2][0] * global[3][2]);
		invGlobal[3][1] = -(invGlobal[0][1] * global[3][0] + invGlobal[1][1] * global[3][1] + invGlobal[2][1] * global[3][2]);
		invGlobal[3][2] = -(invGlobal[0][2] * global[3][0] + invGlobal[1][2] * global[3][1] + invGlobal[2][2] * global[3][2]);

		invGlobal[0][3] = invGlobal[1][3] = invGlobal[2][3] = 0.0;
		invGlobal[3][3] = 1.0;

		list->nodePoseList->basePose[i].invGlobal.transformMat = invGlobal;
	}
}

void HierarchyList::updateObjectBindToCurrent(HierarchyList* list)
{
	for (int i = 0; i < list->hierarchy->nodeList.size(); i++)
	{
		list->nodePoseList->objectSpaceBindToCurrent[i].global.transformMat = list->nodePoseList->currentPose[i].global.transformMat * list->nodePoseList->basePose[i].invGlobal.transformMat;
	}
}
