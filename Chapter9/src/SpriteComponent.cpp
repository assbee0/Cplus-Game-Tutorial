//! @file SpriteComponent.cpp

#include	<SpriteComponent.h>
#include	<GameObject.h>
#include	<Game.h>
#include	<SDL/SDL.h>

namespace Dungeon
{
	SpriteComponent::SpriteComponent(GameObject* gameObject, int drawOrder) :
		Component(gameObject),
		mTexture(nullptr),
		mTexWidth(0),
		mTexHeight(0),
		mDrawOrder(drawOrder)
	{
		mGameObject->GetGame()->CreateSprite(this);
	}

	SpriteComponent::~SpriteComponent()
	{
		mGameObject->GetGame()->RemoveSprite(this);
	}

	void SpriteComponent::Draw(SDL_Renderer* renderer)
	{
		if (!mTexture)
		{
			return;
		}

		// 贴图即将被绘制的位置
		SDL_Rect dstrect;
		dstrect.w = static_cast<int>(mTexWidth * mGameObject->GetScale().x);
		dstrect.h = static_cast<int>(mTexHeight * mGameObject->GetScale().y);
		dstrect.x = static_cast<int>(mGameObject->GetPosition().x);
		dstrect.y = static_cast<int>(mGameObject->GetPosition().y);
		// 绘制贴图（考虑旋转）
		SDL_RenderCopyEx(renderer, mTexture, nullptr, &dstrect, mGameObject->GetRotation(), nullptr, SDL_FLIP_NONE);
	}

	void SpriteComponent::SetTexture(SDL_Texture* texture)
	{
		mTexture = texture;
		// 从贴图中查询贴图的宽和高
		SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
	}

	int SpriteComponent::GetTexWidth() const
	{
		return mTexWidth;
	}

	int SpriteComponent::GetTexHeight() const
	{
		return mTexHeight;
	}

	int SpriteComponent::GetDrawOrder() const
	{
		return mDrawOrder;
	}

	void SpriteComponent::SetDrawOrder(int order)
	{
		mDrawOrder = order;
	}


}