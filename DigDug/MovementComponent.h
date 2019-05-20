#pragma once
#include "BaseComponent.h"

namespace dae
{
	enum class MovementState
	{
		Idle,
		Running,
		Attacking
	};

	class MovementComponent : public BaseComponent
	{
	public:
		MovementComponent();

		void Update() override;

	private:
		void StartAttack();

	private:
		float m_MoveSpeed;
		MovementState m_State;
		float m_AttackAccu;
		float m_TotalAttackTime;
		bool m_IsAttacking;
	};
}
