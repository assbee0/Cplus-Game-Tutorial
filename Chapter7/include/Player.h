//! @file Player.h

#ifndef __Dungeon_Player__
#define __Dungeon_Player__

#include	<GameObject.h>

namespace Dungeon
{
	class Player : public GameObject
	{
	public:
		//! 构造函数
		Player(class Game* game);
	};
}

#endif	// __Dungeon_Player__