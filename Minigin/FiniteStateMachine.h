#pragma once

namespace dae
{
	class FSMState;

	class FiniteStateMachine
	{
	public:
		FiniteStateMachine(const std::vector<FSMState*>& pStates, FSMState* pStartState);
		~FiniteStateMachine();

		void Initialize();
		void Update();

	private:
		std::vector<FSMState*> m_pStates;
		FSMState* m_pCurrentState;
	};
}
