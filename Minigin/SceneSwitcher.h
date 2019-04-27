#pragma once
#include "GameObject.h"

namespace dae
{
	class SceneSwitcher final : public GameObject
	{
	public:
		SceneSwitcher() = default;

		void Update() override;

	private:
		float mAccumulatedTime;
	};
}
