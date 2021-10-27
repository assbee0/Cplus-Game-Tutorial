//! @file MoveComponent.h

#ifndef __Dungeon_MoveComponent__
#define __Dungeon_MoveComponent__

#include	<Component.h>

namespace Dungeon
{
	class GameObject;

	class MoveComponent : public Component
	{
	public:
		//! 构造函数
		MoveComponent(GameObject* gameObject);

		//! 每帧更新（重写）
		void	Update() override;
	};
}

#endif	// __Dungeon_MoveComponent__