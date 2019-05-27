#include "pch.h"
#include "GameManagerComponent.h"
#include "Time.h"

GameManagerComponent* GameManagerComponent::s_Instance = nullptr;

void GameManagerComponent::Start()
{
	s_Instance = this;
}

void GameManagerComponent::Update()
{
	if (!m_pPlayer->IsActive())
	{
		m_PlayerDeadAccu += dae::Time::GetDeltaTime();

		if (m_PlayerDeadAccu >= m_PlayerRespawnTime)
		{
			m_PlayerDeadAccu = 0;
			m_pPlayer->SetActive(true);
		}
	}
}

void GameManagerComponent::RegisterPlayer(dae::GameObject* pPlayer)
{
	s_Instance->m_pPlayer = pPlayer;
}

void GameManagerComponent::KillPlayer(float respawnTime)
{
	s_Instance->m_PlayerRespawnTime = respawnTime;
	s_Instance->m_pPlayer->SetActive(false);
	s_Instance->m_pPlayer->GetComponent<dae::TransformComponent>()->SetPosition(0, 0, 0);
}
