#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Actor.h"
#include "SpriteComponent.h"
class Game
{
public:

	std::vector<Actor*> mActors;
	std::vector<Actor*> mPendingActors;
	std::vector<SpriteComponent*> mSprites;
	bool mUpdatingActors = false;
	Uint32 mTicksCount;
	SDL_Renderer* mRenderer;

	void AddActor(Actor* actor);
	void AddSprite(SpriteComponent* sprite);
	void Initialize();
	SDL_Texture* LoadTexture(const char* fileName);
	void RemoveActor(Actor* actor);
	void UpdateGame();
	void ShutDown();

private:

};

