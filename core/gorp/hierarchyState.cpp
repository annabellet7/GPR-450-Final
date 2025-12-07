#include "hierarchyState.h"

HierarchyState::HierarchyState(Hierarchy* hierarchy)
{
	mHierarchy = hierarchy;
}

void HierarchyState::updateLocalInverse(HierarchyState* state)
{
	if (state && state->mHierarchy)
	{
		for (int i = 0; i < state->animList.size(); i++)
		{
			for (int j = 0; j < state->mHierarchy->nodeList.size(); j++)
			{
				std::string name = state->mHierarchy->nodeList[i].name;
				const float sx2 = 1.0 / glm::dot(state->animList[i].tNode[name][j].local.transformMat[0], state->animList[i].tNode[name][j].local.transformMat[0]);
				const float sy2 = 1.0 / glm::dot(state->animList[i].tNode[name][j].local.transformMat[1], state->animList[i].tNode[name][j].local.transformMat[1]);
				const float sz2 = 1.0 / glm::dot(state->animList[i].tNode[name][j].local.transformMat[2], state->animList[i].tNode[name][j].local.transformMat[2]);

				//update x rotation
				state->animList[i].tNode[name][j].invLocal.transformMat[0][0] = state->animList[i].tNode[name][j].local.transformMat[0][0] * sx2;
				state->animList[i].tNode[name][j].invLocal.transformMat[1][0] = state->animList[i].tNode[name][j].local.transformMat[0][1] * sx2;
				state->animList[i].tNode[name][j].invLocal.transformMat[2][0] = state->animList[i].tNode[name][j].local.transformMat[0][2] * sx2;

				//update y roation
				state->animList[i].tNode[name][j].invLocal.transformMat[0][1] = state->animList[i].tNode[name][j].local.transformMat[1][0] * sy2;
				state->animList[i].tNode[name][j].invLocal.transformMat[1][1] = state->animList[i].tNode[name][j].local.transformMat[1][1] * sy2;
				state->animList[i].tNode[name][j].invLocal.transformMat[2][1] = state->animList[i].tNode[name][j].local.transformMat[1][2] * sy2;

				//update z roation
				state->animList[i].tNode[name][j].invLocal.transformMat[0][2] = state->animList[i].tNode[name][j].local.transformMat[2][0] * sz2;
				state->animList[i].tNode[name][j].invLocal.transformMat[1][2] = state->animList[i].tNode[name][j].local.transformMat[2][1] * sz2;
				state->animList[i].tNode[name][j].invLocal.transformMat[2][2] = state->animList[i].tNode[name][j].local.transformMat[2][2] * sz2;

				//update position
				state->animList[i].tNode[name][j].invLocal.transformMat[3][0] = -(state->animList[i].tNode[name][j].invLocal.transformMat[0][0] * state->animList[i].tNode[name][j].local.transformMat[3][0]
					+ state->animList[i].tNode[name][j].invLocal.transformMat[1][0] * state->animList[i].tNode[name][j].local.transformMat[3][1]
					+ state->animList[i].tNode[name][j].invLocal.transformMat[2][0] * state->animList[i].tNode[name][j].local.transformMat[3][2]);
				state->animList[i].tNode[name][j].invLocal.transformMat[3][1] = -(state->animList[i].tNode[name][j].invLocal.transformMat[0][1] * state->animList[i].tNode[name][j].local.transformMat[3][0]
					+ state->animList[i].tNode[name][j].invLocal.transformMat[1][1] * state->animList[i].tNode[name][j].local.transformMat[3][1]
					+ state->animList[i].tNode[name][j].invLocal.transformMat[2][1] * state->animList[i].tNode[name][j].local.transformMat[3][2]);
				state->animList[i].tNode[name][j].invLocal.transformMat[3][2] = -(state->animList[i].tNode[name][j].invLocal.transformMat[0][2] * state->animList[i].tNode[name][j].local.transformMat[3][0]
					+ state->animList[i].tNode[name][j].invLocal.transformMat[1][2] * state->animList[i].tNode[name][j].local.transformMat[3][1]
					+ state->animList[i].tNode[name][j].invLocal.transformMat[2][2] * state->animList[i].tNode[name][j].local.transformMat[3][2]);

				state->animList[i].tNode[name][j].invLocal.transformMat[0][3] = state->animList[i].tNode[name][j].invLocal.transformMat[1][3] = state->animList[i].tNode[name][j].invLocal.transformMat[2][3] = 0.0;
				state->animList[i].tNode[name][j].invLocal.transformMat[3][3] = 1.0;
			}
		}
	}
}

void HierarchyState::updateWorldInverse(HierarchyState* state)
{
	if (state && state->mHierarchy)
	{
		for (int i = 0; i < state->mHierarchy->nodeList.size(); i++)
		{
			for (int j = 0; j < state->mHierarchy->nodeList.size(); j++)
			{
				std::string name = state->mHierarchy->nodeList[i].name;
				const float sx2 = 1.0 / glm::dot(state->animList[i].tNode[name][j].global.transformMat[0], state->animList[i].tNode[name][j].global.transformMat[0]);
				const float sy2 = 1.0 / glm::dot(state->animList[i].tNode[name][j].global.transformMat[1], state->animList[i].tNode[name][j].global.transformMat[1]);
				const float sz2 = 1.0 / glm::dot(state->animList[i].tNode[name][j].global.transformMat[2], state->animList[i].tNode[name][j].global.transformMat[2]);

				//update x rotation
				state->animList[i].tNode[name][j].invGlobal.transformMat[0][0] = state->animList[i].tNode[name][j].global.transformMat[0][0] * sx2;
				state->animList[i].tNode[name][j].invGlobal.transformMat[1][0] = state->animList[i].tNode[name][j].global.transformMat[0][1] * sx2;
				state->animList[i].tNode[name][j].invGlobal.transformMat[2][0] = state->animList[i].tNode[name][j].global.transformMat[0][2] * sx2;

				//update y roation
				state->animList[i].tNode[name][j].invGlobal.transformMat[0][1] = state->animList[i].tNode[name][j].global.transformMat[1][0] * sy2;
				state->animList[i].tNode[name][j].invGlobal.transformMat[1][1] = state->animList[i].tNode[name][j].global.transformMat[1][1] * sy2;
				state->animList[i].tNode[name][j].invGlobal.transformMat[2][1] = state->animList[i].tNode[name][j].global.transformMat[1][2] * sy2;

				//update z roation
				state->animList[i].tNode[name][j].invGlobal.transformMat[0][2] = state->animList[i].tNode[name][j].global.transformMat[2][0] * sz2;
				state->animList[i].tNode[name][j].invGlobal.transformMat[1][2] = state->animList[i].tNode[name][j].global.transformMat[2][1] * sz2;
				state->animList[i].tNode[name][j].invGlobal.transformMat[2][2] = state->animList[i].tNode[name][j].global.transformMat[2][2] * sz2;

				//update position
				state->animList[i].tNode[name][j].invGlobal.transformMat[3][0] = -(state->animList[i].tNode[name][j].invGlobal.transformMat[0][0] * state->animList[i].tNode[name][j].global.transformMat[3][0]
					+ state->animList[i].tNode[name][j].invGlobal.transformMat[1][0] * state->animList[i].tNode[name][j].global.transformMat[3][1]
					+ state->animList[i].tNode[name][j].invGlobal.transformMat[2][0] * state->animList[i].tNode[name][j].global.transformMat[3][2]);
				state->animList[i].tNode[name][j].invGlobal.transformMat[3][1] = -(state->animList[i].tNode[name][j].invGlobal.transformMat[0][1] * state->animList[i].tNode[name][j].global.transformMat[3][0]
					+ state->animList[i].tNode[name][j].invGlobal.transformMat[1][1] * state->animList[i].tNode[name][j].global.transformMat[3][1]
					+ state->animList[i].tNode[name][j].invGlobal.transformMat[2][1] * state->animList[i].tNode[name][j].global.transformMat[3][2]);
				state->animList[i].tNode[name][j].invGlobal.transformMat[3][2] = -(state->animList[i].tNode[name][j].invGlobal.transformMat[0][2] * state->animList[i].tNode[name][j].global.transformMat[3][0]
					+ state->animList[i].tNode[name][j].invGlobal.transformMat[1][2] * state->animList[i].tNode[name][j].global.transformMat[3][1]
					+ state->animList[i].tNode[name][j].invGlobal.transformMat[2][2] * state->animList[i].tNode[name][j].global.transformMat[3][2]);

				state->animList[i].tNode[name][j].invGlobal.transformMat[0][3] = state->animList[i].tNode[name][j].invGlobal.transformMat[1][3] = state->animList[i].tNode[name][j].invGlobal.transformMat[2][3] = 0.0;
				state->animList[i].tNode[name][j].invGlobal.transformMat[3][3] = 1.0;
			}
		}
	}
}
