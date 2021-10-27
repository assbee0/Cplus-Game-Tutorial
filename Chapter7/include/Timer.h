//! @file Timer.h

#ifndef __Dungeon_Timer__
#define __Dungeon_Timer__

namespace Dungeon
{
	class Timer
	{
	public:
		// 增量时间
		static float deltaTime;
		// 总共经过的时间
		static unsigned int ticksCount;
	};
}

#endif	// __Dungeon_Timer__