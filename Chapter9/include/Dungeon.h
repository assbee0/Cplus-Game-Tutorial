//! @file Dungeon.h

#ifndef __Dungeon_Dungeon__
#define __Dungeon_Dungeon__

#include	<GameObject.h>

namespace Dungeon
{
	class Dungeon : public GameObject
	{
	public:
		//! 构造函数
		Dungeon(class Game* game);
	};
}

#endif	// __Dungeon_Dungeon__