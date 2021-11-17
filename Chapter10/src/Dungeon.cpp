//! @file Dungeon.cpp

#include	<Dungeon.h>
#include	<MapComponent.h>
#include	<Game.h>

namespace Dungeon
{
	Dungeon::Dungeon(Game* game):
		GameObject(game)
	{
		MapComponent* mapComponent = new MapComponent(this);
		mapComponent->SetTexture(game->GetTexture("ground"), 0);
		mapComponent->SetTexture(game->GetTexture("wall"), 1);
	}
}