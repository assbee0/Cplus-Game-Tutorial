//! @file InputComponent.cpp

#include	<InputComponent.h>
#include	<MoveComponent.h>
#include	<GameObject.h>
#include	<SDL/SDL_scancode.h>

namespace Dungeon
{
	InputComponent::InputComponent(GameObject* gameObject) :
		Component(gameObject)
	{
	}

	void InputComponent::ProcessInput(const uint8_t* state)
	{
		MoveComponent* mc = mGameObject->GetComponent<MoveComponent>();
		if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
		{
			mc->SetDir(Vector2::NY);
		}
		else if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
		{
			mc->SetDir(Vector2::Y);
		}
		else if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT])
		{
			mc->SetDir(Vector2::NX);
		}
		else if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])
		{
			mc->SetDir(Vector2::X);
		}
		else
		{
			mc->SetDir(Vector2::Zero);
		}
	}

}