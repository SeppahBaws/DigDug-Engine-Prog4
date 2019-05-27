#include "MiniginPCH.h"
#include "FiniteStateMachine.h"
#include "FSMState.h"
#include "FSMTransition.h"

namespace dae
{
	FiniteStateMachine::FiniteStateMachine(const std::vector<FSMState*>& pStates, FSMState* pStartState)
		: m_pStates(pStates)
		, m_pCurrentState(pStartState)
	{
	}

	FiniteStateMachine::~FiniteStateMachine()
	{
		m_pCurrentState = nullptr;

		for (size_t i = 0; i < m_pStates.size(); i++)
		{
			if (m_pStates[i] != nullptr)
			{
				delete m_pStates[i];
				m_pStates[i] = nullptr;
			}
		}
		m_pStates.clear();
	}

	void FiniteStateMachine::Initialize()
	{
		m_pCurrentState->ExecuteEntryActions();
	}

	void FiniteStateMachine::Update()
	{
		bool isTransitioning = false;
		FSMTransition* pCurrentTransition = nullptr;

		// Check all transitions
		for (FSMTransition* pTransition : m_pCurrentState->GetTransitions())
		{
			// Indicate whether we have to transition
			isTransitioning = pTransition->IsTriggered();
			if (isTransitioning)
			{
				pCurrentTransition = pTransition;
				break;
			}
		}

		if (isTransitioning)
		{
			// Exit the current state, transition, and enter the new state
			m_pCurrentState->ExecuteExitActions();
			pCurrentTransition->ExecuteExitActions();
			pCurrentTransition->GetTargetState()->ExecuteEntryActions();

			// Switch the current state to the new state
			m_pCurrentState = pCurrentTransition->GetTargetState();
		}
		else
		{
			m_pCurrentState->Tick();
		}
	}
}
