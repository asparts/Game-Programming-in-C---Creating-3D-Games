#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder) 
	:Component(owner), mTexture(nullptr), mDrawOrder(drawOrder), mTextureWidth(0), mTextureHeight(0)
{
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_Rect sdl_rect;
		//scale the width/height by owner's scale
		sdl_rect.w = static_cast<int>(mTextureWidth * mOwner->GetScale());
		sdl_rect.h = static_cast<int>(mTextureHeight * mOwner->GetScale());
		//center the rectange around the position of the owner
		sdl_rect.x = static_cast<int>(mOwner->GetPosition().x - sdl_rect.w / 2);
		sdl_rect.x = static_cast<int>(mOwner->GetPosition().y - sdl_rect.h / 2);

		//Draw
		SDL_RenderCopyEx(renderer,
			mTexture, //texture to draw 
			nullptr,  //source rectangle
			&sdl_rect, //destination rectangle
			-Math::ToDegrees(mOwner->GetRotation()), //Convert angle
			nullptr, //point of rotation
			SDL_FLIP_NONE //flip begavior
		);
		
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	//Get width/hight of texture
	SDL_QueryTexture(texture, nullptr, nullptr, &mTextureWidth, &mTextureHeight);
}
