//! @file Component.cpp

#include	<Component.h>
#include	<GameObject.h>

namespace Dungeon
{
	Component::Component(GameObject* gameObject) :
		mGameObject(gameObject),
		mUpdateOrder(100)
	{
		mGameObject->AddComponent(this);
	}

	Component::~Component()
	{
		mGameObject->RemoveComponent(this);
	}

	void Component::ProcessInput(const uint8_t* state)
	{
	}

	void Component::Update()
	{
	}

	int Component::GetUpdateOrder() const
	{
		return mUpdateOrder;
	}

	void Component::SetUpdateOrder(int order)
	{
		mUpdateOrder = order;
	}

	GameObject* Component::GetGameObject()
	{
		return mGameObject;
	}
}