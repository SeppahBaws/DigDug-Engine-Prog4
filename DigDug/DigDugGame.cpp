#include "pch.h"
#include "DigDugGame.h"

// Engine includes
#include "Scene.h"
#include "Components.h"
#include "GameObject.h"
#include "LuaHelpers.h"
#include "Sprite.h"

// Game includes
#include "PlayerBehaviourComponent.h"

using namespace dae;

void DigDugGame::LoadGame() const
{
	// Scene 1
	Scene& scene = SceneManager::GetInstance().CreateScene("Demo");
	SceneManager::GetInstance().SetActiveScene("Demo");

	// +----------------+
	// |   Background   |
	// +----------------+
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<RenderComponent>("background.jpg"));
	scene.Add(go);

	// +------------+
	// |   Player   |
	// +------------+
	std::shared_ptr<GameObject> player = std::make_shared<GameObject>();
	player->GetComponent<TransformComponent>()->SetPosition(50, 200, 0);
	std::shared_ptr<SpriteRenderComponent> spriteRenderer = std::make_shared<SpriteRenderComponent>();

	LuaHelpers::GetInstance().OpenFile("Sprites.lua");

	// Read and set sprites config
	SpriteRenderConfig config = LuaHelpers::GetInstance().ReadSpriteConfig("spriteRenderConfig");
	spriteRenderer->SelectSprite(config.defaultSprite);
	spriteRenderer->SetScale(config.scale);

	// Read and set sprites
	std::vector<Sprite> playerSprites = LuaHelpers::GetInstance().ReadSprites("player", { "run", "dig", "pump", "shoot", "death" });
	for (Sprite& sprite : playerSprites)
	{
		spriteRenderer->AddSprite(std::make_unique<Sprite>(sprite));
	}

	player->AddComponent(spriteRenderer);
	player->AddComponent(std::make_shared<PlayerBehaviourComponent>());
	scene.Add(player);
}
