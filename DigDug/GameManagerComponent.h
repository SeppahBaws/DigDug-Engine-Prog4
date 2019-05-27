#pragma once
#include "BaseComponent.h"
#include "GameObject.h"

class GameManagerComponent final : public dae::BaseComponent
{
public:

	static void RegisterPlayer(dae::GameObject* pPlayer);
	static void KillPlayer(float respawnTime);

	void Start() override;
	void Update() override;

private:
	dae::GameObject* m_pPlayer = nullptr;
	float m_PlayerDeadAccu = 0;
	float m_PlayerRespawnTime = 0;

	static GameManagerComponent* s_Instance;
};
