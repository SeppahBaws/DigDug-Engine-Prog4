#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TextComponent;
	class InputTesterComponent final : public BaseComponent
	{
	public:
		InputTesterComponent() = default;
		virtual ~InputTesterComponent() = default;

		virtual void Update() override;

	private:
		void UpdateButtons(std::shared_ptr<TextComponent> pText);
		void UpdateTriggers(std::shared_ptr<TextComponent> pText);
		void UpdateJoysticks(std::shared_ptr<TextComponent> pText);
	};
}
