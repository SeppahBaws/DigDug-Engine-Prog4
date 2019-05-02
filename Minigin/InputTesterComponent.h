#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"

namespace dae
{
	class InputTesterComponent final : public BaseComponent
	{
	public:
		InputTesterComponent() = default;
		virtual ~InputTesterComponent() = default;

		virtual void Update() override;
	};
}
