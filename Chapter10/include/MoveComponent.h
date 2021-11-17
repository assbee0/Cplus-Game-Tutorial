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

		//! 设置移动方向并判断是否移动
		void	SetDir(const Vector2& dir);
		//! 设置地图数据
		void	SetMap(int* map);

	private:
		//! 处理移动过程中每帧的更新
		void	ProcessMoving();
		//! 检测与地图上墙的碰撞
		bool	WallCheck(const Vector2& dst);
		//! 处理到达一个格子后的各种操作
		void	ReachOneGrid();

		float	mSpeed;			//!<	移动速度
		Vector2	mDir;			//!<	移动方向
		Vector2 mDst;			//!<	移动目的地
		bool	mIsMoving;		//!<	是否在运动中
		float	mPixelsCount;	//!<	已走过的像素数

		int*	mMapArray;		//!<	地图数组
	};
}

#endif	// __Dungeon_MoveComponent__