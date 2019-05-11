#pragma once
#include "BaseComponent.h"

namespace dae
{
	class MovementComponent : public BaseComponent
	{
	public:
		MovementComponent();

		void Update() override;

	private:
		float m_MoveSpeed;
	};
}
