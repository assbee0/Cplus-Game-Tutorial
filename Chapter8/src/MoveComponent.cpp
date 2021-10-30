//! @file MoveComponent.cpp

#include	<GameObject.h>
#include	<MoveComponent.h>
#include	<Timer.h>

namespace Dungeon
{
	MoveComponent::MoveComponent(GameObject* gameObject):
		Component(gameObject),
		mSpeed(100),
		mDir(Vector2::Zero)
	{
	}

	void MoveComponent::Update()
	{
		Vector2 curPos = mGameObject->GetPosition();
		Vector2 newPos = curPos + mDir * mSpeed * Timer::deltaTime;
		mGameObject->SetPosition(newPos);
	}

	void MoveComponent::SetDir(const Vector2& dir)
	{
		mDir = dir;
	}
}