#pragma once
#include <string>
#include "keyframe.h"

struct clipCtrl
{
	std::string name;
	int clipIndex, keyframeIndex;
	float clipTime, keyframeTime;
	float clipParam, keyframeParam;

	Clip const* clip;
	Keyframe const* keyframe;
};

int clipCtrlInit(clipCtrl* ctrl, std::string name, Clip* currentClip);
