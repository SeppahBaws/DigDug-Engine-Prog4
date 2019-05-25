#pragma once
#include "BaseComponent.h"

// Engine Forward Declarations
namespace dae
{
	class FiniteStateMachine;
}

// Other Forward Declarations
class FSMTestRobot;

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
	~PlayerMovementComponent();

	void Start() override;
	void Update() override;

private:
	void StartAttack();

private:
	dae::FiniteStateMachine* m_pFSM;
	FSMTestRobot* m_pRobot;

	float m_MoveSpeed;
	MovementState m_State;
	float m_AttackAccu;
	float m_TotalAttackTime;
	bool m_IsAttacking;
};
