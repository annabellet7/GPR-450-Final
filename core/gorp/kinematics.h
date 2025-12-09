#pragma once
#include "hierarchyList.h"

//Things for FK (Annabelle)
void poseConcat(HierarchyList* list);
void poseCovert(HierarchyList* list);
void basePoseCovert(HierarchyList* list);
void solveFKSingle(HierarchyList* list, int index);
void baseSolveFKSingle(HierarchyList* list, int index);
void solveFK(HierarchyList* list);
void baseSolveFK(HierarchyList* list);

//Things for IK (Victor)
void poseRestore(NodeTransform* node);
void poseDeconcat(Transform* node_out, Transform const* LHS, Transform const* RHS);
void solveIKSingle(HierarchyList* list, int const index, int const parentIndex);
void resolvePostIK(HierarchyList* list, int const index, glm::mat4 const result);
void updateLimbIK(HierarchyList* list, int const baseIndex, int const hingeIndex, int const endIndex, int const constraintIndex, glm::vec3 targetPosition);