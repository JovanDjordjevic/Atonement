#include "animation.h"

#include "core/graphics/animations.h"

void dagger::AnimatorPlayOnce(Animator& animator_, String animationName_)
{
	if (animationName_ == animator_.currentAnimation) return;

	animator_.isLooping = false;
	animator_.currentAnimation = animationName_;
	animator_.currentFrame = 0;
	animator_.currentFrameTime = 0;
	animator_.animationPlaying = true;
}

void dagger::AnimatorPlay(Animator& animator_, String animationName_)
{
	if (animationName_ == animator_.currentAnimation) return;

	animator_.isLooping = true;
	animator_.currentAnimation = animationName_;
	animator_.currentFrame = 0;
	animator_.currentFrameTime = 0;
	animator_.animationPlaying = true;
}

void dagger::AnimatorStop(Animator& animator_)
{
	animator_.animationPlaying = false;
}
