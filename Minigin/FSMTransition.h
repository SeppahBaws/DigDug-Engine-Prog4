#pragma once

namespace dae
{
	class FSMActionBase;
	class FSMConditionBase;
	class FSMState;

	class FSMTransition
	{
	public:
		FSMTransition(FSMState* pTargetState, std::vector<FSMConditionBase*> pConditions, std::vector<FSMActionBase*> pExitActions);
		FSMTransition();
		~FSMTransition();

		void AddCondition(FSMConditionBase* pCondition);
		void AddExitAction(FSMActionBase* pAction);
		void SetTargetState(FSMState* pState);

		FSMState* GetTargetState() const;

		bool IsTriggered();
		void ExecuteExitActions();

	private:
		std::vector<FSMConditionBase*> m_pConditions;
		std::vector<FSMActionBase*> m_pExitActions;
		FSMState* m_pTargetState;
	};
}
