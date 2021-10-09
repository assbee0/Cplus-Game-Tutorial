//! @file Game.cpp

#include	<SDL/SDL.h>
#include	<Game.h>

namespace Dungeon
{
	Game::Game():
		mWindow(nullptr),
		mIsRunning(true)
	{

	}

	bool Game::Initialize()
	{
		// SDL库初始化
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			SDL_Log("SDL库初始化失败: %s", SDL_GetError());
			return false;
		}

		// 窗口初始化
		mWindow = SDL_CreateWindow("Dungeon", 400, 200, 600, 480, 0);
		if (!mWindow)
		{
			SDL_Log("窗口初始化失败: %s", SDL_GetError());
			return false;
		}

		return true;
	}

	void Game::Loop()
	{
		while (mIsRunning)
		{
			Event();
			Update();
			Draw();
		}
	}

	void Game::Shutdown()
	{
		SDL_DestroyWindow(mWindow);
		SDL_Quit();
	}

	void Game::Event()
	{
		SDL_Event event;
		// 如果事件队列中有未处理的事件，按顺序处理
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				// 退出事件，按下窗口的叉
			case SDL_QUIT:
				mIsRunning = false;
				break;
			default:
				break;
			}
		}
	}

	void Game::Update()
	{
	}

	void Game::Draw()
	{
	}
}