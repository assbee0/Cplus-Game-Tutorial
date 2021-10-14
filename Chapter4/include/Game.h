//! @file Game.h

#ifndef __Dungeon_Game__
#define __Dungeon_Game__

#include	<string>

namespace Dungeon
{
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

	private:
		//!	处理事件
		void	Event();
		//!	更新各种状态
		void	Update();
		//!	渲染
		void	Draw();

		//! 加载数据
		void	LoadData();
		//!	释放数据
		void	UnloadData();
		//!	加载贴图
		void	LoadTexture(const std::string fileName);

		class SDL_Window*	mWindow;		//!<	窗口
		class SDL_Renderer* mRenderer;		//!<	渲染器
		bool				mIsRunning;		//!<	运行状态

		class SDL_Texture*	mTexture;		//!<	图片
	};
}

#endif	// __Dungeon_Game__