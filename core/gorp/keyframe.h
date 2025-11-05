#pragma once
#include <string>
#include <vector>

struct Keyframe
{
	int index;
	float duration;
};

typedef enum ClipTransitionFlag
{
	stopFlag,		// stop flag (no change)
	clip_playFlag,		// play after transition
	clip_reverseFlag,	// direction is reverse after transition
} ClipTransitionFlag;

struct ClipTransition
{
	ClipTransitionFlag flag;
	int clipIndex;
};

struct Clip
{
	std::string name;
	float duration;
	std::vector <Keyframe*> keyframes;

	ClipTransition transitionForward[1], transitionReverse[1];
};

int keyframeInit(Keyframe* keyframe, int index, float duration);
void deleteKeyframe(Keyframe* keyframe);
int clipTransitionInit(ClipTransition* transition, ClipTransitionFlag const flag, Clip const* clip);
int clipInit(Clip* clip, std::string const name, std::vector <Keyframe*> keyframes);
void deleteClip(Clip* clip);
int addKeyframeToClip(Clip* clip, Keyframe* keyframe);
