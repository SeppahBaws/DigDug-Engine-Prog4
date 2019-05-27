#pragma once
#include "BaseComponent.h"
#include "GameObject.h"

class GameManager final : public dae::BaseComponent
{
public:

	virtual ~GameManager();

	static GameManager* GetInstance() { return s_Instance; }

	void RegisterPlayer(dae::GameObject* pPlayer);
	void RegisterPooka(dae::GameObject* pPooka);

	std::vector<dae::GameObject*> GetPookas();

	void KillPlayer(float respawnTime);

	void Start() override;
	void Update() override;

private:
	dae::GameObject* m_pPlayer = nullptr;
	std::vector<dae::GameObject*> m_pPookas;

	float m_PlayerDeadAccu = 0;
	float m_PlayerRespawnTime = 0;

	static GameManager* s_Instance;
};

