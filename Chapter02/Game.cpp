#include "Game.h"

void Game::AddActor(Actor* actor)
{

	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}

}

void Game::AddSprite(SpriteComponent* sprite)
{
	//Find the insertoin point in the sorted vector
	//the first element with a higher draw order than me
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
			break;
	}

	//Inserts element before position of the iterator
	mSprites.insert(iter, sprite);
}

void Game::Initialize()
{
	IMG_Init(IMG_INIT_PNG);



	//Loads an image from a file
	//returns a pointer to an SDL_Surface if successfull, otherwise nullptr
	SDL_Surface* IMG_Load(
		const char* file //img file name
	);

	//Converts an SDL_surface to an SDL_Texture (which SDL requires for drawing)
	//returns a pointer to an SDL_texture if successfull, otherwise nullptr

	SDL_Texture* SDL_CreateTextureFromSurface(
		SDL_Renderer * renderer,
		SDL_Surface * surface
	);
}

void Game::RemoveActor(Actor* actor)
{
	int found = 0;
	if (found < count(mPendingActors.begin(), mPendingActors.end(), actor))
		mPendingActors.erase(std::remove(mPendingActors.begin(), mPendingActors.end(), actor), mPendingActors.end());
	else if (found < count(mActors.begin(), mActors.end(), actor))
		mActors.erase(std::remove(mActors.begin(), mActors.end(), actor), mActors.end());

}

SDL_Texture* Game::LoadTexture(const char* fileName)
{
	//Load from file
	SDL_Surface* surface = IMG_Load(fileName);

	if (!surface)
	{
		SDL_Log("Failed to load texture %s", fileName);
		return nullptr;
	}

	//Create texture from surface
	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
	SDL_FreeSurface(surface);
	if (!texture)
	{
		SDL_Log("Failed to convert surface to texture for %s", fileName);
		return nullptr;
	}
	return texture;
}

void Game::UpdateGame()
{
	//compute delta time 
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	//update tick counts (for next frame
	mTicksCount = SDL_GetTicks();

	//Update all actors
	mUpdatingActors = true;

	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	//Move any pending actors to mActors
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	//Add any dead actors to temp vector

	std::vector<Actor*> deadActors;

	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::Dead)
		{
			deadActors.emplace_back(actor);
		}
	}
	//Delete dead actors
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::ShutDown()
{

	//Because Actor calls RemoveActor and can remove itself from the game, be sure that actors is empty etc.
	while (!mActors.empty())
	{
		delete mActors.back();
	}
}
