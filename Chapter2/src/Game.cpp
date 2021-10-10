//! @file Game.cpp

#include	<SDL/SDL.h>
#include	<Game.h>

namespace Dungeon
{
	Game::Game():
		mWindow(nullptr),
		mRenderer(nullptr),
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
		mWindow = SDL_CreateWindow("Dungeon", 400, 200, 640, 480, 0);
		if (!mWindow)
		{
			SDL_Log("窗口初始化失败: %s", SDL_GetError());
			return false;
		}

		// 渲染器初始化
		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
		if (!mRenderer)
		{
			SDL_Log("渲染器初始化失败: %s", SDL_GetError());
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
		SDL_DestroyRenderer(mRenderer);
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
		// 设置渲染器颜色（蓝）
		SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);

		// 清除缓冲区
		SDL_RenderClear(mRenderer);

		// 设置渲染器颜色（白）
		SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

		// 设置长方形的坐标以及宽高
		SDL_Rect rect;
		rect.x = 200;
		rect.y = 200;
		rect.w = 240;
		rect.h = 80;
		// 绘制长方形
		SDL_RenderFillRect(mRenderer, &rect);

		// 交换缓冲区
		SDL_RenderPresent(mRenderer);
	}
}