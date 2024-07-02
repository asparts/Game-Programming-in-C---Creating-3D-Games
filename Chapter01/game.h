#pragma once

#include <SDL.h>

class Game
{
public:
	Game();

	//Initialize the game
	bool Initialize();

	//runs the game loop until the game is over

	void RunLoop();

	//shutdown the game

	void Shutdown();

private:

	struct Vector2
	{
		float x;
		float y;
	};
	Vector2 mPaddlePos;
	Vector2 mPaddle2Pos;
	Vector2 mBallPos;
	Vector2 mBallVel;
	int thickness = 15;
	Uint32 mTicksCount;

	//paddle direction
	int mPaddleDir;
	int mPaddle2Dir;

	//paddle height
	int paddleH;

	//Game should continue to run
	bool mIsRunning;
	//window created by sdl
	SDL_Window* mWindow;

	//renderer
	SDL_Renderer* mRenderer;
	

	//game loop helper functions

	void ProcessInput();

	void UpdateGame();

	void GenerateOutput();


	

	
	
};