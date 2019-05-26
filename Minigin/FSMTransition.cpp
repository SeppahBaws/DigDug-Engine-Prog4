#include "MiniginPCH.h"
#include "FSMTransition.h"
#include "FSMFunctions.h"

namespace dae
{
	FSMTransition::FSMTransition(FSMState* pTargetState, std::vector<FSMConditionBase*> pConditions, std::vector<FSMActionBase*> pExitActions)
		: m_pConditions(pConditions)
		, m_pExitActions(pExitActions)
		, m_pTargetState(pTargetState)
	{
	}

	FSMTransition::FSMTransition()
		: m_pConditions({})
		, m_pExitActions({})
		, m_pTargetState()
	{
	}

	FSMTransition::~FSMTransition()
	{
		m_pTargetState = nullptr;

		for (FSMActionBase* pAction : m_pExitActions)
		{
			delete pAction;
			pAction = nullptr;
		}
		m_pExitActions.clear();

		for (FSMConditionBase* pCondition : m_pConditions)
		{
			delete pCondition;
			pCondition = nullptr;
		}
		m_pConditions.clear();
	}

	void FSMTransition::AddCondition(FSMConditionBase* pCondition)
	{
		m_pConditions.push_back(pCondition);
	}

	void FSMTransition::AddExitAction(FSMActionBase* pAction)
	{
		m_pExitActions.push_back(pAction);
	}

	void FSMTransition::SetTargetState(FSMState* pState)
	{
		m_pTargetState = pState;
	}

	FSMState* FSMTransition::GetTargetState() const
	{
		return m_pTargetState;
	}

	bool FSMTransition::IsTriggered()
	{
		for (FSMConditionBase* pCondition : m_pConditions)
		{
			if (pCondition->Evaluate())
			{
				return true;
			}
		}

		return false;
	}

	void FSMTransition::ExecuteExitActions()
	{
		for (FSMActionBase* pAction : m_pExitActions)
		{
			pAction->Execute();
		}
	}
}
