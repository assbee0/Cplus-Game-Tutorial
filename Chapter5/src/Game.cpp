//! @file Game.cpp

#include	<SDL/SDL.h>
#include	<SDL/SDL_image.h>
#include	<Game.h>
#include	<GameObject.h>

namespace Dungeon
{
	Game::Game():
		mWindow(nullptr),
		mRenderer(nullptr),
		mIsRunning(true),
		mIsUpdating(false),
		mTexture(nullptr)
	{

	}

	bool Game::Initialize()
	{
		// SDL库初始化
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
			return false;
		}

		// 窗口初始化
		mWindow = SDL_CreateWindow("Dungeon", 400, 200, 640, 480, 0);
		if (!mWindow)
		{
			SDL_Log("Failed to create window: %s", SDL_GetError());
			return false;
		}

		// 渲染器初始化
		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
		if (!mRenderer)
		{
			SDL_Log("Failed to create renderer: %s", SDL_GetError());
			return false;
		}

		// 初始化SDL_image库
		if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
		{
			SDL_Log("Failed to initialize SDL_image: %s", SDL_GetError());
			return false;
		}

		// 加载数据
		LoadData();

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
		UnloadData();
		SDL_DestroyRenderer(mRenderer);
		SDL_DestroyWindow(mWindow);
		SDL_Quit();
		IMG_Quit();
	}

	void Game::CreateGameObject(GameObject* gameObject)
	{
		// 如果当前正在更新，将该对象加入等待区
		if (mIsUpdating)
		{
			mPendingObjects.emplace_back(gameObject);
		}
		else
		{
			mGameObjects.emplace_back(gameObject);
		}
	}

	void Game::RemoveGameObject(GameObject* gameObject)
	{
		// 先在等待区中寻找并移除物体
		auto iter = std::find(mPendingObjects.begin(), mPendingObjects.end(), gameObject);
		if (iter != mPendingObjects.end())
		{
			// 交换后删除末尾，效率高于erase，但会破坏顺序
			std::iter_swap(iter, mPendingObjects.end() - 1);
			mPendingObjects.pop_back();
		}

		// 在正式物体区中寻找并移除物体
		iter = std::find(mGameObjects.begin(), mGameObjects.end(), gameObject);
		if (iter != mGameObjects.end())
		{
			// 交换后删除末尾，效率高于erase，但会破坏顺序
			std::iter_swap(iter, mGameObjects.end() - 1);
			mGameObjects.pop_back();
		}
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
		// 等待10ms（临时用）
		SDL_Delay(10);

		// 更新开始
		mIsUpdating = true;
		// 遍历并执行所有物体的更新函数
		for (auto gameObject : mGameObjects)
		{
			gameObject->Update();
		}
		// 更新结束
		mIsUpdating = false;

		// 将所有等待区物体移动至正式的物体区
		for (auto pendingObject : mPendingObjects)
		{
			mGameObjects.emplace_back(pendingObject);
		}
		// 清空等待区
		mPendingObjects.clear();

		// 将所有状态为EDead的物体添加至死亡区
		std::vector<GameObject*> deadObjects;
		for (auto deadObject : mGameObjects)
		{
			if (deadObject->GetState() == GameObject::State::EDead)
			{
				deadObjects.emplace_back(deadObject);
			}
		}
		// 释放掉所有死亡区的物体
		for (auto deadObject : deadObjects)
		{
			delete deadObject;
		}
	}

	void Game::Draw()
	{
		// 设置渲染器颜色（蓝）
		SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);

		// 清除缓冲区
		SDL_RenderClear(mRenderer);

		int textureW;
		int textureH;
		// 获取贴图的宽和高
		SDL_QueryTexture(mTexture, nullptr, nullptr, &textureW, &textureH);

		// 截取原图片（这里是完整截取）
		SDL_Rect imageRect{ 0, 0, textureW, textureH };
		// 图片目的地
		SDL_Rect dstRect{ 130, 50, textureW, textureH };
		// 将截取好的图片拷贝并填充至目的地的长方形中
		SDL_RenderCopy(mRenderer, mTexture, &imageRect, &dstRect);

		// 交换缓冲区
		SDL_RenderPresent(mRenderer);
	}

	void Game::LoadData()
	{
		LoadTexture("sprites/yajyuu.jpg");
	}

	void Game::UnloadData()
	{
		// 释放所有游戏物体
		while (!mGameObjects.empty())
		{
			delete mGameObjects.back();
		}

		SDL_DestroyTexture(mTexture);
	}

	void Game::LoadTexture(const std::string fileName)
	{
		// 清空当前贴图，防止重复读取时内存泄漏
		if (mTexture)
		{
			SDL_DestroyTexture(mTexture);
		}

		// 读取图片存为surface形式
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
		}

		// 将surface转换为texture形式
		SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		// 释放surface的内存
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
		}

		mTexture = tex;
	}
}