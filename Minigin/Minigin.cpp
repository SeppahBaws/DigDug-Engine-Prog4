#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include <SDL.h>

#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"
#include "Components.h"

#include "SceneSwitcher.h"
#include "TestComponent.h"


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
	Scene& scene = SceneManager::GetInstance().CreateScene("Demo");
	// SceneManager::GetInstance().SetActiveScene("Demo");

	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<RenderComponent>("background.jpg"));
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->GetComponent<TransformComponent>()->SetPosition(glm::vec3{ 216, 180, 0 });
	go->AddComponent(std::make_shared<RenderComponent>("logo.png"));
	scene.Add(go);

	std::shared_ptr<Font> font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<GameObject>();
	go->GetComponent<TransformComponent>()->SetPosition(glm::vec3{ 80, 20, 0 });
	go->AddComponent(std::make_shared<TextComponent>("Programming 4 Assignment", font));
	scene.Add(go);

	std::shared_ptr<Font> fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);
	std::shared_ptr<GameObject> fpsObject = std::make_shared<GameObject>();
	fpsObject->AddComponent(std::make_shared<TextComponent>("0 fps", fpsFont, SDL_Color{ 255, 255, 0 }));
	fpsObject->AddComponent(std::make_shared<FpsComponent>());
	scene.Add(fpsObject);

	scene.Add(std::make_shared<SceneSwitcher>());


	// Scene 2
	Scene& scene2 = SceneManager::GetInstance().CreateScene("Demo2");

	std::shared_ptr<Font> font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 40);
	std::shared_ptr<GameObject> demoObj2 = std::make_shared<GameObject>();
	demoObj2->GetComponent<TransformComponent>()->SetPosition(glm::vec3{ 80, 20, 0 });
	demoObj2->AddComponent(std::make_shared<TextComponent>("Scene 2", font));
	demoObj2->AddComponent(std::make_shared<TestComponent>());
	demoObj2->AddComponent(std::make_shared<TestComponent>());

	demoObj2->RemoveComponent<TestComponent>();
	scene2.Add(demoObj2);

	scene2.Add(std::make_shared<SceneSwitcher>());

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
