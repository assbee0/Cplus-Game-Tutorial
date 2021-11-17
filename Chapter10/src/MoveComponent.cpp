//! @file MoveComponent.cpp

#include	<GameObject.h>
#include	<MoveComponent.h>
#include	<Timer.h>

namespace Dungeon
{
	MoveComponent::MoveComponent(GameObject* gameObject):
		Component(gameObject),
		mSpeed(150),
		mDir(Vector2::Zero),
		mDst(Vector2::Zero),
		mIsMoving(false),
		mPixelsCount(0),
		mMapArray(nullptr)
	{
	}

	void MoveComponent::Update()
	{
		if(mIsMoving)
		{
			ProcessMoving();
		}
	}

	void MoveComponent::SetDir(const Vector2& dir)
	{
		// 角色处于移动状态中时跳过本函数
		if (mIsMoving)
		{
			return;
		}

		mDir = dir;
		Vector2 curPos = mGameObject->GetPosition();
		// 计算临时的目的地
		Vector2 tempDst = curPos + mDir * 32;
		// 检测该目的地是否可以移动
		if (WallCheck(tempDst))
		{
			// 使角色进入移动状态
			mIsMoving = true;
			mDst = tempDst;
		}
	}

	void MoveComponent::SetMap(int* map)
	{
		mMapArray = map;
	}

	void MoveComponent::ProcessMoving()
	{
		Vector2 curPos = mGameObject->GetPosition();

		// 实际速度要乘上增量时间
		float realSpeed = mSpeed * Timer::deltaTime;
		// 计算出移动中的临时位置
		Vector2 tempPos = curPos + mDir * realSpeed;

		// 已经走过的像素数加上这帧即将走过的像素数
		mPixelsCount += realSpeed;
		// 还未走完一整格
		if (mPixelsCount < 32)
		{
			mGameObject->SetPosition(tempPos);
		}
		// 走完一整格 抵达目的地
		else
		{
			ReachOneGrid();
		}
	}

	bool MoveComponent::WallCheck(const Vector2& dst)
	{
		// 将像素坐标转换成格子坐标
		int gridX = static_cast<int>(dst.x / 32);
		int gridY = static_cast<int>(dst.y / 32);

		// 地图数组内元素的值为1时说明不可通行
		if (mMapArray[gridY * 20 + gridX] == 1)
		{
			return false;
		}
		return true;
	}

	void MoveComponent::ReachOneGrid()
	{
		// 重置各种状态
		mIsMoving = false;
		mPixelsCount = 0;
		mDir = Vector2::Zero;

		// 将目的地设置为当前位置
		mGameObject->SetPosition(mDst);
	}
}