#pragma once
#include <string>
#include <vector>
#include "keyframe.h"
#include "hierarchyObj.h"

struct clipCtrl
{
	std::string name;
	int clipIndex, keyframeIndex;
	float clipTime, keyframeTime;
	float clipParam, keyframeParam;

	std::vector<Clip const*> clips;
	Clip const* clip;
	Keyframe const* keyframe;
};

void clipCtrlInit(clipCtrl* ctrl, std::string name, int clipIndex, std::vector<Clip const*> clips);
