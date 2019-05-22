#pragma once
#include "BaseComponent.h"

enum class MovementState
{
	Idle,
	Running,
	Attacking
};

class PlayerMovementComponent : public dae::BaseComponent
{
public:
	PlayerMovementComponent();

	void Start() override;
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
