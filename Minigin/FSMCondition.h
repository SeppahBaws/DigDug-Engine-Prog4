#pragma once

namespace dae
{
	class FSMCondition
	{
	public:
		FSMCondition() {}
		virtual ~FSMCondition() {}

		virtual bool Evaluate() { return false; }
	};
}
