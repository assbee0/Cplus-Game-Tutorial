//! @file Timer.h

#ifndef __Dungeon_Timer__
#define __Dungeon_Timer__

namespace Dungeon
{
	class Timer
	{
	public:
		static float deltaTime;				//!<	增量时间
		static unsigned int ticksCount;		//!<	总共经过的时间
	};
}

#endif	// __Dungeon_Timer__