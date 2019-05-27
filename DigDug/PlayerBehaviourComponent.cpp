#include "pch.h"
#include "PlayerBehaviourComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "InputManager.h"
#include "Time.h"
#include "SpriteRenderComponent.h"
#include "FiniteStateMachine.h"
#include "FSMState.h"
#include "FSMTransition.h"
#include "FSMFunctions.h"
#include "FSMTestRobot.h"
#include <glm/detail/func_geometric.inl>
#include "BoxColliderComponent.h"
#include "GameManagerComponent.h"

#pragma region Player Commands
class PlayerAttackCommand : public dae::Command
{
public:
	explicit PlayerAttackCommand(dae::GamepadButton button, dae::GamepadButtonState status, PlayerBehaviourComponent& comp)
		: Command(button, status)
		, m_Movement(comp)
	{
	}

	void Execute() override
	{
		std::cout << "Player Attack!" << std::endl;
	}

private:
	PlayerBehaviourComponent& m_Movement;
};
#pragma endregion

PlayerBehaviourComponent::PlayerBehaviourComponent()
	: m_pFSM(nullptr)
	, m_MovementSpeed{ 500 }
{
}

PlayerBehaviourComponent::~PlayerBehaviourComponent()
{
	delete m_pFSM;
	m_pFSM = nullptr;
}

void PlayerBehaviourComponent::Start()
{
	// Register the player with the game manager
	GameManagerComponent::RegisterPlayer(GetGameObject());


	// +---------------------------------+
	// |   Player Input Commands setup   |
	// +---------------------------------+
	// Player Attack Command
	std::unique_ptr<PlayerAttackCommand> attackCommand = std::make_unique<PlayerAttackCommand>(
		dae::GamepadButton::ButtonA, dae::GamepadButtonState::Pressed, *this);
	dae::InputManager::GetInstance().RegisterCommand(std::move(attackCommand));


	// +--------------------------------+
	// |   Finite State Machine setup   |
	// +--------------------------------+
	// Create states
	dae::FSMState* pIdleState = new dae::FSMState();
	dae::FSMState* pRunningState = new dae::FSMState();
	// dae::FSMState* pPumpingState = new dae::FSMState();

	// Action lambdas
	// auto pumpAction = [](float& accuTime)
	// {
	// 	accuTime += dae::Time::GetDeltaTime();
	// };
	auto enterIdle = [](std::shared_ptr<dae::SpriteRenderComponent> pSpriteRenderer)
	{
		pSpriteRenderer->SelectSprite("Run");
		pSpriteRenderer->SetSpeed(0);
	};
	auto enterRunning = [](std::shared_ptr<dae::SpriteRenderComponent> pSpriteRenderer)
	{
		pSpriteRenderer->SelectSprite("Run");
		pSpriteRenderer->SetSpeed(1.0f);
	};

	// Condition lambdas
	auto isMoving = [](glm::vec2& velocity) { return glm::length(velocity) > 0; };
	auto isNotMoving = [](glm::vec2& velocity) { return glm::length(velocity) <= 0; };

	// Action functions
	// dae::FSMActionBase* pPumpingAction = new dae::FSMAction<float&>(pumpAction, m_AttackAccu);
	dae::FSMActionBase* pEnterIdleAction = new dae::FSMAction<std::shared_ptr<dae::SpriteRenderComponent>>(enterIdle,
		GetGameObject()->GetComponent<dae::SpriteRenderComponent>());
	dae::FSMActionBase* pEnterRunningAction = new dae::FSMAction<std::shared_ptr<dae::SpriteRenderComponent>>(enterRunning,
		GetGameObject()->GetComponent<dae::SpriteRenderComponent>());


	// Condition functions
	dae::FSMConditionBase* pMovingCondition = new dae::FSMCondition<glm::vec2&>(isMoving, m_Velocity);
	dae::FSMConditionBase* pNotMovingCondition = new dae::FSMCondition<glm::vec2&>(isNotMoving, m_Velocity);

	pIdleState->SetEntryActions({ pEnterIdleAction });
	pIdleState->SetTransitions(
		{
			new dae::FSMTransition(pRunningState, {pMovingCondition}, {})
		});

	pRunningState->SetEntryActions({ pEnterRunningAction });
	pRunningState->SetTransitions(
		{
			new dae::FSMTransition(pIdleState, {pNotMovingCondition}, {})
		});

	// pPumpingState->SetActions({ pPumpingAction });
	// pPumpingState->SetTransitions(
	// 	{
	//
	// 	});
	
	// Create FiniteStateMachine
	m_pFSM = new dae::FiniteStateMachine(
		{ pIdleState, pRunningState/*, pStateShooting, pStatePumping*/ },
		pIdleState);
	m_pFSM->Initialize();
}

void PlayerBehaviourComponent::Update()
{
	m_pFSM->Update();

	std::shared_ptr<dae::TransformComponent> transform = GetGameObject()->GetComponent<dae::TransformComponent>();

	m_Velocity = dae::InputManager::GetInstance().GetThumbstick(dae::GamepadAxis::LeftThumbstick);
	m_Velocity *= dae::Time::GetDeltaTime() * m_MovementSpeed;
	transform->SetPosition(transform->GetPosition() + glm::vec3(m_Velocity.x, m_Velocity.y, 0));


	// Check collisions
	if (GetGameObject()->GetComponent<dae::BoxColliderComponent>()->IsColliding())
	{
		std::cout << "Colliding!" << std::endl;
	}
}
