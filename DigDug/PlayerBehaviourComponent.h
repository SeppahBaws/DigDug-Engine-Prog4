#pragma once
#include "BaseComponent.h"

#include <glm/vec2.hpp>

// Engine Forward Declarations
namespace dae
{
	class FiniteStateMachine;
}

class PlayerBehaviourComponent final : public dae::BaseComponent
{
public:
	PlayerBehaviourComponent();
	~PlayerBehaviourComponent();

	void Start() override;
	void Update() override;

private:
	dae::FiniteStateMachine* m_pFSM;

	glm::vec2 m_Velocity;

	float m_MovementSpeed;
	float m_AttackAccu;
	float m_TotalAttackTime;
};
