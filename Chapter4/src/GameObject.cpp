//! @file GameObject.cpp

#include	<GameObject.h>
#include	<Game.h>
#include	<Component.h>

namespace Dungeon
{
	GameObject::GameObject(Game* game) :
		mGame(game),
		mState(State::EActive)
	{
		mGame->CreateGameObject(this);
	}

	GameObject::~GameObject()
	{
		mGame->RemoveGameObject(this);
		while (!mComponents.empty())
		{
			delete mComponents.back();
		}
	}

	void GameObject::Update()
	{
		if (mState == State::EActive)
		{
			// 每帧执行，更新所有的组件
			for (auto component : mComponents)
			{
				component->Update();
			}
		}
	}

	void GameObject::AddComponent(Component* component)
	{
		// 获取该组件的更新顺序
		int order = component->GetUpdateOrder();
		auto iter = mComponents.begin();
		// 新组件需要按顺序插入到对应位置
		for (; iter != mComponents.end(); ++iter)
		{
			if (order < (*iter)->GetUpdateOrder())
			{
				break;
			}
		}
		mComponents.insert(iter, component);
	}

	void GameObject::RemoveComponent(Component* component)
	{
		auto iter = std::find(mComponents.begin(), mComponents.end(), component);
		if (iter != mComponents.end())
		{
			mComponents.erase(iter);
		}
	}

	GameObject::State GameObject::GetState() const
	{
		return mState;
	}

	void GameObject::SetState(State state)
	{
		mState = state;
	}
}