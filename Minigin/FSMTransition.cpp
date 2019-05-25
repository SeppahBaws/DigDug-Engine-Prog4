#include "MiniginPCH.h"
#include "FSMTransition.h"
#include "FSMAction.h"
#include "FSMCondition.h"

namespace dae
{
	FSMTransition::FSMTransition(FSMState* pTargetState, std::vector<FSMCondition*> pConditions, std::vector<FSMAction*> pExitActions)
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

		for (FSMAction* pAction : m_pExitActions)
		{
			delete pAction;
			pAction = nullptr;
		}
		m_pExitActions.clear();

		for (FSMCondition* pCondition : m_pConditions)
		{
			delete pCondition;
			pCondition = nullptr;
		}
		m_pConditions.clear();
	}

	void FSMTransition::AddCondition(FSMCondition* pCondition)
	{
		m_pConditions.push_back(pCondition);
	}

	void FSMTransition::AddExitAction(FSMAction* pAction)
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
		for (FSMCondition* pCondition : m_pConditions)
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
		for (FSMAction* pAction : m_pExitActions)
		{
			pAction->Execute();
		}
	}
}
