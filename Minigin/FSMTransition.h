#pragma once

namespace dae
{
	class FSMAction;
	class FSMCondition;
	class FSMState;

	class FSMTransition
	{
	public:
		FSMTransition(FSMState* pTargetState, std::vector<FSMCondition*> pConditions, std::vector<FSMAction*> pExitActions);
		FSMTransition();
		~FSMTransition();

		void AddCondition(FSMCondition* pCondition);
		void AddExitAction(FSMAction* pAction);
		void SetTargetState(FSMState* pState);

		FSMState* GetTargetState() const;

		bool IsTriggered();
		void ExecuteExitActions();

	private:
		std::vector<FSMCondition*> m_pConditions;
		std::vector<FSMAction*> m_pExitActions;
		FSMState* m_pTargetState;
	};
}
