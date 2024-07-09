#pragma once

#include <SDL.h>
#include <vector>
/// <summary>
/// an object in the game (trees, NPCs, buildings, etc. A similar term is "entity".)
/// </summary>
class Actor
{
public:

	//used to track state of actor

	enum State
	{
		Active,
		Paused,
		Dead
	};

	//constructor/destructor
	Actor(class Game* game);
	virtual ~Actor();

	//Update fucntion calles from Game (not overridable)

	void Update(float deltaTime);

	//Updates all the components attached to the actor

	void UpdateComponents(float deltaTime);

	//Any actor-specific update code (overridable)

	virtual void UpdateActor(float deltaTime);

	//Getters and setters

	State GetState() { return this->mState; }
	State SetState(State state) { this->mState = state; }
	const Vector2& GetPosition() const { return mPosition; }

	//Add/remove components

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	
	/*struct Vector2
	{
		float x;
		float y;
	};*/

	//Actors state
	State mState;

	//Transform
	Vector2 mPosition; //Center position of actor

	float mScale; //Uniforms scale of actor

	float mRotation; //Rotation angle in radians

	//Components held by this actor

	std::vector<class Component*> mComponents;

	class Game* game;

};

