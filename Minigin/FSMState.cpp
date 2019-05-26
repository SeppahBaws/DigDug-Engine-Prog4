#include "MiniginPCH.h"
#include "FSMState.h"
#include "FSMTransition.h"
// #include "FSMAction.h"
#include "FSMFunctions.h"

namespace dae
{
	FSMState::FSMState(const std::vector<FSMActionBase*>& pEntryActions, const std::vector<FSMActionBase*>& pActions,
		const std::vector<FSMActionBase*>& pExitActions, const std::vector<FSMTransition*>& pTransitions)
	{
		m_pEntryActions = std::move(pEntryActions);
		m_pActions = std::move(pActions);
		m_pExitActions = std::move(pExitActions);

		m_pTransitions = std::move(pTransitions);
	}

	FSMState::~FSMState()
	{
		for (FSMActionBase* pAction : m_pActions)
		{
			delete pAction;
			pAction = nullptr;
		}
		m_pActions.clear();

		for (FSMActionBase* pAction : m_pEntryActions)
		{
			delete pAction;
			pAction = nullptr;
		}
		m_pEntryActions.clear();

		for (FSMActionBase* pAction : m_pExitActions)
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

	void FSMState::SetEntryActions(const std::vector<FSMActionBase*>& pActions)
	{
		m_pEntryActions = std::move(pActions);
	}

	void FSMState::SetActions(const std::vector<FSMActionBase*>& pActions)
	{
		m_pActions = std::move(pActions);
	}

	void FSMState::SetExitActions(const std::vector<FSMActionBase*>& pActions)
	{
		m_pExitActions = std::move(pActions);
	}

	void FSMState::SetTransitions(const std::vector<FSMTransition*>& pTransitions)
	{
		m_pTransitions = std::move(pTransitions);
	}

	void FSMState::AddAction(FSMActionBase* pAction)
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
		for (FSMActionBase* pAction : m_pActions)
		{
			pAction->Execute();
		}
	}

	void FSMState::ExecuteEntryActions()
	{
		for (FSMActionBase* pAction : m_pEntryActions)
		{
			pAction->Execute();
		}
	}

	void FSMState::ExecuteExitActions()
	{
		for (FSMActionBase* pAction : m_pExitActions)
		{
			pAction->Execute();
		}
	}
}
