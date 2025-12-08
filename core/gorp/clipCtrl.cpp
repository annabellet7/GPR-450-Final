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

	ctrl->keyframe = new Keyframe;
	ctrl->keyframe->index = 0;
	ctrl->keyframe->duration = frameDuration;


	for (int i = 0; i < clipCount; i++)
	{
		ctrl->clip = new Clip;
		
		ctrl->clip->name = clipNames[i];
		ctrl->clip->duration = keyFrameCount * frameDuration;

		ctrl->clips.push_back(ctrl->clip);


		for (int j = 0; j < keyFrameCount; j++)
		{
			Keyframe* frame = new Keyframe;
			frame->index = j;
			frame->duration = frameDuration;
			addKeyframeToClip(ctrl->clips[i], frame);
		}
	}
}

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
	if (ctrl /*&& clipCtrl->clipPool*/)
	{
		//-----------------------------------------------------------------------------
		//****TO-DO-ANIM-PROJECT-1: IMPLEMENT ME
		//-----------------------------------------------------------------------------

				// variables
		float overstep;

		// time step
		//dt *= ctrl->playback_sec;
		ctrl->clipTime += dt;
		ctrl->keyframeTime += dt;
		//dt *= clipCtrl->playback_stepPerSec;
		//clipCtrl->clipTime_step += (a3i32)dt;
		//clipCtrl->keyframeTime_step += (a3i32)dt;

		// resolve forward
		while ((overstep = ctrl->keyframeTime - ctrl->keyframe->duration) >= 0.0)
		{
			// are we passing the forward terminus of the clip
			if (ctrl->keyframeIndex == ctrl->clip->keyframes.size() - 1/*ctrl->clip->keyframeIndex_final*/)
			{
				// handle forward transition

				// default testing behavior: loop with overstep
				ctrl->keyframeIndex = 0 /*ctrl->clip->keyframeIndex_first*/;
				ctrl->keyframe = ctrl->clips[ctrl->clipIndex]->keyframes[ctrl->keyframeIndex];
				//ctrl->keyframe = ctrl->clipPool->keyframe + ctrl->keyframeIndex;
				ctrl->keyframeTime = overstep;
			}
			// are we simply moving to the next keyframe
			else
			{
				// set keyframe indices
				ctrl->keyframeIndex += 1;


				// set keyframe pointers
				ctrl->keyframe = ctrl->clips[ctrl->clipIndex]->keyframes[ctrl->keyframeIndex];
				//ctrl->keyframe = ctrl->clipPool->keyframe + ctrl->keyframeIndex;

				// new time is just the overstep
				ctrl->keyframeTime = overstep;
			}
		}

		// resolve reverse
		while ((overstep = ctrl->keyframeTime) < 0.0)
		{
			// are we passing the reverse terminus of the clip
			if (ctrl->keyframeIndex == 0)
			{
				// handle reverse transition

				// default testing behavior: loop with overstep
				ctrl->keyframeIndex = ctrl->clip->keyframes.size() - 1;
				ctrl->keyframe = ctrl->clips[ctrl->clipIndex]->keyframes[ctrl->keyframeIndex];
				ctrl->keyframeTime = overstep + ctrl->keyframe->duration;
			}
			// are we simply moving to the previous keyframe
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

		//-----------------------------------------------------------------------------
		//****END-TO-DO-PROJECT-1
		//-----------------------------------------------------------------------------
	}
	return -1;
}


