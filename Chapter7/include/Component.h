//! @file Component.h

#ifndef __Dungeon_Component__
#define __Dungeon_Component__

#include	<string>
#include	<vector>

namespace Dungeon
{
	class Component
	{
	public:
		//! 构造函数
		Component(class GameObject* gameObject);
		//! 析构函数
		virtual ~Component();

		//! 每帧更新
		virtual void		Update();

		//! 更新顺序的get和set
		int					GetUpdateOrder() const;
		void				SetUpdateOrder(int order);
		//! 游戏物体的get
		class GameObject*	GetGameObject();

	protected:
		class GameObject*	mGameObject;		//!<	自身附着的游戏物体
		int					mUpdateOrder;		//!<	更新顺序
	};
}

#endif	// __Dungeon_Component__