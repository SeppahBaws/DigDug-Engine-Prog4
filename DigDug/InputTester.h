#pragma once
#include "GameObject.h"

namespace dae
{
	class InputTester final : public GameObject
	{
	public:
		InputTester();

		virtual void Update() override;
	};
}
