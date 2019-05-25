#include "MiniginPCH.h"
#include "FSMState.h"
#include "FSMTransition.h"
#include "FSMAction.h"

namespace dae
{
	FSMState::FSMState(const std::vector<FSMAction*>& pEntryActions, const std::vector<FSMAction*>& pActions,
		const std::vector<FSMAction*>& pExitActions, const std::vector<FSMTransition*>& pTransitions)
	{
		m_pEntryActions = std::move(pEntryActions);
		m_pActions = std::move(pActions);
		m_pExitActions = std::move(pExitActions);

		m_pTransitions = std::move(pTransitions);
	}

	FSMState::~FSMState()
	{
		for (FSMAction* pAction : m_pActions)
		{
			delete pAction;
			pAction = nullptr;
		}
		m_pActions.clear();

		for (FSMAction* pAction : m_pEntryActions)
		{
			delete pAction;
			pAction = nullptr;
		}
		m_pEntryActions.clear();

		for (FSMAction* pAction : m_pExitActions)
		{
			delete pAction;
			pAction = nullptr;
		}
		m_pExitActions.clear();

		for (FSMTransition* pTransition : m_pTransitions)
		{
			delete pTransition;
			pTransition = nullptr;
		}
		m_pTransitions.clear();
	}

	void FSMState::SetEntryActions(const std::vector<FSMAction*>& pActions)
	{
		m_pEntryActions = std::move(pActions);
	}

	void FSMState::SetActions(const std::vector<FSMAction*>& pActions)
	{
		m_pActions = std::move(pActions);
	}

	void FSMState::SetExitActions(const std::vector<FSMAction*>& pActions)
	{
		m_pExitActions = std::move(pActions);
	}

	void FSMState::SetTransitions(const std::vector<FSMTransition*>& pTransitions)
	{
		m_pTransitions = std::move(pTransitions);
	}

	void FSMState::AddAction(FSMAction* pAction)
	{
		m_pActions.push_back(pAction);
	}

	void FSMState::AddTransition(FSMTransition* pTransition)
	{
		m_pTransitions.push_back(pTransition);
	}

	std::vector<FSMTransition*> FSMState::GetTransitions() const
	{
		return m_pTransitions;
	}

	void FSMState::Tick()
	{
		for (FSMAction* pAction : m_pActions)
		{
			pAction->Execute();
		}
	}

	void FSMState::ExecuteEntryActions()
	{
		for (FSMAction* pAction : m_pEntryActions)
		{
			pAction->Execute();
		}
	}

	void FSMState::ExecuteExitActions()
	{
		for (FSMAction* pAction : m_pExitActions)
		{
			pAction->Execute();
		}
	}
}
