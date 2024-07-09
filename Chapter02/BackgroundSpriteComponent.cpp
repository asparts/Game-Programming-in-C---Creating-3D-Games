#include "BackgroundSpriteComponent.h"

BackgroundComponent::BackgroundComponent(Actor* owner, int draworder)
{
}
/// <summary>
///updates the offsets of
///each background, taking to account when one image
///moves all the way off the screen.This allows the images
///to infinitely repeat
/// </summary>
/// <param name="deltaTime"></param>
void BackgroundComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	for (auto& bg : mBackgroundTextures)
	{
		//Update the x offset
		bg.mOffset.x += mScrollSpeed * deltaTime;

		//if this is compelety off the screen, reset offset to the right of the last background texture
		if (bg.mOffset.x < -mScreenSize.x)
			bg.mOffset.x = (mBackgroundTextures.size() - 1) * mScreenSize.x - 1;
	}
}
/// <summary>
/// Draw function simply draws each background
/// texture using SDL_RenderCopy, making sure to adjust
/// the position based on the owner’s position and the offset
/// of that background.This achieves the simple scrolling
/// behavior.
/// </summary>
/// <param name="renderer"></param>
void BackgroundComponent::Draw(SDL_Renderer* renderer)
{
	// Draw each background texture
	for (auto& bg : mBackgroundTextures)
	{
		SDL_Rect r;
		// Assume screen size dimensions
		r.w = static_cast<int>(mScreenSize.x);
		r.h = static_cast<int>(mScreenSize.y);
		// Center the rectangle around the position of the owner
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2 + bg.mOffset.x);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2 + bg.mOffset.y);

		// Draw this background
		SDL_RenderCopy(renderer,
			bg.mTexture,
			nullptr,
			&r
		);
	}
}

void BackgroundComponent::SetBackgroundTextures(const std::vector<SDL_Texture*>& textures)
{
	/**
	The BackgroundTexture struct associates each background
	texture with its corresponding offset. The offsets update
	every frame to create the scrolling effect. So we need to
	initialize the offsets in SetBackgroundTextures, positioning
	each background to the right of the previous one
	*/
	int count = 0;

	for (auto texture : textures)
	{
		BackgroundTexture tempBackroundTexture;

		tempBackroundTexture.mTexture = texture;

		//Each texture is  screen width in offset

		tempBackroundTexture.mOffset.x = count * mScreenSize.x;

		tempBackroundTexture.mOffset.y = 0;

		mBackgroundTextures.emplace_back(tempBackroundTexture);

		count++;
	}
}
