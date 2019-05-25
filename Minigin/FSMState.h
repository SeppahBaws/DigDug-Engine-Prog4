#pragma once

namespace dae
{
	class FSMAction;
	class FSMTransition;

	class FSMState
	{
	public:
		FSMState() = default;
		FSMState(const std::vector<FSMAction*>& pEntryActions,
			const std::vector<FSMAction*>& pActions,
			const std::vector<FSMAction*>& pExitActions,
			const std::vector<FSMTransition*>& pTransitions);
		~FSMState();

		void SetEntryActions(const std::vector<FSMAction*>& pActions);
		void SetActions(const std::vector<FSMAction*>& pActions);
		void SetExitActions(const std::vector<FSMAction*>& pActions);
		void SetTransitions(const std::vector<FSMTransition*>& pTransitions);

		void AddAction(FSMAction* pAction);
		void AddTransition(FSMTransition* pTransition);

		std::vector<FSMTransition*> GetTransitions() const;

		void Tick();
		void ExecuteEntryActions();
		void ExecuteExitActions();

	private:
		std::vector<FSMAction*> m_pActions;
		std::vector<FSMAction*> m_pEntryActions;
		std::vector<FSMAction*> m_pExitActions;

		std::vector<FSMTransition*> m_pTransitions;
	};
}
