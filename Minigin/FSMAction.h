#pragma once

namespace dae
{
	class FSMAction
	{
	public:
		FSMAction() {}
		virtual ~FSMAction() {}

		virtual void Execute() {}
	};
}
