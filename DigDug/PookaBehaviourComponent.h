#pragma once
#include "BaseComponent.h"

// Engine Forward Declarations
namespace dae
{
	class FiniteStateMachine;
}

class PookaBehaviourComponent : public dae::BaseComponent
{
public:
	PookaBehaviourComponent();
	~PookaBehaviourComponent();

	void Start() override;
	void Update() override;

private:
	dae::FiniteStateMachine* m_pFSM;

	const float m_FreeRoamMaxTime = 5.0f;
	const float m_GhostMaxTime = 5.0f;
	float m_FreeRoamAccu = 0.0f;
	float m_GhostAccu = 0.0f;
};
