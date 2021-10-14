//! @file GameObject.h

#ifndef __Dungeon_GameObject__
#define __Dungeon_GameObject__

#include	<string>
#include	<vector>

namespace Dungeon
{
	class GameObject
	{
	public:
		//! 物体状态
		enum class State
		{
			EActive,
			EDead
		};

		//! 构造函数
		GameObject(class Game* game);
		//! 析构函数
		virtual ~GameObject();

		//! 每帧更新
		void	Update();
		//! 添加组件
		void	AddComponent(class Component* component);
		//! 移除组件
		void	RemoveComponent(class Component* component);

		//! 物体状态的get和set
		State	GetState() const;
		void	SetState(State state);

	protected:
		std::vector<class Component*>	mComponents;	//!<	组件数组

	private:
		class Game*						mGame;			//!<	Game对象
		State							mState;			//!<	物体当前状态
	};
}

#endif	// __Dungeon_GameObject__