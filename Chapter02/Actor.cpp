#include "Actor.h"

Actor::Actor(Game* game)
{
	this->game = game;
}

Actor::~Actor()
{
}

void Actor::Update(float deltaTime)
{
}

void Actor::UpdateComponents(float deltaTime)
{
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::AddComponent(Component* component)
{
}

void Actor::RemoveComponent(Component* component)
{
}
