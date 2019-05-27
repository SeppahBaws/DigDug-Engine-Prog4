#include "pch.h"
#include "GameManager.h"
#include "Time.h"

GameManager* GameManager::s_Instance = nullptr;

GameManager::~GameManager()
{
	m_pPlayer = nullptr;

	for (dae::GameObject* pPooka : m_pPookas)
	{
		pPooka = nullptr;
	}
	m_pPookas.clear();
}

void GameManager::Start()
{
	s_Instance = this;
}

void GameManager::Update()
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

void GameManager::RegisterPlayer(dae::GameObject* pPlayer)
{
	m_pPlayer = pPlayer;
}

void GameManager::RegisterPooka(dae::GameObject* pPooka)
{
	m_pPookas.push_back(pPooka);
}

std::vector<dae::GameObject*> GameManager::GetPookas()
{
	return m_pPookas;
}

void GameManager::KillPlayer(float respawnTime)
{
	m_PlayerRespawnTime = respawnTime;
	m_pPlayer->GetComponent<dae::TransformComponent>()->SetPosition(0, 0, 0);
	m_pPlayer->SetActive(false);
}
