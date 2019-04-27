#pragma once
#include "BaseComponent.h"

namespace dae
{
	class SceneSwitcherComponent final : public BaseComponent
	{
	public:
		SceneSwitcherComponent() = default;

		virtual void Update() override;

	private:
		float mAccumulatedTime = 0;
	};
}
