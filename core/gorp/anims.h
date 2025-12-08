#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "transform.h"

class Anim
{
public:
	std::string name;
	//map node name or index to a list of node transforms
	std::unordered_map<std::string, std::vector<NodeTransform>> tNode; //for accessing use tNode[name] and that will be the nodetransform mapped to that name
};