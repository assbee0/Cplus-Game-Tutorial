//! @file SpriteComponent.h

#ifndef __Dungeon_SpriteComponent__
#define __Dungeon_SpriteComponent__

#include	<Component.h>

struct SDL_Texture;
struct SDL_Renderer;

namespace Dungeon
{
	class GameObject;

	class SpriteComponent : public Component
	{
	public:
		//! 构造函数
		SpriteComponent(GameObject* gameObject, int drawOrder);
		//! 析构函数
		~SpriteComponent();

		//! 绘制函数
		virtual void Draw(SDL_Renderer* renderer);
		//! 设置贴图
		virtual void SetTexture(SDL_Texture* texture);

		//! 贴图宽度的get
		int		GetTexWidth() const;
		//! 贴图高度的get
		int		GetTexHeight() const;
		//! 绘制顺序的get和set
		int		GetDrawOrder() const;
		void	SetDrawOrder(int order);

	protected:
		SDL_Texture*	mTexture;		//!<	贴图		
		int				mDrawOrder;		//!<	绘制顺序
		int				mTexWidth;		//!<	贴图宽
		int				mTexHeight;		//!<	贴图高
	};
}

#endif	// __Dungeon_SpriteComponent__