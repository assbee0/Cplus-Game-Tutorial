//! @file MapComponent.cpp

#include	<GameObject.h>
#include	<MapComponent.h>
#include	<SDL/SDL.h>

namespace Dungeon
{
	MapComponent::MapComponent(GameObject* gameObject):
		SpriteComponent(gameObject, 0)
	{
		// 宽20高15的地图
		mMapArray = new int[20 * 15];
		// 随便进行一下初始化
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (i < 2 || j < 2 || i>12 || j>17)
				{
					mMapArray[i * 20 + j] = 1;
				}
				else
				{
					mMapArray[i * 20 + j] = 0;
				}
			}
		}
	}

	MapComponent::~MapComponent()
	{
		delete mMapArray;
	}

	void MapComponent::Draw(SDL_Renderer* renderer)
	{
		SDL_Rect dstRect{ 0, 0, 32, 32 };
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				// 实际在窗口中的位置
				dstRect.x = j * 32;
				dstRect.y = i * 32;
				// 该地图块的值
				int massNumber = mMapArray[i * 20 + j];
				// 通过地图块的值去索引贴图并绘制
				SDL_RenderCopy(renderer, mTextures[massNumber], nullptr, &dstRect);
			}
		}
	}

	void MapComponent::SetTexture(SDL_Texture* texture, int number)
	{
		mTextures.emplace(number, texture);
	}

}