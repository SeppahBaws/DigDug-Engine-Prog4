#include "pch.h"
#include "PookaBehaviourComponent.h"
#include "FiniteStateMachine.h"
#include "FSMState.h"
#include "FSMTransition.h"
#include "FSMFunctions.h"
#include "SpriteRenderComponent.h"
#include "GameObject.h"
#include "Time.h"
#include "BoxColliderComponent.h"
#include "PlayerBehaviourComponent.h"
#include "GameManagerComponent.h"

PookaBehaviourComponent::PookaBehaviourComponent()
	: m_pFSM(nullptr)
{
}

PookaBehaviourComponent::~PookaBehaviourComponent()
{
	delete m_pFSM;
	m_pFSM = nullptr;
}

void PookaBehaviourComponent::Start()
{
	// +--------------------------------+
	// |   Finite State Machine setup   |
	// +--------------------------------+
	// Create states
	dae::FSMState* pFreeRoamState = new dae::FSMState();
	dae::FSMState* pGhostState = new dae::FSMState();
	// dae::FSMState* pAttackState = new dae::FSMState();

	// Action lambdas
	auto enterFreeRoam = [](std::shared_ptr<dae::SpriteRenderComponent> pSpriteRenderer)
	{
		if (!pSpriteRenderer) return;
		pSpriteRenderer->SelectSprite("Run");
	};

	auto enterGhost = [](std::shared_ptr<dae::SpriteRenderComponent> pSpriteRenderer)
	{
		if (!pSpriteRenderer) return;
		pSpriteRenderer->SelectSprite("Ghost");
	};

	auto doStateTimer = [](float& stateAccu)
	{
		stateAccu += dae::Time::GetDeltaTime();
	};

	auto resetTime = [](float& timer)
	{
		timer = 0;
	};

	// Condition lambdas
	auto hasReachedMaxTime = [](float& accuTime, float max)
	{
		return accuTime >= max;
	};

	// Action functions
	dae::FSMActionBase* pEnterFreeRoamAction = new dae::FSMAction<std::shared_ptr<dae::SpriteRenderComponent>>(enterFreeRoam,
		GetGameObject()->GetComponent<dae::SpriteRenderComponent>());
	dae::FSMActionBase* pFreeRoamAction = new dae::FSMAction<float&>(doStateTimer, m_FreeRoamAccu);

	dae::FSMActionBase* pEnterGhostAction = new dae::FSMAction<std::shared_ptr<dae::SpriteRenderComponent>>(enterGhost,
		GetGameObject()->GetComponent<dae::SpriteRenderComponent>());
	dae::FSMActionBase* pGhostAction = new dae::FSMAction<float&>(doStateTimer, m_GhostAccu);

	dae::FSMActionBase* pResetGhostTime = new dae::FSMAction<float&>(resetTime, m_GhostAccu);
	dae::FSMActionBase* pResetFreeRoamTime = new dae::FSMAction<float&>(resetTime, m_FreeRoamAccu);

	// Condition functions
	dae::FSMConditionBase* pHasReachedMaxGhostTime = new dae::FSMCondition<float&, float>(hasReachedMaxTime, m_GhostAccu, m_GhostMaxTime);
	dae::FSMConditionBase* pHasMaxTimeInFreeRoam = new dae::FSMCondition<float&, float>(hasReachedMaxTime, m_FreeRoamAccu, m_FreeRoamMaxTime);


	// Set up states
	pFreeRoamState->SetActions({ pFreeRoamAction });
	pFreeRoamState->SetEntryActions({ pEnterFreeRoamAction });
	pFreeRoamState->SetTransitions(
		{
			new dae::FSMTransition(pGhostState, {pHasMaxTimeInFreeRoam}, {pResetFreeRoamTime})
		});

	pGhostState->SetActions({ pGhostAction });
	pGhostState->SetEntryActions({ pEnterGhostAction });
	pGhostState->SetTransitions(
		{
			new dae::FSMTransition(pFreeRoamState, {pHasReachedMaxGhostTime}, {pResetGhostTime})
		});


	// Create Finite State Machine
	m_pFSM = new dae::FiniteStateMachine({ pFreeRoamState, pGhostState }, pFreeRoamState);
	m_pFSM->Initialize();
}

void PookaBehaviourComponent::Update()
{
	m_pFSM->Update();

	auto boxCollider = GetGameObject()->GetComponent<dae::BoxColliderComponent>();
	if (boxCollider && boxCollider->IsColliding())
	{
		auto player = boxCollider->GetCollidingComponent()->GetGameObject()->GetComponent<PlayerBehaviourComponent>();
		if (player)
		{
			GameManagerComponent::KillPlayer(3);
			std::cout << "Pooka: Killed player, he'll respawn in 3 seconds" << std::endl;
		}
	}
}
