#include "hierarchyState.h"

HierarchyState::HierarchyState(Hierarchy* hierarchy)
{
	mHierarchy = hierarchy;
}

void HierarchyState::updateLocalInverse(HierarchyState* state)
{
	if (state && state->mHierarchy)
	{
		for (int i = 0; i < state->mHierarchy->nodeList.size(); i++)
		{
			const float sx2 = 1.0 / glm::dot(state->local[i].transformMat[0], state->local[i].transformMat[0]);
			const float sy2 = 1.0 / glm::dot(state->local[i].transformMat[1], state->local[i].transformMat[1]);
			const float sz2 = 1.0 / glm::dot(state->local[i].transformMat[2], state->local[i].transformMat[2]);

			//update x rotation
			state->invLocal[i].transformMat[0][0] = state->local[i].transformMat[0][0] * sx2; 
			state->invLocal[i].transformMat[1][0] = state->local[i].transformMat[0][1] * sx2;
			state->invLocal[i].transformMat[2][0] = state->local[i].transformMat[0][2] * sx2;

			//update y roation
			state->invLocal[i].transformMat[0][1] = state->local[i].transformMat[1][0] * sy2;
			state->invLocal[i].transformMat[1][1] = state->local[i].transformMat[1][1] * sy2;
			state->invLocal[i].transformMat[2][1] = state->local[i].transformMat[1][2] * sy2;

			//update z roation
			state->invLocal[i].transformMat[0][2] = state->local[i].transformMat[2][0] * sz2;
			state->invLocal[i].transformMat[1][2] = state->local[i].transformMat[2][1] * sz2;
			state->invLocal[i].transformMat[2][2] = state->local[i].transformMat[2][2] * sz2;

			//update position
			state->invLocal[i].transformMat[3][0] = -(state->invLocal[i].transformMat[0][0] * state->local[i].transformMat[3][0]
													+ state->invLocal[i].transformMat[1][0] * state->local[i].transformMat[3][1]
													+ state->invLocal[i].transformMat[2][0] * state->local[i].transformMat[3][2]);
			state->invLocal[i].transformMat[3][1] = -(state->invLocal[i].transformMat[0][1] * state->local[i].transformMat[3][0]
													+ state->invLocal[i].transformMat[1][1] * state->local[i].transformMat[3][1]
													+ state->invLocal[i].transformMat[2][1] * state->local[i].transformMat[3][2]);
			state->invLocal[i].transformMat[3][2] = -(state->invLocal[i].transformMat[0][2] * state->local[i].transformMat[3][0]
													+ state->invLocal[i].transformMat[1][2] * state->local[i].transformMat[3][1]
													+ state->invLocal[i].transformMat[2][2] * state->local[i].transformMat[3][2]);

			state->invLocal[i].transformMat[0][3] = state->invLocal[i].transformMat[1][3] = state->invGlobal[i].transformMat[2][3] = 0.0;
			state->invLocal[i].transformMat[3][3] = 1.0;
		}
	}
}

void HierarchyState::updateWorldInverse(HierarchyState* state)
{
	if (state && state->mHierarchy)
	{
		for (int i = 0; i < state->mHierarchy->nodeList.size(); i++)
		{
			const float sx2 = 1.0 / glm::dot(state->global[i].transformMat[0], state->global[i].transformMat[0]);
			const float sy2 = 1.0 / glm::dot(state->global[i].transformMat[1], state->global[i].transformMat[1]);
			const float sz2 = 1.0 / glm::dot(state->global[i].transformMat[2], state->global[i].transformMat[2]);

			//update x rotation
			state->invGlobal[i].transformMat[0][0] = state->global[i].transformMat[0][0] * sx2;
			state->invGlobal[i].transformMat[1][0] = state->global[i].transformMat[0][1] * sx2;
			state->invGlobal[i].transformMat[2][0] = state->global[i].transformMat[0][2] * sx2;

			//update y roation
			state->invGlobal[i].transformMat[0][1] = state->global[i].transformMat[1][0] * sy2;
			state->invGlobal[i].transformMat[1][1] = state->global[i].transformMat[1][1] * sy2;
			state->invGlobal[i].transformMat[2][1] = state->global[i].transformMat[1][2] * sy2;

			//update z roation
			state->invGlobal[i].transformMat[0][2] = state->global[i].transformMat[2][0] * sz2;
			state->invGlobal[i].transformMat[1][2] = state->global[i].transformMat[2][1] * sz2;
			state->invGlobal[i].transformMat[2][2] = state->global[i].transformMat[2][2] * sz2;

			//update position
			state->invGlobal[i].transformMat[3][0] = -(state->invGlobal[i].transformMat[0][0] * state->global[i].transformMat[3][0]
				+ state->invGlobal[i].transformMat[1][0] * state->global[i].transformMat[3][1]
				+ state->invGlobal[i].transformMat[2][0] * state->global[i].transformMat[3][2]);
			state->invGlobal[i].transformMat[3][1] = -(state->invGlobal[i].transformMat[0][1] * state->global[i].transformMat[3][0]
				+ state->invGlobal[i].transformMat[1][1] * state->global[i].transformMat[3][1]
				+ state->invGlobal[i].transformMat[2][1] * state->global[i].transformMat[3][2]);
			state->invGlobal[i].transformMat[3][2] = -(state->invGlobal[i].transformMat[0][2] * state->global[i].transformMat[3][0]
				+ state->invGlobal[i].transformMat[1][2] * state->global[i].transformMat[3][1]
				+ state->invGlobal[i].transformMat[2][2] * state->global[i].transformMat[3][2]);

			state->invGlobal[i].transformMat[0][3] = state->invGlobal[i].transformMat[1][3] = state->invGlobal[i].transformMat[2][3] = 0.0;
			state->invGlobal[i].transformMat[3][3] = 1.0;
		}
	}
}
