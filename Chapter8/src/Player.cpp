//! @file Player.h

#include	<Player.h>
#include	<SpriteComponent.h>
#include	<MoveComponent.h>
#include	<InputComponent.h>
#include	<Game.h>

namespace Dungeon
{
	Player::Player(Game* game):
		GameObject(game)
	{
		SpriteComponent* sprite = new SpriteComponent(this, 100);
		sprite->SetTexture(GetGame()->GetTexture("player"));
		SetPosition(Vector2(288, 240));
		MoveComponent* moveComponent = new MoveComponent(this);
		InputComponent* inputComponent = new InputComponent(this);
	}
}