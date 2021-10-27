//! @file Game.h

#ifndef __Dungeon_Game__
#define __Dungeon_Game__

#include	<string>
#include	<vector>
#include	<unordered_map>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

namespace Dungeon
{
	class GameObject;
	class SpriteComponent;
	class Player;

	class Game
	{
	public:
		//!	构造函数
		Game();

		//!	初始化
		bool	Initialize();
		//!	主循环
		void	Loop();
		//!	游戏结束
		void	Shutdown();

		//! 创建并存储游戏物体
		void	CreateGameObject(GameObject* gameObject);
		//! 移除游戏对象
		void	RemoveGameObject(GameObject* gameObject);
		//! 创建并按绘制顺序存储精灵
		void	CreateSprite(SpriteComponent* sprite);
		//! 移除精灵
		void	RemoveSprite(SpriteComponent* sprite);
		//! 获取贴图
		SDL_Texture* GetTexture(const std::string& fileName);

	private:
		//!	处理事件
		void	Event();
		//!	更新各种状态
		void	Update();
		//!	渲染
		void	Draw();

		//! 设置帧率
		void	Tick(int fps);
		//! 加载数据
		void	LoadData();
		//!	释放数据
		void	UnloadData();
		//!	加载贴图并重命名
		void	LoadTexture(const std::string& fileName, const std::string& newName);

		std::vector<GameObject*> mGameObjects;		//!<	游戏物体容器
		std::vector<GameObject*> mPendingObjects;	//!<	等待状态的游戏物体容器
		std::vector<SpriteComponent*> mSprites;		//!<	存放精灵的容器

		std::unordered_map<std::string, SDL_Texture*> mTextures;	//!<	存放贴图的容器

		SDL_Window*		mWindow;		//!<	窗口
		SDL_Renderer*	mRenderer;		//!<	渲染器
		bool			mIsRunning;		//!<	运行状态
		bool			mIsUpdating;	//!<	是否在更新状态

		Player*			mPlayer;		//!<	玩家角色
	};
}

#endif	// __Dungeon_Game__