#include "Component.h"

Component::Component(Actor* owner, int updateOrder)
{
	this->mOwner = owner;
	this->mUpdateOrder = updateOrder;
}

Component::~Component()
{
}

void Component::Update(float deltaTime)
{
}
