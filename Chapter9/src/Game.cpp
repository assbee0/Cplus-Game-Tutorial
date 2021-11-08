//! @file Game.cpp

#include	<SDL/SDL.h>
#include	<SDL/SDL_image.h>
#include	<Game.h>
#include	<Player.h>
#include	<Dungeon.h>
#include	<SpriteComponent.h>
#include	<Timer.h>

namespace Dungeon
{
	Game::Game():
		mWindow(nullptr),
		mRenderer(nullptr),
		mIsRunning(true),
		mIsUpdating(false),
		mPlayer(nullptr)
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

		Timer::ticksCount = SDL_GetTicks();

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

	void Game::CreateSprite(SpriteComponent* sprite)
	{
		int order = sprite->GetDrawOrder();
		// 按照绘制顺序插入
		auto iter = mSprites.begin();
		for (; iter != mSprites.end(); ++iter)
		{
			if (order < (*iter)->GetDrawOrder())
			{
				break;
			}
		}
		mSprites.insert(iter, sprite);
	}

	void Game::RemoveSprite(SpriteComponent* sprite)
	{
		auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
		mSprites.erase(iter);
	}

	SDL_Texture* Game::GetTexture(const std::string& fileName)
	{
		SDL_Texture* tex = nullptr;
		auto iter = mTextures.find(fileName);
		if (iter != mTextures.end())
		{
			tex = iter->second;
		}
		return tex;
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

		// 获取键盘输入状态
		const uint8_t* keyState = SDL_GetKeyboardState(NULL);

		// 处理所有物体的输入逻辑
		mIsUpdating = true;
		for (auto gameObject : mGameObjects)
		{
			gameObject->ProcessInput(keyState);
		}
		mIsUpdating = false;
	}

	void Game::Update()
	{
		// 设置帧率
		Tick(60);

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

		// 绘制所有精灵
		for (auto sprite : mSprites)
		{
			sprite->Draw(mRenderer);
		}

		// 交换缓冲区
		SDL_RenderPresent(mRenderer);
	}

	void Game::Tick(int fps)
	{
		// 根据设置的帧率计算每帧至少的时间
		int fpsTime = 1000 / fps;
		// 如果上一帧结束后还没有达到要求时间，则等待
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), Timer::ticksCount + fpsTime))
		{
			SDL_Delay(1);
		}

		// 计算新的增量时间
		Timer::deltaTime = (SDL_GetTicks() - Timer::ticksCount) / 1000.0f;
		// 计算新的一帧开始时所经过的总时间
		Timer::ticksCount = SDL_GetTicks();
	}

	void Game::LoadData()
	{
		LoadTexture("sprites/chrA07.png", "player");
		LoadTexture("sprites/ground.png", "ground");
		LoadTexture("sprites/wall.png", "wall");
		
		mPlayer = new Player(this);
		mDungeon = new Dungeon(this);
	}

	void Game::UnloadData()
	{
		// 释放所有游戏物体
		while (!mGameObjects.empty())
		{
			delete mGameObjects.back();
		}

		// 释放所有贴图资源
		for (auto tex : mTextures)
		{
			SDL_DestroyTexture(tex.second);
		}
		mTextures.clear();
	}

	void Game::LoadTexture(const std::string& fileName, const std::string& newName)
	{
		// 判断该key值是否已被使用
		auto iter = mTextures.find(newName);
		if (iter != mTextures.end())
		{
			SDL_DestroyTexture(iter->second);
			mTextures.erase(iter);
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

		// 将贴图加入到哈希表中，并将新名字作为key值
		mTextures.emplace(newName, tex);
	}
}