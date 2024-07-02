#include "game.h"

Game::Game()
{
	mWindow = nullptr;
	mIsRunning = true;

	mPaddlePos.x = 50;
	mPaddlePos.y = 768/2;

	mBallPos.x = 1024/2;
	mBallPos.y = 768/2;

	//init ball velocity
	mBallVel.y = -200.0f;
	mBallVel.x = 235.0f;

	paddleH = 100.0f;

}

bool Game::Initialize()
{
	//initializing sdl library.
	int sdlResult = SDL_Init(SDL_INIT_VIDEO); 

	//nonzero is failed
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL : %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game Programming in C++ (Chapter 1)", //title
		100, //top left x-coordinate,
		100, //top left y-coordinate,
		1024, //width
		768, //height
		0 //flags (0 for n o flags set)
	);

	if (!mWindow)
	{
		SDL_Log("Unable to initialize window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{

	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);

	SDL_Quit();
}

void Game::ProcessInput()
{
	SDL_Event event;

	//while there are still events in the queue
	while (SDL_PollEvent(&event))
	{
		//handling different event types via switch-case
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}

	//Get state of keyboard

	const Uint8* state = SDL_GetKeyboardState(NULL);

	//if escape is pressed, end game loop
	if (state[SDL_SCANCODE_ESCAPE])
		mIsRunning = false;


	//Paddle directions
	mPaddleDir = 0;

	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}
}

void Game::UpdateGame()
{
	//Frame limiting: ensuring that atleast 16ms elapses between frames
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	// deltatime is the difference in ticks from last frame (converted to seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	//clamp maximum delta time value so simulation doesn't run too fast while paused (for example in debugging with breakpoints)
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	//update tick counts (for next frame
	mTicksCount = SDL_GetTicks();

	//TODO: Update objects in game world as function of delta time

	// update the y position of the paddle based on
	// the paddle direction, a speed of 300.0f pixels / second
	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;

		//making sure paddle doesnt move off screen
		if (mPaddlePos.y < (paddleH / 2.0f + thickness))
		{
			mPaddlePos.y = (paddleH / 2.0f + thickness);
		}
		else if (mPaddlePos.y > (768.0f*2 - paddleH - thickness))
		{
			mPaddlePos.y = (768.0f * 2 - paddleH - thickness);
		}
	}

	//update ball position
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;



	//ball collisions

	//if moving up and colliding with top wall
	if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1;
	}
	//if moving down and colliding with bot wall
	else if (mBallPos.y >= 768 - thickness && mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
	}
	//right wall
	else if (mBallPos.x >= 1024 - thickness && mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1;
	}

	float diff = mBallPos.y - mPaddlePos.y;
	if (diff <= paddleH / 2.0f && mBallPos.x <= 75.0f && mBallPos.x >= 20.0f && mBallVel.x < 0.0f)
	{
		mBallVel.x *= -1.0f;
	}
}

void Game::GenerateOutput()
{
	//draw color (for background)
	SDL_SetRenderDrawColor(mRenderer,0, 0, 255, 255);
	//clear buffer
	SDL_RenderClear(mRenderer);
	
	//change draw color
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	
	//draw ball
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);
	
	//draw paddle
	SDL_Rect mPaddle{
		mPaddlePos.x,mPaddlePos.y / 2,thickness,paddleH
	};
	SDL_RenderFillRect(mRenderer, &mPaddle);

	//draw top wall
	SDL_Rect wall{
		0,0,1024,thickness
	};
	SDL_RenderFillRect(mRenderer, &wall);

	//draw bot wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	//draw right wall
	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 1024;
	SDL_RenderFillRect(mRenderer, &wall);

	//swap colorbuffers
	SDL_RenderPresent(mRenderer);
}
//109