#include "pch.h"
#include "PlayerMovementComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "InputManager.h"
#include "Time.h"
#include "SpriteRenderComponent.h"

PlayerMovementComponent::PlayerMovementComponent()
	: m_MoveSpeed{ 500 }
	, m_State{ MovementState::Idle }
	, m_AttackAccu{ 0 }
	, m_TotalAttackTime{ 0.16f }
	, m_IsAttacking{ false }
{
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
		else if (dae::InputManager::GetInstance().IsPressed(dae::ControllerButton::ButtonA))
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
