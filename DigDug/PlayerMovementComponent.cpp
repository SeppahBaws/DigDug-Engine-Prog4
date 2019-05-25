#include "pch.h"
#include "PlayerMovementComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "InputManager.h"
#include "Time.h"
#include "SpriteRenderComponent.h"
#include "FiniteStateMachine.h"
#include "FSMState.h"
#include "FSMTransition.h"
#include "FSMAction.h"
#include "FSMCondition.h"

#include "FSMTestRobot.h"

#pragma region Player Commands
class PlayerAttackCommand : public dae::Command
{
public:
	explicit PlayerAttackCommand(dae::GamepadButton button, dae::GamepadButtonState status, PlayerMovementComponent& comp)
		: Command(button, status)
		, m_Movement(comp)
	{
	}

	void Execute() override
	{
		std::cout << "Player Attack!" << std::endl;
	}

private:
	PlayerMovementComponent& m_Movement;
};

class PlayerJumpCommand : public dae::Command
{
public:
	PlayerJumpCommand(dae::GamepadButton button, dae::GamepadButtonState status)
		: Command(button, status)
	{
	}

	void Execute() override
	{
		std::cout << "Player Jump!" << std::endl;
	}
};

class PlayerDigCommand : public dae::Command
{
public:
	PlayerDigCommand(dae::GamepadButton button, dae::GamepadButtonState status)
		: Command(button, status)
	{
	}

	void Execute() override
	{
		std::cout << "Player digging!" << std::endl;
	}
};
#pragma endregion

#pragma region FSM Classes
class IdleAction : public dae::FSMAction
{
public:
	IdleAction() = default;

	void Execute() override
	{
		
	}

private:
	MovementState* m_pMovementState;
};

class RunningAction : public dae::FSMAction
{
public:
	RunningAction() = default;

	void Execute() override
	{
		
	}
};

class AttackingAction : public dae::FSMAction
{
public:
	AttackingAction() = default;

	void Execute() override
	{
		
	}
};

class IdleCondition : public dae::FSMCondition
{
public:
	IdleCondition() = default;

	bool Evaluate() override
	{
		if (std::rand() > 500)
		{
			
		}
	}
};
#pragma endregion 

PlayerMovementComponent::PlayerMovementComponent()
	: m_pFSM(nullptr)
	, m_MoveSpeed{ 500 }
	, m_State{ MovementState::Idle }
	, m_AttackAccu{ 0 }
	, m_TotalAttackTime{ 0.16f }
	, m_IsAttacking{ false }
{
}

PlayerMovementComponent::~PlayerMovementComponent()
{
	// delete m_pFSM;
	delete m_pRobot;
}

void PlayerMovementComponent::Start()
{
	// Register the commands
	
	// Player Attack Command
	std::unique_ptr<PlayerAttackCommand> attackCommand = std::make_unique<PlayerAttackCommand>(
		dae::GamepadButton::ButtonA, dae::GamepadButtonState::Pressed, *this);
	dae::InputManager::GetInstance().RegisterCommand(std::move(attackCommand));

	// Player Jump Command
	std::unique_ptr<PlayerJumpCommand> jumpCommand = std::make_unique<PlayerJumpCommand>(
		dae::GamepadButton::ButtonA, dae::GamepadButtonState::Released);
	dae::InputManager::GetInstance().RegisterCommand(std::move(jumpCommand));

	// Player Dig Command
	std::unique_ptr<PlayerDigCommand> digCommand = std::make_unique<PlayerDigCommand>(
		dae::GamepadButton::ButtonX, dae::GamepadButtonState::Down);
	dae::InputManager::GetInstance().RegisterCommand(std::move(digCommand));


	// // Create States
	// dae::FSMState* pStateIdle = new dae::FSMState();
	// dae::FSMState* pStateRunning = new dae::FSMState();
	//
	// // Prepare the Transitions
	// dae::FSMTransition* pIdleToRunningTransition = new dae::FSMTransition();
	// pIdleToRunningTransition->AddCondition(new IdleCondition());
	// pIdleToRunningTransition->SetTargetState(pStateRunning);
	//
	// // Prepare the States
	// pStateIdle->AddAction(new IdleAction());
	// pStateIdle->AddTransition(pIdleToRunningTransition);
	//
	// pStateRunning->AddAction(new RunningAction());
	//
	//
	// // Create FiniteStateMachine
	// m_pFSM = new dae::FiniteStateMachine(
	// 	{ pStateIdle, pStateRunning/*, pStateShooting, pStatePumping*/ },
	// 	pStateIdle);

	m_pRobot = new FSMTestRobot();
	m_pRobot->Initialize();
}

void PlayerMovementComponent::Update()
{
	// m_pFSM->Update();
	m_pRobot->Update();

	std::shared_ptr<dae::TransformComponent> transform = GetGameObject()->GetComponent<dae::TransformComponent>();

	glm::vec2 move = dae::InputManager::GetInstance().GetThumbstick(dae::GamepadAxis::LeftThumbstick);
	move *= dae::Time::GetDeltaTime() * m_MoveSpeed;
	transform->SetPosition(transform->GetPosition() + glm::vec3(move.x, 0, 0));

	if (!m_IsAttacking)
	{
		if (abs(move.x) > 0 && abs(move.y) > 0)
		{
			m_State = MovementState::Running;
		}
		else if (dae::InputManager::GetInstance().IsDown(dae::GamepadButton::ButtonA))
		{
			StartAttack();
		}
		else
		{
			m_State = MovementState::Idle;
		}
	}
	else
	{
		m_AttackAccu += dae::Time::GetDeltaTime();
		if (m_AttackAccu >= m_TotalAttackTime)
		{
			m_IsAttacking = false;
			m_AttackAccu = 0;
		}
	}

	switch (m_State)
	{
	case MovementState::Idle:
		GetGameObject()->GetComponent<dae::SpriteRenderComponent>()->SelectSprite("Run");
		// todo: set sprite playback speed to 0
		break;
	case MovementState::Running:
		GetGameObject()->GetComponent<dae::SpriteRenderComponent>()->SelectSprite("Run");
		break;
	case MovementState::Attacking:
		GetGameObject()->GetComponent<dae::SpriteRenderComponent>()->SelectSprite("Pump");
		break;
	}
}

void PlayerMovementComponent::StartAttack()
{
	m_IsAttacking = true;
	m_State = MovementState::Attacking;
}
