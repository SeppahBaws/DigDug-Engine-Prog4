#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include <SDL.h>

#include "InputManager.h"
#include "LuaHelpers.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Time.h"

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_pWindow = SDL_CreateWindow(
		"DigDug - Seppe Dekeyser - 2DAE06 - 2018-2019",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1280,
		720,
		SDL_WINDOW_OPENGL
	);
	if (m_pWindow == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_pWindow);
	LuaHelpers::Init();
}

void dae::Minigin::Cleanup()
{
	LuaHelpers::Cleanup();
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto t = std::chrono::high_resolution_clock::now();
		Renderer& renderer = Renderer::GetInstance();
		SceneManager& sceneManager = SceneManager::GetInstance();
		InputManager& input = InputManager::GetInstance();

		sceneManager.Start();

		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		while (doContinue)
		{
			const auto currentTime = std::chrono::high_resolution_clock::now();
			Time::GetInstance().Update(lastTime);

			doContinue = input.ProcessInput();
			sceneManager.Update();
			renderer.Render();

			t = lastTime + std::chrono::milliseconds(m_MsPerFrame);
			lastTime = currentTime;
			std::this_thread::sleep_until(t);
		}
	}

	Cleanup();
}
