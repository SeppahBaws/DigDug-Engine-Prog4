#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include <SDL.h>

// Engine includes
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"
#include "Components.h"
#include "Sprite.h"

// Game includes
#include "InputTesterComponent.h"
#include "MovementComponent.h"
#include "LuaHelpers.h"

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

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	// Scene 1
	Scene& scene = SceneManager::GetInstance().CreateScene("Demo", true);

	// ------------------
	// --- Background ---
	// ------------------
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<RenderComponent>("background.jpg"));
	scene.Add(go);

	// ---------------------
	// --- Sprite tester ---
	// ---------------------
	std::shared_ptr<GameObject> spriteTester = std::make_shared<GameObject>();
	spriteTester->GetComponent<TransformComponent>()->SetPosition(50, 200, 0);
	std::shared_ptr<SpriteRenderComponent> spriteRenderer = std::make_shared<SpriteRenderComponent>();

	LuaHelpers::GetInstance().OpenFile("Sprites.lua");
	
	// Read and set sprites config
	SpriteRenderConfig config = LuaHelpers::GetInstance().ReadSpriteConfig("spriteRenderConfig");
	spriteRenderer->SelectSprite(config.defaultSprite);
	spriteRenderer->SetScale(config.scale);

	// Read and set sprites
	std::vector<Sprite> sprites = LuaHelpers::GetInstance().ReadSprites("sprites", { "idle", "run", "attack" });
	for (Sprite& sprite : sprites)
	{
		spriteRenderer->AddSprite(std::make_unique<Sprite>(sprite));
	}

	spriteTester->AddComponent(spriteRenderer);
	spriteTester->AddComponent(std::make_shared<MovementComponent>());
	scene.Add(spriteTester);
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
