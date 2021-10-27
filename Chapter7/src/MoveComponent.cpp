//! @file MoveComponent.cpp

#include	<MoveComponent.h>
#include	<GameObject.h>
#include	<Timer.h>

namespace Dungeon
{
	MoveComponent::MoveComponent(GameObject* gameObject):
		Component(gameObject)
	{
	}

	void MoveComponent::Update()
	{
		Vector2 curPos = mGameObject->GetPosition();
		mGameObject->SetPosition(curPos + Vector2::X /*方向*/ * 50 /*速度*/ * Timer::deltaTime /*增量时间*/);
	}
}