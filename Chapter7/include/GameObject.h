//! @file GameObject.h

#ifndef __Dungeon_GameObject__
#define __Dungeon_GameObject__

#include	<string>
#include	<vector>
#include	<Math/Math.h>

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

		//! 获取特定类型的组件，并得到该组件类型的指针
		template<typename T> T* GetComponent()
		{
			for (auto com : mComponents)
			{
				T* component = dynamic_cast<T*>(com);
				if (component != nullptr)
				{
					return component;
				}
			}
			return nullptr;
		}

		//! game对象的get
		Game*		GetGame() const;
		//! 物体状态的get和set
		State		GetState() const;
		void		SetState(State state);
		//! 位置的get和set
		Vector2		GetPosition() const;
		void		SetPosition(const Vector2& p);
		//! 缩放大小的get和set
		Vector2		GetScale() const;
		void		SetScale(Vector2 s);
		//! 旋转的get和set
		float		GetRotation() const;
		void		SetRotation(float r);

	protected:
		std::vector<class Component*>	mComponents;	//!<	组件数组

	private:
		Game*							mGame;			//!<	Game对象
		State							mState;			//!<	物体当前状态
		Vector2							mPosition;		//!<	位置坐标
		Vector2							mScale;			//!<	缩放
		float							mRotation;		//!<	旋转
	};
}

#endif	// __Dungeon_GameObject__