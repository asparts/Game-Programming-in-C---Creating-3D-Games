#pragma once
#include "Actor.h"
class Component
{

public:

	//constructor

	//the lower the update order, the earlier the component is updated

	Component(class Actor* owner, int updateOrder = 100);
	//desctructor
	virtual ~Component();

	//Update this component by deltatime
	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }

protected:
	//owning actor
	class Actor* mOwner;
	//Update order of this component
	int mUpdateOrder;
};

