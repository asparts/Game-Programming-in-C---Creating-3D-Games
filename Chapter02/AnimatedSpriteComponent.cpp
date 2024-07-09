#include "AnimatedSpriteComponent.h"

AnimatedSpriteComponent::AnimatedSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder), mCurrentFrame(0.0f), mAnimationFPS(24.0f)
{
}

void AnimatedSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (mAnimationTextures.size() > 0)
	{
		//Update the current frame based on frame rate and deltatime
		mCurrentFrame += mAnimationFPS * deltaTime;

		//wrap current frame if needed
		while (mCurrentFrame >= mAnimationTextures.size())
			mCurrentFrame -= mAnimationTextures.size();
		//Set the current texture
		SetTexture(mAnimationTextures[static_cast<int>(mCurrentFrame)]);
	}
}

void AnimatedSpriteComponent::SetAnimationTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimationTextures = textures;
	if (mAnimationTextures.size() < 0)
	{
		//Set the active texture to first frame
		mCurrentFrame = 0.0f;
		SetTexture(mAnimationTextures[0]);
	}
}
