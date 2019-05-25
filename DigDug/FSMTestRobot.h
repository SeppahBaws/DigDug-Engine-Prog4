#pragma once

namespace dae
{
	class FiniteStateMachine;
	class FSMAction;
	class FSMCondition;
	class FSMTransition;
}


// This is a test robot that removes trash. It has a fuel level and can move around.
// It can only move around when it has enough fuel. If it doesn't have enough fuel, it stops to recharge
// until it has enough fuel again to continue with removing trash.
//
// This robot comes from the classes of Gameplay Programming.
// I adjusted it a bit to work with my implementation of a Finite State Machine.
class FSMTestRobot
{
public:
	FSMTestRobot() = default;
	~FSMTestRobot();

	void Initialize();
	void Update();

private:
	dae::FiniteStateMachine* m_pFSM = nullptr;

	float m_UpdateTimer = 0.0f;
	float m_UpdateInterval = 0.25f;

	float m_BatteryCapacity = 40.0f;
	float m_BatteryPower = 25.0f;
	float m_CriticalBatteryLevel = 5.0f;
	float m_BatteryRechargeInterval = 6.0f;
	float m_BatteryDepletionInterval = 4.0f;

	bool m_FoundTrash = false;
	bool m_MovingTrash = false;

private:
	friend class CapBatteryAction;
	friend class RefuelAction;
	friend class SearchAction;
	friend class MoveAction;
	friend class RemoveAction;
	friend class SetMovingTrashAction;
	friend class SetTrashInSightAction;

	friend class BatteryLowCond;
	friend class BatteryMaxCond;
	friend class Random1OutOf6;
	friend class MovingTrashCond;
	friend class TrashInSightCond;

	void Search();
	void MoveToTrash();
	void RemovingTrash();
	void Refuel();
};
