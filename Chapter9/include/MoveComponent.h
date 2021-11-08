//! @file MoveComponent.h

#ifndef __Dungeon_MoveComponent__
#define __Dungeon_MoveComponent__

#include	<Component.h>
#include	<Math/Math.h>

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

		//! 移动方向的set
		void	SetDir(const Vector2& dir);

	private:
		float	mSpeed;		//!<	移动速度
		Vector2	mDir;		//!<	移动方向
	};
}

#endif	// __Dungeon_MoveComponent__