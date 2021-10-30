//! @file GameObject.cpp

#include	<Game.h>
#include	<Component.h>
#include	<GameObject.h>

namespace Dungeon
{
	GameObject::GameObject(Game* game) :
		mGame(game),
		mState(State::EActive),
		mPosition(Vector2::Zero),
		mScale(Vector2::One),
		mRotation(0.0f)
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

	void GameObject::ProcessInput(const uint8_t* state)
	{
		if (mState == State::EActive)
		{
			// 每帧执行，处理所有组件的输入逻辑
			for (auto component : mComponents)
			{
				component->ProcessInput(state);
			}
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

	Game* GameObject::GetGame() const
	{
		return mGame;
	}

	GameObject::State GameObject::GetState() const
	{
		return mState;
	}

	void GameObject::SetState(const State state)
	{
		mState = state;
	}

	Vector2 GameObject::GetPosition() const
	{
		return mPosition;
	}

	void GameObject::SetPosition(const Vector2& p)
	{
		mPosition = p;
	}

	Vector2 GameObject::GetScale() const
	{
		return mScale;
	}

	void GameObject::SetScale(const Vector2& s)
	{
		mScale = s;
	}

	float GameObject::GetRotation() const
	{
		return mRotation;
	}

	void GameObject::SetRotation(float r)
	{
		mRotation = r;
	}
}