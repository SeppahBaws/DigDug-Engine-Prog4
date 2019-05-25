#include "pch.h"
#include "FSMTestRobot.h"
#include "FiniteStateMachine.h"
#include "FSMState.h"
#include "FSMAction.h"
#include "FSMTransition.h"
#include "FSMCondition.h"
#include "Time.h"

#pragma region FSM Actions
class CapBatteryAction : public dae::FSMAction
{
public:
	CapBatteryAction(FSMTestRobot* pRobot) : m_pRobot(pRobot) {}
	void Execute() override
	{
		if (m_pRobot->m_BatteryPower > m_pRobot->m_BatteryCapacity)
			m_pRobot->m_BatteryPower = m_pRobot->m_BatteryCapacity;
	}
private:
	FSMTestRobot* m_pRobot;
};
class RefuelAction : public dae::FSMAction
{
public:
	RefuelAction(FSMTestRobot* pRobot) : m_pRobot(pRobot){}
	void Execute() override
	{
		m_pRobot->Refuel();
	}
private:
	FSMTestRobot* m_pRobot;
};
class SearchAction : public dae::FSMAction
{
public:
	SearchAction(FSMTestRobot* pRobot) : m_pRobot(pRobot){}
	void Execute() override
	{
		m_pRobot->Search();
	}
private:
	FSMTestRobot* m_pRobot;
};
class MoveAction : public dae::FSMAction
{
public:
	MoveAction(FSMTestRobot* pRobot) : m_pRobot(pRobot) {}
	void Execute() override
	{
		m_pRobot->MoveToTrash();
	}
private:
	FSMTestRobot* m_pRobot;
};
class RemoveAction : public dae::FSMAction
{
public:
	RemoveAction(FSMTestRobot* pRobot) : m_pRobot(pRobot) {}

	void Execute() override
	{
		m_pRobot->RemovingTrash();
	}
private:
	FSMTestRobot* m_pRobot;
};
class SetMovingTrashAction : public dae::FSMAction
{
public:
	SetMovingTrashAction(FSMTestRobot* pRobot, bool value) : m_pRobot(pRobot), m_bValue(value) {}
	void Execute() override
	{
		m_pRobot->m_MovingTrash = m_bValue;
	}
private:
	FSMTestRobot* m_pRobot;
	bool m_bValue;
};
class SetTrashInSightAction : public dae::FSMAction
{
public:
	SetTrashInSightAction(FSMTestRobot* pRobot, bool value) : m_pRobot(pRobot), m_bValue(value) {}
	void Execute() override
	{
		m_pRobot->m_FoundTrash = m_bValue;
	}
private:
	FSMTestRobot* m_pRobot;
	bool m_bValue;
};
#pragma endregion

#pragma region FSM Conditions
class BatteryLowCond : public dae::FSMCondition
{
public:
	BatteryLowCond(FSMTestRobot* pRobot) : m_pRobot(pRobot) {}
	bool Evaluate() override
	{
		return m_pRobot->m_BatteryPower <= m_pRobot->m_CriticalBatteryLevel;
	}
private:
	FSMTestRobot* m_pRobot;
};
class BatteryMaxCond : public dae::FSMCondition
{
public:
	BatteryMaxCond(FSMTestRobot* pRobot) : m_pRobot(pRobot) {}
	bool Evaluate() override
	{
		return m_pRobot->m_BatteryPower >= m_pRobot->m_BatteryCapacity;
	}
private:
	FSMTestRobot* m_pRobot;
};
class Random1OutOf6 : public dae::FSMCondition
{
public:
	bool Evaluate() override
	{
		int r = rand() % 6;
		return r == 0;
	}
};
class MovingTrashCond : public dae::FSMCondition
{
public:
	MovingTrashCond(FSMTestRobot* pRobot) : m_pRobot(pRobot) {}
	bool Evaluate() override
	{
		return m_pRobot->m_MovingTrash;
	}
private:
	FSMTestRobot* m_pRobot;
};
class TrashInSightCond : public dae::FSMCondition
{
public:
	TrashInSightCond(FSMTestRobot* pRobot) : m_pRobot(pRobot) {}
	bool Evaluate() override
	{
		return m_pRobot->m_FoundTrash;
	}
private:
	FSMTestRobot* m_pRobot;
};
#pragma endregion


FSMTestRobot::~FSMTestRobot()
{
	delete m_pFSM;
}

void FSMTestRobot::Initialize()
{
	// Create states
	dae::FSMState* pRefuelState	= new dae::FSMState();
	dae::FSMState* pSearchState	= new dae::FSMState();
	dae::FSMState* pMoveState	= new dae::FSMState();
	dae::FSMState* pRemoveState	= new dae::FSMState();

	// Create conditions
	BatteryLowCond* pBatteryLow		= new BatteryLowCond(this);
	BatteryMaxCond* pBatteryMax		= new BatteryMaxCond(this);
	Random1OutOf6* pRandomValue		= new Random1OutOf6();
	MovingTrashCond* pMovingTrash	= new MovingTrashCond(this);
	TrashInSightCond* pTrashSight	= new TrashInSightCond(this);

	// Setup states
	pRefuelState->SetActions({ new RefuelAction(this) });
	pRefuelState->SetTransitions(
		{
			new dae::FSMTransition(pSearchState, {pBatteryMax}, {new CapBatteryAction(this)})
		});

	pSearchState->SetActions({ new SearchAction(this) });
	pSearchState->SetTransitions(
		{
			new dae::FSMTransition(pRemoveState, {pMovingTrash}, {}),
			new dae::FSMTransition(pMoveState, {pTrashSight}, {}),
			new dae::FSMTransition(pMoveState, {pRandomValue}, {new SetTrashInSightAction(this, true)})
		});

	pMoveState->SetActions({ new MoveAction(this) });
	pMoveState->SetTransitions(
		{
			new dae::FSMTransition(pRefuelState, {pBatteryLow}, {}),
			new dae::FSMTransition(pRemoveState, {pRandomValue}, {new SetMovingTrashAction(this, true)})
		});

	pRemoveState->SetActions({ new RemoveAction(this) });
	pRemoveState->SetTransitions(
		{
			new dae::FSMTransition(pRefuelState, {pBatteryLow}, {}),
			new dae::FSMTransition(pSearchState, {pRandomValue},
				{
					new SetMovingTrashAction(this, false),
					new SetTrashInSightAction(this, false)
				})
		});

	m_pFSM = new dae::FiniteStateMachine(
		{ pRefuelState, pSearchState, pMoveState, pRemoveState },
		pSearchState);
}

void FSMTestRobot::Update()
{
	// Timer - Only update when > interval
	m_UpdateTimer += dae::Time::GetDeltaTime();
	if (m_UpdateTimer >= m_UpdateInterval)
	{
		m_UpdateTimer = 0.0f;
		m_pFSM->Update();
	}
}

void FSMTestRobot::Search()
{
	std::cout << "Searching for garbage..." << std::endl;
}

void FSMTestRobot::MoveToTrash()
{
	std::cout << "Moving to trash. BatteryLevel: " << m_BatteryPower << std::endl;
	m_BatteryPower -= m_BatteryDepletionInterval;
}

void FSMTestRobot::RemovingTrash()
{
	std::cout << "Removing trash! BatteryLevel: " << m_BatteryPower << std::endl;
	m_BatteryPower -= m_BatteryDepletionInterval;
}

void FSMTestRobot::Refuel()
{
	std::cout << "Refueling... BatteryLevel: " << m_BatteryPower << std::endl;
	m_BatteryPower += m_BatteryRechargeInterval;
}
