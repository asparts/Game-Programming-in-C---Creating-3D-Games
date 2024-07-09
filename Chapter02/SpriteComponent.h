#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Component.h"
#include "Math.h"
class SpriteComponent : public Component
{
public:

	//lower draw order correstponds fith further back
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();
	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTextureHeight() const { return mTextureHeight; }
	int GetTextureWidth() const { return mTextureWidth; }

protected:
	//Texture to draw
	SDL_Texture* mTexture;
	//Draw order used for a painter's algorithm
	int mDrawOrder;
	//Width and height of texture
	int mTextureWidth;
	int mTextureHeight;

};

