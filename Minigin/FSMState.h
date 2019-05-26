#pragma once

namespace dae
{
	class FSMActionBase;
	class FSMTransition;

	class FSMState
	{
	public:
		FSMState() = default;
		FSMState(const std::vector<FSMActionBase*>& pEntryActions,
			const std::vector<FSMActionBase*>& pActions,
			const std::vector<FSMActionBase*>& pExitActions,
			const std::vector<FSMTransition*>& pTransitions);
		~FSMState();

		void SetEntryActions(const std::vector<FSMActionBase*>& pActions);
		void SetActions(const std::vector<FSMActionBase*>& pActions);
		void SetExitActions(const std::vector<FSMActionBase*>& pActions);
		void SetTransitions(const std::vector<FSMTransition*>& pTransitions);

		void AddAction(FSMActionBase* pAction);
		void AddTransition(FSMTransition* pTransition);

		std::vector<FSMTransition*> GetTransitions() const;

		void Tick();
		void ExecuteEntryActions();
		void ExecuteExitActions();

	private:
		std::vector<FSMActionBase*> m_pActions;
		std::vector<FSMActionBase*> m_pEntryActions;
		std::vector<FSMActionBase*> m_pExitActions;

		std::vector<FSMTransition*> m_pTransitions;
	};
}
