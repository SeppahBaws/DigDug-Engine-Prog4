#include "pch.h"
#include "PlayerMovementComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "InputManager.h"
#include "Time.h"
#include "SpriteRenderComponent.h"

class PlayerAttackCommand : public dae::Command
{
public:
	explicit PlayerAttackCommand(dae::ControllerButton button, dae::ControllerButtonState status, PlayerMovementComponent& comp)
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
	PlayerJumpCommand(dae::ControllerButton button, dae::ControllerButtonState status)
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
	PlayerDigCommand(dae::ControllerButton button, dae::ControllerButtonState status)
		: Command(button, status)
	{
	}

	void Execute() override
	{
		std::cout << "Player digging!" << std::endl;
	}
};

PlayerMovementComponent::PlayerMovementComponent()
	: m_MoveSpeed{ 500 }
	, m_State{ MovementState::Idle }
	, m_AttackAccu{ 0 }
	, m_TotalAttackTime{ 0.16f }
	, m_IsAttacking{ false }
{
}

void PlayerMovementComponent::Start()
{
	// Register the commands
	
	// Player Attack Command
	std::unique_ptr<PlayerAttackCommand> attackCommand = std::make_unique<PlayerAttackCommand>(
		dae::ControllerButton::ButtonA, dae::ControllerButtonState::Pressed, *this);
	dae::InputManager::GetInstance().RegisterCommand(std::move(attackCommand));

	// Player Jump Command
	std::unique_ptr<PlayerJumpCommand> jumpCommand = std::make_unique<PlayerJumpCommand>(
		dae::ControllerButton::ButtonA, dae::ControllerButtonState::Released);
	dae::InputManager::GetInstance().RegisterCommand(std::move(jumpCommand));

	// Player Dig Command
	std::unique_ptr<PlayerDigCommand> digCommand = std::make_unique<PlayerDigCommand>(
		dae::ControllerButton::ButtonX, dae::ControllerButtonState::Down);
	dae::InputManager::GetInstance().RegisterCommand(std::move(digCommand));
}

void PlayerMovementComponent::Update()
{
	std::shared_ptr<dae::TransformComponent> transform = GetGameObject()->GetComponent<dae::TransformComponent>();

	glm::vec2 move = dae::InputManager::GetInstance().GetThumbstick(dae::ControllerAxis::LeftThumbstick);
	move *= dae::Time::GetDeltaTime() * m_MoveSpeed;
	transform->SetPosition(transform->GetPosition() + glm::vec3(move.x, 0, 0));

	if (!m_IsAttacking)
	{
		if (abs(move.x) > 0 && abs(move.y) > 0)
		{
			m_State = MovementState::Running;
		}
		else if (dae::InputManager::GetInstance().IsDown(dae::ControllerButton::ButtonA))
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
