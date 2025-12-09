#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include <stack>

class HierarchyNode
{
public:
	std::string name;
	int parentIndex;
	int selfIndex;

	HierarchyNode();
	void setNode(std::string name, int parent, int self);
	int GetNode();
};

