#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "SpriteComponent.h"
class AnimatedSpriteComponent : SpriteComponent
{
public:
	AnimatedSpriteComponent(class Actor* owner, int drawOrder = 100);
	//Update animation every frame (overriden from component)
	void Update(float deltaTime) override;
	//Set the textures used for animation
	void SetAnimationTextures(const std::vector<SDL_Texture*>& textures);
	//Set and get the animation FPS
	float GetAnimationFPS() const { return mAnimationFPS; }
	float SetAnimationFPS(float fps){ this->mAnimationFPS = fps; }

private:
	//All textures in the animation
	std::vector<SDL_Texture*> mAnimationTextures;
	//Current frame displayed
	float mCurrentFrame;
	//Animation frame rate. Allows different animated sprites to run at different frame rates.
	float mAnimationFPS;
};

