#include "clipCtrl.h"

void clipCtrlInit(clipCtrl* ctrl, std::string name, std::vector<std::string> clipNames, float frameDuration, int keyFrameCount, int clipCount)
{
	ctrl->name = name;

	ctrl->keyframeIndex = 0;
	ctrl->keyframeTime = 0.0;
	ctrl->keyframeParam = 0.0;

	ctrl->clipIndex = 0;
	ctrl->clipTime = 0.0;
	ctrl->clipTime = 0.0;

	//holds current keyframe
	ctrl->keyframe = new Keyframe;
	ctrl->keyframe->index = 0;
	ctrl->keyframe->duration = frameDuration;

	//creates a new clip 
	for (int i = 0; i < clipCount; i++)
	{
		ctrl->clip = new Clip;
		
		ctrl->clip->name = clipNames[i];
		ctrl->clip->duration = keyFrameCount * frameDuration;

		ctrl->clips.push_back(ctrl->clip);

		//creates new keyframes per clip
		for (int j = 0; j < keyFrameCount; j++)
		{
			Keyframe* frame = new Keyframe;
			frame->index = j;
			frame->duration = frameDuration;
			addKeyframeToClip(ctrl->clips[i], frame);
		}
	}
}

//clean up memory
void clipCtrlCleanUp(clipCtrl* ctrl)
{
	for (int j = 0; j < ctrl->clips.size(); j++)
	{
		for (int i = 0; i < ctrl->clips[j]->keyframes.size(); i++)
		{
			delete  ctrl->clips[j]->keyframes[i];
		}
		delete ctrl->clips[j];
	}
	
}

int clipControllerUpdate(clipCtrl* ctrl, float dt)
{
	if (ctrl)
	{
		float overstep;
		ctrl->clipTime += dt;
		ctrl->keyframeTime += dt;

		// resolve forward
		while ((overstep = ctrl->keyframeTime - ctrl->keyframe->duration) >= 0.0)
		{
			// are we passing the forward terminus of the clip
			if (ctrl->keyframeIndex == ctrl->clip->keyframes.size() - 1)
			{
				// handle forward transition
				ctrl->keyframeIndex = 0;
				ctrl->keyframe = ctrl->clips[ctrl->clipIndex]->keyframes[ctrl->keyframeIndex];
				ctrl->keyframeTime = overstep;
			}
			else
			{
				// set keyframe indices
				ctrl->keyframeIndex += 1;


				// set keyframe pointers
				ctrl->keyframe = ctrl->clips[ctrl->clipIndex]->keyframes[ctrl->keyframeIndex];

				// new time is just the overstep
				ctrl->keyframeTime = overstep;
			}
		}

		// resolve reverse
		while ((overstep = ctrl->keyframeTime) < 0.0)
		{
			if (ctrl->keyframeIndex == 0)
			{
				ctrl->keyframeIndex = ctrl->clip->keyframes.size() - 1;
				ctrl->keyframe = ctrl->clips[ctrl->clipIndex]->keyframes[ctrl->keyframeIndex];
				ctrl->keyframeTime = overstep + ctrl->keyframe->duration;
			}
			else
			{
				ctrl->keyframeIndex -= 1;

				// set keyframe pointers
				ctrl->keyframe = ctrl->clips[ctrl->clipIndex]->keyframes[ctrl->keyframeIndex];

				// new time is overstep (negative) from new duration
				ctrl->keyframeTime = overstep + ctrl->keyframe->duration;
			}
		}

		// normalize
		ctrl->keyframeParam = ctrl->keyframeTime * (1 / ctrl->keyframe->duration);
		ctrl->clipParam = ctrl->clipTime * (1 / ctrl->clip->duration);

		// done
		return 1;
	}
	return -1;
}


