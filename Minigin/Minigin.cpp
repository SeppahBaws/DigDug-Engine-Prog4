#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"
#include "Components.h"
#include "SceneSwitcherComponent.h"


void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	// Scene 1
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	SceneManager::GetInstance().SetActiveScene("Demo");

	auto go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<RenderComponent>("background.jpg"));
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->GetComponent<TransformComponent>()->SetPosition(glm::vec3{ 216, 180, 0 });
	go->AddComponent(std::make_shared<RenderComponent>("logo.png"));
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<GameObject>();
	go->GetComponent<TransformComponent>()->SetPosition(glm::vec3{ 80, 20, 0 });
	go->AddComponent(std::make_shared<TextComponent>("Programming 4 Assignment", font));
	scene.Add(go);

	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);
	auto fpsObject = std::make_shared<GameObject>();
	fpsObject->AddComponent(std::make_shared<TextComponent>("0 fps", fpsFont, SDL_Color{ 255, 255, 0 }));
	fpsObject->AddComponent(std::make_shared<FpsComponent>());
	scene.Add(fpsObject);



	// Scene 2
	auto& scene2 = SceneManager::GetInstance().CreateScene("Demo2");

	auto font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 40);
	auto demoObj2 = std::make_shared<GameObject>();
	demoObj2->GetComponent<TransformComponent>()->SetPosition(glm::vec3{ 80, 20, 0 });
	demoObj2->AddComponent(std::make_shared<TextComponent>("Scene 2", font));
	scene2.Add(demoObj2);

	SceneManager::GetInstance().SetActiveScene("Demo2");
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
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
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		while (doContinue)
		{
			const auto currentTime = std::chrono::high_resolution_clock::now();
			Time::GetInstance().Update(lastTime);

			doContinue = input.ProcessInput();
			sceneManager.Update();
			renderer.Render();

			t = lastTime + std::chrono::milliseconds(msPerFrame);
			lastTime = currentTime;
			std::this_thread::sleep_until(t);
		}
	}

	Cleanup();
}
