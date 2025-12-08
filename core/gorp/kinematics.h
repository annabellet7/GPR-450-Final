#pragma once
#include "hierarchyList.h"


void poseConcat(HierarchyList* list);
void poseCovert(HierarchyList* list);
void basePoseCovert(HierarchyList* list);
void solveFKSingle(HierarchyList* list, int index);
void baseSolveFKSingle(HierarchyList* list, int index);
void solveFK(HierarchyList* list);
void baseSolveFK(HierarchyList* list);