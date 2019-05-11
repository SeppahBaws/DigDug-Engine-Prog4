#include "MiniginPCH.h"
#include "MovementComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "InputManager.h"
#include "Time.h"
#include "SpriteRenderComponent.h"

namespace dae
{
	MovementComponent::MovementComponent()
		: m_MoveSpeed{ 500 }
		, m_State{ MovementState::Idle }
		, m_AttackAccu{ 0 }
		, m_TotalAttackTime{ 0.16f }
		, m_IsAttacking{ false }
	{
	}

	void MovementComponent::Update()
	{
		std::shared_ptr<TransformComponent> transform = GetGameObject()->GetComponent<TransformComponent>();

		glm::vec2 move = InputManager::GetInstance().GetThumbstick(ControllerAxis::LeftThumbstick);
		move *= Time::GetDeltaTime() * m_MoveSpeed;
		transform->SetPosition(transform->GetPosition() + glm::vec3(move.x, 0, 0));

		if (!m_IsAttacking)
		{
			if (abs(move.x) > 0 && abs(move.y) > 0)
			{
				m_State = MovementState::Running;
			}
			else if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonA))
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
			m_AttackAccu += Time::GetDeltaTime();
			if (m_AttackAccu >= m_TotalAttackTime)
			{
				m_IsAttacking = false;
				m_AttackAccu = 0;
			}
		}

		switch (m_State)
		{
		case MovementState::Idle:
			GetGameObject()->GetComponent<SpriteRenderComponent>()->SelectSprite("DwarfIdle");
			break;
		case MovementState::Running:
			GetGameObject()->GetComponent<SpriteRenderComponent>()->SelectSprite("DwarfRun");
			break;
		case MovementState::Attacking:
			GetGameObject()->GetComponent<SpriteRenderComponent>()->SelectSprite("DwarfAttack");
			break;
		}
	}

	void MovementComponent::StartAttack()
	{
		m_IsAttacking = true;
		m_State = MovementState::Attacking;
	}
}
