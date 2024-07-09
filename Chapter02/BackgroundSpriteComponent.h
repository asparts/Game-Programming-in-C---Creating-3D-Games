#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "SpriteComponent.h"
class BackgroundComponent : public SpriteComponent
{
public:
	//Set draw order to default to lower
	BackgroundComponent(class Actor* owner, int draworder = 10);
	//update/draw overriden from parent
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	//Set the textures used for the background
	void SetBackgroundTextures(const std::vector<SDL_Texture*>& textures);
	//Get/set screen size and scroll speed
	void SetScreenSize(const Vector2& size){ mScreenSize = size; }
	void SetScrollSpeed(float speed){ mScrollSpeed = speed; }
	float GetScrollSpeed() const { return mScrollSpeed; }
private:
	//struct to encapsulate each background image to its offset
	struct BackgroundTexture
	{
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};
	std::vector<BackgroundTexture> mBackgroundTextures;
	Vector2 mScreenSize;
	float mScrollSpeed;
};

