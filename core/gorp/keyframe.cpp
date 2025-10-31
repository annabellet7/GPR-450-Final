#include "keyframe.h"

int keyframeInit(Keyframe* keyframe, int index, float duration)
{
	if(!keyframe)
		return -1;

	keyframe->index = index;
	keyframe->duration = duration; //1/framerate
	return keyframe->index;
}

int clipPoolCreate(ClipPool* clipPool, int const clipCount, int const keyframeCount)
{
	if (!clipPool && clipPool->clip && !clipCount && !keyframeCount)
		return -1;
	
	if(!clipPool->clip)
		clipPool->clip = new Clip;




	return 0;
}

int clipPoolRelease(ClipPool* clipPool)
{
	return 0;
}

int clipTransitionInit(ClipTransition* transition, ClipTransitionFlag const flag, Clip const* clip)
{
	return 0;
}

int clipInit(Clip* clip, std::string const name, Keyframe const* keyframeFirst, Keyframe const* keyframeLast)
{
	return 0;
}

int a3clipGetIndexInPool(ClipPool const* clipPool, std::string name)
{
	return 0;
}

int a3clipCalculateDuration(ClipPool const* clipPool, int const clipIndex, int const fps)
{
	return 0;
}
