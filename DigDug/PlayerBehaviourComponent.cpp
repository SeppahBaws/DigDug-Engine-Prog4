#include "pch.h"
#include "PlayerBehaviourComponent.h"

#include "GameObject.h"
#include "TransformComponent.h"
#include "InputManager.h"
#include "Time.h"
#include "SpriteRenderComponent.h"
#include "BoxColliderComponent.h"
#include "SceneManager.h"
#include "Scene.h"

#include "FiniteStateMachine.h"
#include "FSMState.h"
#include "FSMTransition.h"
#include "FSMFunctions.h"

#include <glm/detail/func_geometric.inl>

#include "GameManager.h"

#pragma region Player Commands
class PlayerAttackCommand : public dae::Command
{
public:
	explicit PlayerAttackCommand(dae::GamepadButton button, dae::GamepadButtonState status, PlayerBehaviourComponent& comp)
		: Command(button, status)
		, m_PlayerBehaviour(comp)
		, m_AttackDistance(100)
	{
	}

	void Execute() override
	{
		std::cout << "Player Attack!" << std::endl;

		std::vector<dae::GameObject*> pPookas = GameManager::GetInstance()->GetPookas();

		glm::vec3 playerPos = m_PlayerBehaviour.GetTransform()->GetPosition();
		
		for (dae::GameObject* pPooka : pPookas)
		{
			if (!pPooka->IsActive())
				continue;

			if (glm::distance(playerPos, pPooka->GetTransform()->GetPosition()) <= m_AttackDistance)
			{
				std::cout << "Pooka in range!" << std::endl;

				// Just set the pookas inactive, because we can't dynamically add or destroy objects in a scene
				pPooka->SetActive(false);
			}
		}
	}

private:
	PlayerBehaviourComponent& m_PlayerBehaviour;
	float m_AttackDistance;
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
	GameManager::GetInstance()->RegisterPlayer(GetGameObject());


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
	
	// Create FiniteStateMachine
	m_pFSM = new dae::FiniteStateMachine(
		{ pIdleState, pRunningState },
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
}
