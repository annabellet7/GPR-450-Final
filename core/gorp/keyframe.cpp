#include "keyframe.h"

int keyframeInit(Keyframe* keyframe, int index, float duration)
{
	if(!keyframe)
		keyframe = new Keyframe;

	keyframe->index = index;
	keyframe->duration = duration; //1/framerate
	return keyframe->index;
}

void deleteKeyframe(Keyframe* keyframe)
{
	if(keyframe)
		delete keyframe;
}

int clipTransitionInit(ClipTransition* transition, ClipTransitionFlag const flag, Clip const* clip)
{
	if (!transition)
	{
		transition = new ClipTransition;
	}
	transition->flag = flag;
	return flag;
}

void clipInit(Clip* clip, std::string const name, std::vector <Keyframe*> keyframes, int keyframeLength)
{
	if (!clip)
	{
		clip = new Clip;
	}
	clip->name = name;
	for (int i = 0; i < keyframeLength; i++)
	{
		clip->keyframes.push_back(keyframes[i]);
	}
	
}

void deleteClip(Clip* clip)
{
	if (clip)
	{
		for (int i = 0; i < clip->keyframes.size(); i++)
		{
			deleteKeyframe(clip->keyframes[i]);
		}
		delete clip;
	}
}

void addKeyframeToClip(Clip* clip, Keyframe* keyframe)
{
	clip->keyframes.push_back(keyframe);
 }