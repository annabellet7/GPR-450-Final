#pragma once
#include <string>
#include "keyframe.h"

struct clipCtrl
{
	std::string name;
	int clipIndex, keyframeIndex;
	float clipTime, keyframeTime;
	float clipParam, keyframeParam;

	ClipPool const* clipPool;
	Clip const* clip;
	Keyframe const* keyframe;
};

