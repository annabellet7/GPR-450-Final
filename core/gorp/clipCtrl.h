#pragma once
#include <string>
#include <vector>
#include "keyframe.h"
#include "hierarchyNode.h"

struct clipCtrl
{
public:
	std::string name = "";
	int clipIndex = 0, keyframeIndex = 0;
	float clipTime = 0.0, keyframeTime = 0.0;
	float clipParam = 0.0, keyframeParam = 0.0;

	std::vector<Clip const*> clips;
	Clip const* clip;
	Keyframe const* keyframe;
};

void clipCtrlInit(clipCtrl* ctrl, std::string name, int clipIndex, std::vector<Clip const*> clips);
int a3clipControllerUpdate(clipCtrl* ctrl, float dt);
