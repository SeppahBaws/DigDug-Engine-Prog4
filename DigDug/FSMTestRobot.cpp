#include "pch.h"
#include "FSMTestRobot.h"
#include "FiniteStateMachine.h"
#include "FSMState.h"
#include "FSMTransition.h"
#include "FSMFunctions.h"
#include "Time.h"

using namespace dae;

FSMTestRobot::~FSMTestRobot()
{
	delete m_pFSM;
}

void FSMTestRobot::Initialize()
{
	// +---------------------------+
	// |   Create all the states   |
	// +---------------------------+
	FSMState* pRefuelState	= new FSMState();
	FSMState* pSearchState	= new FSMState();
	FSMState* pMoveState	= new FSMState();
	FSMState* pRemoveState	= new FSMState();


	// +--------------------+
	// |   Action lambdas   |
	// +--------------------+
	auto capBatteryLevel = [](float& power, float capacity)
	{
		if (power > capacity)
			power = capacity;
	};
	auto setTrashInSight = [](bool& foundTrash, bool state) { foundTrash = state; };
	auto setMovingTrash = [](bool& movingTrash, bool state) { movingTrash = state; };


	// +-----------------------+
	// |   Condition lambdas   |
	// +-----------------------+
	auto isLowOnBattery = [](float& batteryLevel, float batteryLimit)
	{ return batteryLevel <= batteryLimit; };

	auto hasReachedRechargeLimit = [](float& batteryLevel, float batteryCapacity)
	{ return batteryLevel >= batteryCapacity; };

	auto random1OutOf6 = []()
	{
		auto r = rand() % 6;
		return r == 0;
	};

	auto isMovingTrash = [](bool& movingTrash) { return movingTrash; };
	auto hasTrashInSight = [](bool& foundTrash) { return foundTrash; };


	// +----------------------+
	// |   Action functions   |
	// +----------------------+
	FSMActionBase* pRefuelAction = new FSMAction<float&, float>(Refuel, m_BatteryPower, m_BatteryRechargeInterval);
	FSMActionBase* pRemoveAction = new FSMAction<float&, float>(RemovingTrash, m_BatteryPower, m_BatteryRechargeInterval);
	FSMActionBase* pMoveAction = new FSMAction<float&, float>(MoveToTrash, m_BatteryPower, m_BatteryRechargeInterval);
	FSMActionBase* pSearchAction = new FSMAction<>(Search);
	FSMActionBase* pSetFoundTrashAction = new FSMAction<bool&, bool>(setTrashInSight, m_FoundTrash, true);
	FSMActionBase* pSetNotFoundTrashAction = new FSMAction<bool&, bool>(setTrashInSight, m_FoundTrash, false);
	FSMActionBase* pSetRemovingTrashAction = new FSMAction<bool&, bool>(setMovingTrash, m_MovingTrash, true);
	FSMActionBase* pSetNotRemovingTrashAction = new FSMAction<bool&, bool>(setMovingTrash, m_MovingTrash, false);
	FSMActionBase* pCapBatteryLevelAction = new FSMAction<float&, float>(capBatteryLevel, m_BatteryPower, m_BatteryCapacity);


	// +-------------------------+
	// |   Condition functions   |
	// +-------------------------+
	FSMConditionBase* pLowBatteryCondition = new FSMCondition<float&, float>(isLowOnBattery, m_BatteryPower, m_BatteryCapacity);
	FSMConditionBase* pRechargedCondition = new FSMCondition<float&, float>(hasReachedRechargeLimit, m_BatteryPower, m_BatteryCapacity);
	FSMConditionBase* pRandomValueCondition = new FSMCondition<>(random1OutOf6);
	FSMConditionBase* pMovingTrashCondition = new FSMCondition<bool&>(isMovingTrash, m_MovingTrash);
	FSMConditionBase* pTrashInSightCondition = new FSMCondition<bool&>(hasTrashInSight, m_FoundTrash);

	
	// +---------------------------+
	// |   Set up all the states   |
	// +---------------------------+
	pRefuelState->SetActions({ pRefuelAction });
	pRefuelState->SetTransitions(
		{
			new FSMTransition(pSearchState, {pRechargedCondition}, {pCapBatteryLevelAction})
		});

	pSearchState->SetActions({ pSearchAction });
	pSearchState->SetTransitions(
		{
			new FSMTransition(pRemoveState, {pMovingTrashCondition}, {}),
			new FSMTransition(pMoveState, {pTrashInSightCondition}, {}),
			new FSMTransition(pMoveState, {pRandomValueCondition}, {pSetFoundTrashAction})
		});

	pMoveState->SetActions({ pMoveAction });
	pMoveState->SetTransitions(
		{
			new FSMTransition(pRefuelState, {pLowBatteryCondition}, {}),
			new FSMTransition(pRemoveState, {pRandomValueCondition}, {pSetRemovingTrashAction})
		});

	pRemoveState->SetActions({ pRemoveAction });
	pRemoveState->SetTransitions(
		{
			new FSMTransition(pRefuelState, {pLowBatteryCondition}, {}),
			new FSMTransition(pSearchState, {pRandomValueCondition}, { pSetNotRemovingTrashAction, pSetNotFoundTrashAction })
		});

	m_pFSM = new FiniteStateMachine(
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

void FSMTestRobot::MoveToTrash(float& batteryLevel, float depletionInterval)
{
	std::cout << "Moving to trash. BatteryLevel: " << batteryLevel << std::endl;
	batteryLevel -= depletionInterval;
}

void FSMTestRobot::RemovingTrash(float& batteryLevel, float depletionInterval)
{
	std::cout << "Removing trash! BatteryLevel: " << batteryLevel << std::endl;
	batteryLevel -= depletionInterval;
}

void FSMTestRobot::Refuel(float& batteryLevel, float rechargeInterval)
{
	std::cout << "Refueling... BatteryLevel: " << batteryLevel << std::endl;
	batteryLevel += rechargeInterval;
}
