//! @file MapComponent.h

#ifndef __Dungeon_MapComponent__
#define __Dungeon_MapComponent__

#include	<SpriteComponent.h>
#include	<unordered_map>

namespace Dungeon
{
	class MapComponent : public SpriteComponent
	{
	public:
		//! 构造函数
		MapComponent(class GameObject* gameObject);
		//! 析构函数
		~MapComponent();

		//! 绘制（重写）
		void	Draw(SDL_Renderer* renderer) override;
		//! 设置贴图
		void	SetTexture(SDL_Texture* texture, int number);

		//! 获取地图数组
		int*	GetMap();

	private:
		int*	mMapArray;									//!<	地图数组	
		std::unordered_map<int, SDL_Texture*> mTextures;	//!<	贴图存储
	};
}

#endif	// __Dungeon_MapComponent__